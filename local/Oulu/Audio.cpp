#include "Oulu.h"


NAMESPACE_OULU_BEGIN


void VolatileAudioBuffer::Clear() {
	aud_fmt.Clear();
	frames = 0;
	frame_size = 0;
	for(int i = 0; i < 2; i++)
		data[i].Clear();
	data_i = 0;
	read_pos = 0;
	write_pos = 0;
	queue_size = 0;
	total_size = 0;
}

void VolatileAudioBuffer::SetSize(AudioFormat aud_fmt, int frames) {
	this->aud_fmt = aud_fmt;
	this->frames = frames;
	frame_size = aud_fmt.channels * aud_fmt.sample_rate * aud_fmt.var_size;
	ASSERT(aud_fmt.var_size >= 1);
	ASSERT(aud_fmt.freq >= 1);
	ASSERT(aud_fmt.channels >= 1);
	ASSERT(aud_fmt.sample_rate >= 16);
	ASSERT(frames >= 2);
	total_size = frame_size * frames;
	ASSERT(total_size > 0 && total_size < size_limit);
	for(int i = 0; i < 2; i++)
		data[i].SetCount(total_size);
	Zero();
}

void VolatileAudioBuffer::Zero() {
	if (!IsEmpty())
		for(int i = 0; i < 2; i++)
			memset(data[i].Begin(), 0, data[i].GetCount());
	data_i = 0;
	read_pos = 0;
	write_pos = 0;
	queue_size = 0;
}

void VolatileAudioBuffer::Exchange(AudioEx& e) {
	if (e.IsLoading()) {
		Audio& aud = e.Source();
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		if (aud.GetQueueSize() == 0 || IsQueueFull()) {
			e.SetFail();
			return;
		}
		
		VolatileAudioBuffer* vol_aud = dynamic_cast<VolatileAudioBuffer*>(&aud);
		
		if (vol_aud) {
			PutFrameFrom(*vol_aud, conf.sync);
		}
		else {
			TODO
		}
	}
	else if (e.IsStoring()) {
		TODO
	}
	else
		Panic("Invalid AudioEx");
}

void VolatileAudioBuffer::PutFrameFrom(VolatileAudioBuffer& aud, bool realtime) {
	// easy implementation
	thread_local static Vector<byte> tmp, conv;
	AudioFormat src_fmt = aud.GetAudioFormat();
	if (src_fmt == aud_fmt) {
		int sz = aud_fmt.GetFrameBytes();
		tmp.SetCount(sz);
		aud.Get(tmp.Begin(), sz);
		Put(tmp.Begin(), sz, realtime);
	}
	else {
		int src_sz = src_fmt.GetFrameBytes();
		tmp.SetCount(src_sz);
		int dst_sz = aud_fmt.GetFrameBytes(src_fmt.sample_rate);
		conv.SetCount(dst_sz);
		aud.Get(tmp.Begin(), src_sz);
		AudioConverter::Convert(src_fmt, tmp.Begin(), aud_fmt, conv.Begin());
		Put(conv.Begin(), dst_sz, realtime);
	}
}

void VolatileAudioBuffer::PutFrame(const AudioFormat& src_fmt, void* data, bool realtime) {
	// easy implementation
	thread_local static Vector<byte> conv;
	if (src_fmt == aud_fmt) {
		int sz = aud_fmt.GetFrameBytes();
		Put(data, sz, realtime);
	}
	else {
		int dst_sz = aud_fmt.GetFrameBytes(src_fmt.sample_rate);
		conv.SetCount(dst_sz);
		AudioConverter::Convert(src_fmt, (byte*)data, aud_fmt, conv.Begin());
		Put(conv.Begin(), dst_sz, realtime);
	}
}

int VolatileAudioBuffer::Get(void* v_, int size_) {
	byte* v = (byte*)v_;
	
	#if DEBUG_AUDIO_PIPE
	if (size_ > total_size) {
		LOG("AUDIO DEBUG: ERROR: requesting more than total size");
	}
	#endif
	
	size_ = std::min(total_size, size_);
	
	/*if (!CheckSize(size_)) {
		if (size_)
			memset(v, 0, size_);
		return;
	}*/
	
	int total_vars = size_ / aud_fmt.var_size;
	int samples_per_ch = total_vars / aud_fmt.channels;
	int copy_size = samples_per_ch * aud_fmt.channels * aud_fmt.var_size;
	ASSERT(copy_size == size_);
	
	lock.Enter();
	copy_size = min(queue_size, copy_size);
	int zero_size = size_ - copy_size;
	ASSERT(zero_size >= 0);
	
	#if DEBUG_AUDIO_PIPE
	if (zero_size) {
		LOG("AUDIO DEBUG: ERROR: zeroing frame: asked " << size_ << ", got " << copy_size);
	}
	if (queue_size < size_) {
		LOG("AUDIO DEBUG: ERROR: queue not filled");
	}
	#endif
	
	if (copy_size) {
		int new_queue_size = queue_size - copy_size;
		ASSERT(new_queue_size >= 0);
		int old_read_pos = read_pos;
		Vector<byte>& data = this->data[data_i];
		read_pos = (read_pos + copy_size) % total_size;
		queue_size = new_queue_size;
		lock.Leave();
		
		// Two parts
		if (old_read_pos + copy_size > total_size) {
			int right_size = total_size - old_read_pos;
			int left_size = copy_size - right_size;
			ASSERT(right_size + left_size == copy_size);
			
			byte* left_begin = data.Begin();
			byte* right_begin = left_begin + old_read_pos;
			ASSERT(old_read_pos + right_size <= total_size);
			ASSERT(right_size + left_size <= total_size);
			memcpy(v, right_begin, right_size);
			memcpy(v + right_size, left_begin, left_size);
			if (zero_size) {
				ASSERT(right_size + left_size + zero_size <= total_size);
				memset(v + right_size + left_size, 0, zero_size);
			}
		}
		// One part
		else {
			byte* right_begin = data.Begin() + old_read_pos;
			int right_size = copy_size;
			ASSERT(old_read_pos + right_size <= total_size);
			memcpy(v, right_begin, right_size);
			if (zero_size) {
				ASSERT(right_size + zero_size <= total_size);
				memset(v + right_size, 0, zero_size);
			}
		}
	}
	else {
		lock.Leave();
		if (size_)
			memset(v, 0, size_);
	}
	
	return copy_size;
}

void VolatileAudioBuffer::Put(void* v_, int size_, bool realtime) {
	byte* v = (byte*)v_;
	size_ = std::min(total_size, size_);
	
	//if (!CheckSize(size_))
	//	return;
	
	int total_vars = size_ / aud_fmt.var_size;
	int samples_per_ch = total_vars / aud_fmt.channels;
	int copy_size = samples_per_ch * aud_fmt.channels * aud_fmt.var_size;
	ASSERT(copy_size == size_);
	
	if (realtime) {
		int new_data_i = (data_i + 1) % 2;
		int new_read_pos = 0;
		int new_queue_size = copy_size;
		int new_write_pos = copy_size % total_size;
		Vector<byte>& data = this->data[new_data_i];
		
		ASSERT(size_ <= total_size);
		memcpy(data.Begin(), v, size_);
		
		lock.Enter();
		data_i = new_data_i;
		read_pos = new_read_pos;
		write_pos = new_write_pos;
		queue_size = new_queue_size;
		lock.Leave();
	}
	else {
		ASSERT_(queue_size < total_size, "AudioBuffer overflow");
		if (queue_size >= total_size)
			return;
		
		Vector<byte>& data = this->data[data_i];
		
		int free_size = total_size - queue_size;
		ASSERT(copy_size <= free_size);
		if (copy_size > free_size)
			copy_size = free_size;
		
		int new_queue_size = queue_size + copy_size;
		ASSERT(new_queue_size <= total_size);
		ASSERT(total_size - write_pos > 0);
		
		
		// Two parts
		if (write_pos + copy_size > total_size) {
			int right_size = total_size - write_pos;
			int left_size = copy_size - right_size;
			ASSERT(right_size + left_size == copy_size);
			
			byte* left_begin = data.Begin();
			byte* right_begin = left_begin + write_pos;
			ASSERT(write_pos + right_size <= total_size);
			ASSERT(write_pos + left_size <= total_size);
			memcpy(right_begin, v, right_size);
			memcpy(left_begin, v + right_size, left_size);
		}
		// One part
		else {
			int right_size = copy_size;
			byte* right_begin = data.Begin() + write_pos;
			ASSERT(write_pos + right_size <= total_size);
			memcpy(right_begin, v, right_size);
		}
		
		lock.Enter();
		write_pos = (write_pos + copy_size) % total_size;
		queue_size = new_queue_size;
		lock.Leave();
	}
}

bool VolatileAudioBuffer::CheckSize(int size_) {
	ASSERT(!IsEmpty());
	if (IsEmpty())
		return false;
	int size_frames = size_ / frame_size;
	ASSERT(size_ % frame_size == 0);
	if (!size_frames)
		return false;
	return true;
}






bool AudioConverter::Convert(const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst) {
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
