#include "ParallelMach.h"

NAMESPACE_PARALLEL_BEGIN


void SimpleValue::Exchange(Ex& e) {
	Value& src = e.Source();
	auto& sink_buf = GetBuffer();
	
	// Arguments for this individual SimpleValue::Exchange event
	const RealtimeSourceConfig& conf = e.SourceConfig();
	
	SimpleValue* src_val;
	Format src_fmt = src.GetFormat();
	Format& sink_fmt = fmt;
	
	if ((src_val = CastPtr<SimpleValue>(&src))) {
		auto& src_buf = src_val->GetBuffer();
		
		while (src.GetQueueSize() > 0 && !this->IsQueueFull()) {
			Packet p = src_buf.First();
			src_buf.RemoveFirst();
			RTLOG("SimpleValue::Exchange: " << p->ToString());
			Format pk_fmt = p->GetFormat();
			
			if (!pk_fmt.IsCopyCompatible(sink_fmt)) {
				Packet dst = CreatePacket(p->GetOffset());
				dst->SetFormat(sink_fmt);
				if (Convert(p, dst)) {
					RTLOG("SimpleValue::Exchange: converted packet");
					RTLOG("                       from: " << p->ToString());
					RTLOG("                       to:   " << dst->ToString());
					dst->CopyRouteData(*p);
					sink_buf.Add(dst);
				}
				else
					break;
			}
			else {
				sink_buf.Add(p);
			}
		}
	}
	else TODO
}

int SimpleValue::GetQueueSize() const {
	return buf.GetCount();
}

Format SimpleValue::GetFormat() const {
	return fmt;
}

bool SimpleValue::IsQueueFull() const {
	return buf.GetCount() >= max_packets;
}

Packet SimpleValue::Pick() {
	if (buf.IsEmpty())
		return Packet();
	Packet p = buf.First();
	buf.RemoveFirst();
	return p;
}










bool Convert(const Format& src_fmt, const byte* src, const Format& dst_fmt, byte* dst) {
	TODO
}



bool AudioConvert(int src_ch_samples, const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst);

bool Convert(const Packet& src, Packet& dst, bool keep_tracking) {
	RTLOG("Convert(src " << HexStr(&*src) << ", dst " << HexStr(&*dst) << ")");
	
	bool track = keep_tracking && src->GetTrackingId() != 0;
	bool ret = false;
	
	Format src_fmt = src->GetFormat();
	Format dst_fmt = dst->GetFormat();
	if (src_fmt.IsAudio() && dst_fmt.IsAudio()) {
		AudioFormat& srcf = src_fmt;
		AudioFormat& dstf = dst_fmt;
		int src_sr = srcf.GetSampleRate();
		int dst_sr = dstf.GetSampleRate();
		if (src_sr != dst_sr) {
			dst_sr = src_sr;
			dstf.sample_rate = src_sr;
			dst->SetFormat(dst_fmt);
		}
		
		#if 1
		
		int src_frame_sz = src_fmt.GetFrameSize();
		int dst_frame_sz = dst_fmt.GetFrameSize();
		int src_ch_samples = src_sr;
		const Vector<byte>& src_data = src->GetData();
		Vector<byte>& dst_data = dst->Data();
		dst_data.SetCount(dst_frame_sz, 0);
		ASSERT(src_data.GetCount() == src_frame_sz);
		
		#else
		
		int src_sample = srcf.GetSampleSize();
		int src_channels = srcf.res[0];
		int dst_sample = dstf.GetSampleSize();
		int dst_channels = dstf.res[0];
		const Vector<byte>& src_data = src->GetData();
		int src_ch_samples = src_data.GetCount() / (src_sample * src_channels);
		Vector<byte>& dst_data = dst->Data();
		int dst_size = src_ch_samples * dst_sample * dst_channels;
		dst_data.SetCount(dst_size);
		if (0) {
			LOG("src-size:     " << src_data.GetCount());
			LOG("src-ch-sz:    " << src_ch_samples);
			LOG("src-sample:   " << src_sample);
			LOG("src-channels: " << src_channels);
			LOG("dst-size:     " << dst_size);
			LOG("dst-sample:   " << dst_sample);
			LOG("dst-channels: " << dst_channels);
		}
		
		#endif
		
		ret = AudioConvert(src_ch_samples, srcf, src_data.Begin(), dstf, dst_data.Begin());
	}
	else {
		LOG("from: " << src_fmt.ToString() << "\nto:   " << dst_fmt.ToString());
		TODO
	}
	//else if (src_fmt.vd.val.type == ValCls::ORDER) {
	
	if (track) {
		PacketTracker_Track("Convert", __FILE__, __LINE__, *dst);
	}
	
	return ret;
}


NAMESPACE_PARALLEL_END
