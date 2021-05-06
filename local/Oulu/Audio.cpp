#include "Oulu.h"


NAMESPACE_OULU_BEGIN






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

bool AudioConverter::Convert(const AudioPacket& src, AudioPacket& dst) {
	AudioFormat src_fmt = src->GetFormat();
	AudioFormat dst_fmt = dst->GetFormat();
	int src_sample = src_fmt.GetSampleBytes();
	int dst_sample = dst_fmt.GetSampleBytes();
	const Vector<byte>& src_data = src->GetData();
	int src_samples = src_data.GetCount() / src_sample;
	Vector<byte>& dst_data = dst->Data();
	int dst_size = src_samples * dst_sample;
	dst_data.SetCount(dst_size);
	return Convert(src_fmt, src_data.Begin(), dst_fmt, dst_data.Begin());
}








AudioPacket CreateAudioPacket() {
	AudioPacketBase*					obj		= AudioPacketBase::Pool::StaticPool().New();
	RecylerRefBase<AudioPacketBase>*	base	= RecylerRefBase<AudioPacketBase>::Pool::StaticPool().New();
	base->SetObj(obj);
	return AudioPacket(obj, base);
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
			if (consumer.IsEmpty()) {
				consumer.Create();
				consumer->SetDestination(*this);
			}
			consumer->SetOffset(e.GetOffset()); // should be 0 with consumer, though
			consumer->SetSource(*vol_aud);
			consumer->SetDestinationRealtime(conf.sync);
			consumer->ConsumeAll();
			
			e.SetOffset(consumer->GetOffset());
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







bool AudioPacketProducer::ProducePacket() {
	if (src->GetCount()) {
		auto iter = src->begin();
		for (; iter; ++iter)
			if (iter()->IsOffset(offset))
				break;
		if (!iter)
			return false;
		AudioPacket p = iter();
		dst->Put(p, dst_realtime);
		++offset;
		return true;
	}
	return false;
}

void AudioPacketProducer::ProduceAll(bool blocking) {
	while (!IsFinished()) {
		if (!ProducePacket()) {
			if (!blocking) {
				break;
			}
			else {
				while (src->IsEmpty())
					Sleep(1);
			}
		}
	}
}

bool AudioPacketProducer::IsFinished() const {
	return dst->IsQueueFull();
}







void AudioPacketConsumer::SetSource(VolatileAudioBuffer& src) {
	this->src = &src;
}

void AudioPacketConsumer::SetDestination(const AudioFormat& fmt, void* dst, int dst_size) {
	dst_fmt = fmt;
	dst_mem = dst;
	dst_buf = 0;
	dst_iter = (byte*)dst;
	dst_remaining = dst_size;
}

void AudioPacketConsumer::SetDestination(VolatileAudioBuffer& dst) {
	dst_fmt = dst.GetAudioFormat();
	dst_mem = 0;
	dst_buf = &dst;
	dst_iter = 0;
	dst_remaining = 0;
}

void AudioPacketConsumer::ClearDestination() {
	dst_fmt.Clear();
	dst_mem = 0;
	dst_buf = 0;
	dst_iter = 0;
	dst_remaining = 0;
}

void AudioPacketConsumer::Consume(AudioPacket& src) {
	AudioFormat src_fmt = src->GetFormat();
	
	if (dst_fmt.IsCopyCompatible(src_fmt)) {
		if (dst_iter) {
			const Vector<byte>& src_data = src->GetData();
			if (src_data.GetCount() <= dst_remaining) {
				int copy_sz = src_data.GetCount();
				memcpy(dst_iter, src_data.Begin(), copy_sz);
				dst_iter += copy_sz;
				dst_remaining -= copy_sz;
				ASSERT(dst_remaining >= 0);
			}
			else {
				int copy_sz = dst_remaining;
				memcpy(dst_iter, src_data.Begin(), copy_sz);
				dst_iter += copy_sz;
				dst_remaining = 0;
				/*leftover_size = src_data.GetCount() - copy_sz;
				if (leftover_size > 0)
					leftover = src;*/
			}
		}
		else {
			dst_buf->Put(src, internal_count == 0 && dst_realtime);
		}
	}
	else {
		AudioPacket src2 = CreateAudioPacket();
		src2->Set(dst_fmt, src->GetOffset(), src->GetTime());
		AudioConverter::Convert(src, src2);
		/*if (src_data_shift) {
			int src_sample = src_fmt.GetSampleBytes();
			int dst_sample = dst_fmt->GetSampleBytes();
			src_data_shift = src_data_shift * dst_sample / src_sample;
		}*/
		Consume(src2);
	}
}

bool AudioPacketConsumer::ConsumePacket() {
	ASSERT(dst_buf || dst_remaining > 0);
	/*if (leftover) {
		ASSERT(leftover_size > 0);
		int data_shift = leftover->GetData().GetCount() - leftover_size;
		AudioPacket p;
		Swap(leftover, p);
		Consume(p, data_shift);
		return true;
	}
	else*/
	if (src->GetQueueSize()) {
		AUDIOLOG("AudioPacketConsumer::ConsumePacket: get " << offset.ToString());
		
		AudioPacket p = src->Get(offset);
		if (p) {
			Consume(p);
			++offset;
			++internal_count;
			return true;
		}
	}
	return false;
}

void AudioPacketConsumer::ConsumeAll(bool blocking) {
	internal_count = 0;
	while (!IsFinished()) {
		if (!ConsumePacket()) {
			if (!blocking) {
				if (dst_iter)
					memset(dst_iter, 0, dst_remaining);
				break;
			}
			else {
				while (!src->GetQueueSize())
					Sleep(1);
			}
		}
	}
}

bool AudioPacketConsumer::IsFinished() const {
	if (dst_mem)
		return dst_remaining == 0;
	else
		return dst_buf->IsQueueFull();
}







NAMESPACE_OULU_END
