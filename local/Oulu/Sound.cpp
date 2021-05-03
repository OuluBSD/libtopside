#include "Oulu.h"


NAMESPACE_OULU_BEGIN


void VolatileSoundBuffer::Clear() {
	aud_fmt.Clear();
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

void VolatileSoundBuffer::SetSize(AudioFormat aud_fmt, int frames) {
	this->aud_fmt = aud_fmt;
	this->frames = frames;
	frame_size = aud_fmt.channels * aud_fmt.sample_rate * aud_fmt.var_size;
	ASSERT(aud_fmt.var_size >= 1);
	ASSERT(aud_fmt.freq >= 1);
	ASSERT(aud_fmt.channels >= 1);
	ASSERT(aud_fmt.sample_rate >= 16);
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

void VolatileSoundBuffer::Exchange(AudioEx& e) {
	if (e.IsLoading())
		Get(e);
	else if (e.IsStoring())
		Put(e);
	else
		Panic("Invalid AudioEx");
}

void VolatileSoundBuffer::Get(AudioEx& e) {
	TODO
	#if 0
	byte* v = (byte*)v_;
	if (!CheckSize(size_)) {
		if (size_)
			memset(v, 0, size_);
		return;
	}
	
	int total_vars = size_ / aud_fmt.var_size;
	int samples = total_vars / aud_fmt.channels;
	int in_frames = samples / aud_fmt.sample_rate;
	ASSERT(in_frames * aud_fmt.sample_rate * aud_fmt.channels == total_vars);
	
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
	#endif
}

void VolatileSoundBuffer::Put(AudioEx& e) {
	TODO
	#if 0
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
	#endif
}

#if 0
bool VolatileSoundBuffer::GetFrameFrom(Sound& snd, bool realtime) {
	TODO
	
	if (snd.GetQueueSize() == 0)
		return false;
	if (IsQueueFull())
		return false;
	
	// easy implementation
	thread_local static Vector<byte> tmp, conv;
	AudioFormat src_fmt = snd.GetAudioFormat();
	if (src_fmt == aud_fmt) {
		int sz = aud_fmt.GetFrameBytes();
		tmp.SetCount(sz);
		snd.Get(tmp.Begin(), sz);
		Put(tmp.Begin(), sz, realtime);
		return true;
	}
	else {
		int src_sz = src_fmt.GetFrameBytes();
		tmp.SetCount(src_sz);
		int dst_sz = aud_fmt.GetFrameBytes(src_fmt.sample_rate);
		conv.SetCount(dst_sz);
		snd.Get(tmp.Begin(), src_sz);
		SoundConverter::Convert(src_fmt, tmp.Begin(), aud_fmt, conv.Begin());
		Put(conv.Begin(), dst_sz, realtime);
		return true;
	}
}
#endif

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






bool SoundConverter::Convert(const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst) {
	#define LIST_A(nat_is_be) \
		ITEM_A(nat_is_be, unsigned char, 0) \
		ITEM_A(nat_is_be, unsigned short, 0) \
		ITEM_A(nat_is_be, unsigned int, 0) \
		ITEM_A(nat_is_be, char, 1) \
		ITEM_A(nat_is_be, short, 1) \
		ITEM_A(nat_is_be, int, 1) \
		ITEM_A(nat_is_be, float, 0) \
		ITEM_A(nat_is_be, double, 0) \
		ITEM_A(nat_is_be, float, 1) \
		ITEM_A(nat_is_be, double, 1)
	#define ITEM_A(nat_is_be, a, a_signed) \
		ITEM_B(nat_is_be, a, a_signed, unsigned char, 0) \
		ITEM_B(nat_is_be, a, a_signed, unsigned short, 0) \
		ITEM_B(nat_is_be, a, a_signed, unsigned int, 0) \
		ITEM_B(nat_is_be, a, a_signed, char, 1) \
		ITEM_B(nat_is_be, a, a_signed, short, 1) \
		ITEM_B(nat_is_be, a, a_signed, int, 1) \
		ITEM_B(nat_is_be, a, a_signed, float, 0) \
		ITEM_B(nat_is_be, a, a_signed, double, 0) \
		ITEM_B(nat_is_be, a, a_signed, float, 1) \
		ITEM_B(nat_is_be, a, a_signed, double, 1)
	#define ITEM_B(nat_is_be, a, a_signed, b, b_signed) \
		if (src_fmt.var_size == sizeof(a) && \
			src_fmt.is_var_float == (std::is_same<a,float>() || std::is_same<a,double>()) && \
			src_fmt.is_var_signed == a_signed && \
			dst_fmt.var_size == sizeof(b) && \
			dst_fmt.is_var_float == (std::is_same<b,float>() || std::is_same<b,double>()) && \
			dst_fmt.is_var_signed == b_signed) {\
			if (src_fmt.is_var_bigendian == nat_is_be) { \
				if (dst_fmt.is_var_bigendian == nat_is_be) \
					TypeConvert<a,b,1,1>(src_fmt, src, dst_fmt, dst); \
				else \
					TypeConvert<a,b,1,0>(src_fmt, src, dst_fmt, dst); \
			} \
			else { \
				if (dst_fmt.is_var_bigendian == nat_is_be) \
					TypeConvert<a,b,0,1>(src_fmt, src, dst_fmt, dst); \
				else \
					TypeConvert<a,b,0,0>(src_fmt, src, dst_fmt, dst); \
			} \
			return true; \
		}
	#if CPU_LITTLE_ENDIAN
	LIST_A(false)
	#else
	LIST_A(true)
	#endif
	#undef LIST_A
	#undef ITEM_A
	#undef ITEM_B
	return false;
}

NAMESPACE_OULU_END
