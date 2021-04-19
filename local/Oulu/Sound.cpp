#include "Oulu.h"


NAMESPACE_OULU_BEGIN


void VolatileSoundBuffer::Clear() {
	snd_fmt.Clear();
	frames = 0;
	frame_size = 0;
	for(int i = 0; i < 2; i++)
		data[i].Clear();
	data_i = 0;
	read_pos = 0;
	write_pos = 0;
	queue_size = 0;
	write_frame = 0;
}

void VolatileSoundBuffer::SetSize(SoundFormat snd_fmt, int frames) {
	this->snd_fmt = snd_fmt;
	this->frames = frames;
	frame_size = snd_fmt.channels * snd_fmt.sample_rate * snd_fmt.var_size;
	ASSERT(snd_fmt.var_size >= 1);
	ASSERT(snd_fmt.freq >= 1);
	ASSERT(snd_fmt.channels >= 1);
	ASSERT(snd_fmt.sample_rate >= 16);
	ASSERT(frames >= 2);
	int total = frame_size * frames;
	ASSERT(total > 0 && total < size_limit);
	for(int i = 0; i < 2; i++)
		data[i].SetCount(total);
	Zero();
}

void VolatileSoundBuffer::Zero() {
	if (!IsEmpty())
		for(int i = 0; i < 2; i++)
			memset(data[i].Begin(), 0, data[i].GetCount());
	data_i = 0;
	read_pos = 0;
	write_pos = 0;
	queue_size = 0;
	write_frame = 0;
}

void VolatileSoundBuffer::Get(void* v_, int size_) {
	byte* v = (byte*)v_;
	if (!CheckSize(size_)) {
		if (size_)
			memset(v, 0, size_);
		return;
	}
	
	int total_vars = size_ / snd_fmt.var_size;
	int samples = total_vars / snd_fmt.channels;
	int in_frames = samples / snd_fmt.sample_rate;
	ASSERT(in_frames * snd_fmt.sample_rate * snd_fmt.channels == total_vars);
	
	lock.Enter();
	int size_frames = min(queue_size, in_frames);
	int zero_frames = in_frames - size_frames;
	
	if (size_frames) {
		int new_queue_size = queue_size - size_frames;
		ASSERT(new_queue_size >= 0);
		ASSERT(frames - read_pos > 0);
		int old_read_pos = read_pos;
		Vector<byte>& data = this->data[data_i];
		read_pos = (read_pos + size_frames) % frames;
		queue_size = new_queue_size;
		lock.Leave();
		
		// Two parts
		if (old_read_pos + size_frames > frames) {
			int right_side = frames - old_read_pos;
			int left_side = size_frames - right_side;
			ASSERT(right_side + left_side == size_frames);
			
			byte* left_begin = data.Begin();
			byte* right_begin = left_begin + old_read_pos * frame_size;
			int right_size = right_side * frame_size;
			int left_size = left_side * frame_size;
			memcpy(v, right_begin, right_size);
			memcpy(v + right_size, left_begin, left_size);
			if (zero_frames)
				memset(v + right_size + left_size, 0, zero_frames * frame_size);
		}
		// One part
		else {
			byte* right_begin = data.Begin() + old_read_pos * frame_size;
			int right_size = size_frames * frame_size;
			memcpy(v, right_begin, right_size);
			if (zero_frames)
				memset(v + right_size, 0, zero_frames * frame_size);
		}
	}
	else {
		lock.Leave();
		if (size_)
			memset(v, 0, size_);
	}
}

void VolatileSoundBuffer::Put(void* v_, int size_, bool realtime) {
	byte* v = (byte*)v_;
	if (!CheckSize(size_))
		return;
	
	int size_frames = size_ / frame_size;
	size_frames = min(size_frames, frames);
	size_ = size_frames * frame_size; // align size to frames
	ASSERT(size_ % frame_size == 0);
	
	write_frame += size_frames;
	
	if (realtime) {
		int new_data_i = (data_i + 1) % 2;
		int new_read_pos = 0;
		int new_queue_size = size_frames;
		int new_write_pos = new_queue_size % frames;
		Vector<byte>& data = this->data[new_data_i];
		
		memcpy(data.Begin(), v, size_);
		
		lock.Enter();
		data_i = new_data_i;
		read_pos = new_read_pos;
		write_pos = new_write_pos;
		queue_size = new_queue_size;
		lock.Leave();
	}
	else {
		ASSERT_(queue_size < frames, "SoundBuffer overflow");
		if (queue_size >= frames)
			return;
		
		Vector<byte>& data = this->data[data_i];
		
		int free_frames = frames - queue_size;
		ASSERT(size_frames <= free_frames);
		if (size_frames > free_frames) {
			size_frames = free_frames;
			size_ = free_frames * frame_size;
		}
		
		int new_queue_size = queue_size + size_frames;
		ASSERT(new_queue_size <= frames);
		ASSERT(frames - write_pos > 0);
		
		// Two parts
		if (write_pos + size_frames > frames) {
			int right_side = frames - write_pos;
			int left_side = size_frames - right_side;
			ASSERT(right_side + left_side == size_frames);
			
			byte* left_begin = data.Begin();
			byte* right_begin = left_begin + write_pos * frame_size;
			int right_size = right_side * frame_size;
			int left_size = left_side * frame_size;
			memcpy(right_begin, v, right_size);
			memcpy(left_begin, v + right_size, left_size);
		}
		// One part
		else {
			int right_side = size_frames;
			byte* right_begin = data.Begin() + write_pos * frame_size;
			int right_size = right_side * frame_size;
			memcpy(right_begin, v, right_size);
		}
		
		lock.Enter();
		write_pos = (write_pos + size_frames) % frames;
		queue_size = new_queue_size;
		lock.Leave();
	}
}

bool VolatileSoundBuffer::CheckSize(int size_) {
	ASSERT(!IsEmpty());
	if (IsEmpty())
		return false;
	int size_frames = size_ / frame_size;
	ASSERT(size_ % frame_size == 0);
	if (!size_frames)
		return false;
	return true;
}

template <class T> void SoundBufferUnitTestT() {
	SoundFormat fmt;
	fmt.var_size = sizeof(T);
	fmt.is_var_float = ((T)1.5) == 1.5;
	fmt.channels = 2;
	fmt.sample_rate = 32;
	fmt.freq = 1024;
	int frames = 2;
	
	Vector<T> from, to;
	from.SetCount(fmt.sample_rate * fmt.channels);
	to.SetCount(fmt.sample_rate * fmt.channels);
	
	for(int i = 0; i < fmt.sample_rate; i++) {
		from[i*2 + 0] = +1 + i + 0.5;
		from[i*2 + 1] = -1 - i + 0.5;
	}
	
	VolatileSoundBuffer b;
	b.SetSize(fmt, frames);
	
	for(int i = 0; i < frames; i++)
		b.Put((T*)from.Begin(), from.GetCount() * fmt.var_size, false);
	b.Get((T*)to.Begin(), to.GetCount() * fmt.var_size);
	
	for(int i = 0; i < from.GetCount(); i++) {
		T f = from[i];
		T t = to[i];
		ASSERT(f == t);
	}
}

void SoundBufferUnitTest() {
	SoundBufferUnitTestT<uint8>();
	SoundBufferUnitTestT<uint16>();
	SoundBufferUnitTestT<int32>();
	SoundBufferUnitTestT<float>();
}

NAMESPACE_OULU_END
