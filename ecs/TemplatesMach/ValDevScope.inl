#define DataT			typename ScopeValMachT<typename ValDevSpec::Val>

NAMESPACE_TOPSIDE_BEGIN



TMPL_VALDEVMACH(void) SimpleValue::Exchange(Ex& e) {
	if (e.IsStoring()) {
		Value& sink = e.Sink();
		ASSERT((Value*)&e.Source() == 0);
		auto& src_buf = GetBuffer();
		
		// Arguments for this individual SimpleValue::Exchange event
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		// Consumer model
		/*if (use_consumer) {*/
		SimpleValue* sink_val;
		
		if ((sink_val = CastPtr<SimpleValue>(&sink))) {
			auto& sink_buf = sink_val->GetBuffer();
			
			while (this->GetQueueSize() > 0 && !sink_val->IsQueueFull()) {
				Packet p = src_buf.First();
				src_buf.RemoveFirst();
				ASSERT(p->GetFormat() == fmt);
				sink_buf.Add(p);
			}
		}
		else TODO
		
		// Producer model
		/*} else {
			SimpleValue* sink_vol;
			
			if ((src_vol = CastPtr<SimpleValue>(&src))) {
				if ((sink_vol = CastPtr<SimpleValue>(&sink))) {
					while (src_vol->GetQueueSize() > 0 && !sink_vol->IsQueueFull()) {
						Packet src_p = src_vol->Get(offset);
						Packet sink_p = ValMach::CreatePacket(src_p->GetOffset());
						sink_p->Set(fmt, time);
						//p->Data().SetCount(fmt.GetFrameBytes(), 0);
						StorePacket(sink_p);
						vol->Put(sink_p, false);
						time += fmt.GetFrameSeconds();
					}
				}
				else TODO
			}
			else TODO
		}*/
	}
	else if (e.IsLoading()) {
		Value& src = e.Source();
		ASSERT((Value*)&e.Sink() == 0);
		auto& sink_buf = GetBuffer();
		
		// Arguments for this individual SimpleValue::Exchange event
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		SimpleValue* src_val;
		
		if ((src_val = CastPtr<SimpleValue>(&src))) {
			auto& src_buf = src_val->GetBuffer();
			
			while (src.GetQueueSize() > 0 && !this->IsQueueFull()) {
				Packet p = src_buf.First();
				src_buf.RemoveFirst();
				ASSERT(p->GetFormat() == fmt);
				sink_buf.Add(p);
			}
		}
		else TODO
	}
	else Panic("SimpleValue::Exchange: Internal error. Ex not storing nor loading.");
}

TMPL_VALDEVMACH(int) SimpleValue::GetQueueSize() const {
	return buf.GetCount();
}

TMPL_VALDEVMACH(DataT::Format) SimpleValue::GetFormat() const {
	return fmt;
}

TMPL_VALDEVMACH(bool) SimpleValue::IsQueueFull() const {
	int sr = fmt.GetSampleRate();
	if (sr > 1) {
		int size = 0;
		for(auto& p : buf)
			size += p->GetSizeChannelSamples();
		int c = size / sr;
		return c >= packet_limit;
	}
	else {
		return buf.GetCount() >= packet_limit;
	}
}


















TMPL_VALDEVMACH(typename ScopeValMachT<typename ValDevSpec::Val>::Packet)
SimpleValue::Pick() {
	using ValSpec				= typename ValDevSpec::Val;
	using ValMach				= ScopeValMachT<ValSpec>;
	using Packet				= typename ValMach::Packet;
	
	if (buf.IsEmpty())
		return Packet();
	Packet p = buf.First();
	buf.RemoveFirst();
	return p;
}











TMPL_VALDEVMACH(void) SimpleBufferedValue::Exchange(Ex& e) {
	using ValSpec				= typename ValDevSpec::Val;
	using Mach					= ScopeValDevMachT<ValDevSpec>;
	using ValMach				= ScopeValMachT<ValSpec>;
	using SimpleBufferedValue	= typename Mach::SimpleBufferedValue;
	using PacketBuffer			= typename Mach::PacketBuffer;
	using SimpleValue			= typename Mach::SimpleValue;
	
	
	if (e.IsStoring()) {
		if (buf.IsEmpty()) {
			e.SetFail();
			return;
		}
		auto val_fmt = GetFormat();
		ASSERT(val_fmt.IsValid());
		
		#if DEBUG_RT_PIPE
		{
			auto frame_iter = buf.begin();
			Packet& p = frame_iter();
			off32 buf_read_pos = p->GetOffset();
			
			// Compare exchange and source formats
			auto cmp_fmt = p->GetFormat();
			ASSERT(cmp_fmt == val_fmt);
			
			RTLOG("SimpleBufferedValue::Exchange: buffer read position " << buf_read_pos.ToString());
		}
		#endif
		
		Value& src = e.Source();
		Value& sink = e.Sink();
		ASSERT((Value*)&src == 0);
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		SimpleValue* dst_sbuf;
		SimpleBufferedValue* dst_buf;
		if ((dst_sbuf = CastPtr<SimpleValue>(&sink))) {
			if (producer.IsEmptySource())
				producer.SetSource(buf);
			
			ASSERT(!sink.IsQueueFull());
			
			producer.SetDestination(*dst_sbuf, min_buf_samples);
			producer.SetDestinationRealtime(conf.sync);
			producer.ProduceAll();
			producer.ClearDestination();
			
			int count = producer.GetCount();
			RTLOG("SimpleBufferedValue::Exchange: produced count=" << count);
			
			off32 end = producer.PickLastOffset();
			sink_offsets.GetAdd(&e.Sink(), end) = end;
			
			exchange_count += count;
			
			if (!count)
				e.SetFail();
		}
		else if ((dst_buf = CastPtr<SimpleBufferedValue>(&sink))) {
			while (!buf.IsEmpty()) {
				Packet p = buf.First();
				buf.RemoveFirst();
				p->CheckTracking(TrackerInfo(this, __FILE__, __LINE__));
				dst_buf->GetBuffer().Add(p);
			}
		}
		else {
			TODO
		}
	}
	else if (e.IsLoading()) {
		auto val_fmt = GetFormat();
		ASSERT(val_fmt.IsValid());
		
		
		Value& src = e.Source();
		Value& sink = e.Sink();
		ASSERT((Value*)&sink == 0);
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		PacketBuffer& src_buf = src.GetBuffer();
		if (src_buf.IsEmpty()) {
			e.SetFail();
			return;
		}
		//LOG("BUF dyn name: " << src.GetDynamicName());
		#if DEBUG_RT_PIPE
		{
			auto frame_iter = src_buf.begin();
			Packet& p = frame_iter();
			off32 buf_read_pos = p->GetOffset();
			
			// Compare exchange and source formats
			//auto cmp_fmt = p->GetFormat();
			//ASSERT(cmp_fmt == val_fmt);
			
			RTLOG("SimpleBufferedValue::Exchange: buffer read position " << buf_read_pos.ToString());
		}
		#endif
		
		ASSERT(!IsQueueFull());
		
		consumer.SetSource(src_buf);
		consumer.SetDestination(val_fmt, this->buf, min_buf_samples);
		consumer.SetDestinationRealtime(conf.sync);
		consumer.ConsumeAll();
		consumer.ClearDestination();
		
		int count = consumer.GetCount();
		RTLOG("SimpleBufferedValue::Exchange: produced count=" << count);
		
		exchange_count += count;
		
		if (!count)
			e.SetFail();
	}
	else {
		Panic("Invalid Ex in SimpleBufferedValue");
	}
}

TMPL_VALDEVMACH(int) SimpleBufferedValue::GetQueueSize() const {
	return buf.GetCount();
}

TMPL_VALDEVMACH(DataT::Format) SimpleBufferedValue::GetFormat() const {
	return fmt;
}

TMPL_VALDEVMACH(bool) SimpleBufferedValue::IsQueueFull() const {
	int cs = GetQueueChannelSamples();
	return cs >= min_buf_samples;
}

TMPL_VALDEVMACH(int) SimpleBufferedValue::GetQueueChannelSamples() const {
	int size = 0;
	for(auto& p : buf)
		size += p->GetSizeChannelSamples();
	return size;
}

TMPL_VALDEVMACH(int) SimpleBufferedValue::GetQueueTotalSamples() const {
	int size = 0;
	for(auto& p : buf)
		size += p->GetSizeTotalSamples();
	return size;
}

/*TMPL_VALDEVMACH(void) SimpleBufferedValue::FillBuffersNull() {
	if (!IsQueueFull()) {
		Packet p = ValMach::CreatePacket();
		RTLOG("SimpleBufferedValue::FillBuffersNull: filling buffer with empty packets. offset " << offset.ToString());
		p->Set(fmt, offset, -1);
		p->Data().SetCount(fmt.GetFrameSize(), 0);
		buf.Add(p);
	}
}*/

TMPL_VALDEVMACH(void) SimpleBufferedValue::DropBuffer() {
	if (exchange_count == 0)
		return;
	ASSERT(sink_offsets.GetCount());
	
	// Find sink with lowest read position
	auto sink_iter = sink_offsets.GetValues().begin();
	off32 end_offset_min = sink_iter();
	for(++sink_iter; sink_iter; ++sink_iter)
		end_offset_min = std::min(end_offset_min, sink_iter());
	
	int rem_count = 0;
	auto pkt_iter = buf.begin();
	off32 anchor = pkt_iter()->GetOffset(); // for integer overflow
	for(; pkt_iter; ++pkt_iter) {
		if (off32::GetDifferenceI64(anchor, pkt_iter()->GetOffset(), end_offset_min) > 0) {
			RTLOG("SimpleBufferedValue::DropBuffer: dropping " << pkt_iter()->GetOffset().ToString());
			++rem_count;
		}
		else break;
	}
	
	if (1) {
		RTLOG("SimpleBufferedValue::DropBuffer: "
			"exchange_count " << exchange_count << ", " <<
			"rem_count " << rem_count << ", " <<
			"end_offset_min " << end_offset_min.ToString());}
	
	if (rem_count) {
		buf.RemoveFirst(rem_count);
		sink_offsets.Clear();
	}
}












TMPL_VALDEVMACH(void) SimpleBufferedStream::FillBuffer() {
	while (!ptr->IsQueueFull() && !IsEof()) {
		if (ReadFrame()) {
			if (ProcessFrame())
				continue;
			if (ProcessOtherFrame())
				continue;
			
			ClearPacketData();
		}
		else break;
	}
	
	TODO
	//if (IsEof())
	//	ptr->FillBuffersNull();
	
	ClearPacketData();
}







/*TMPL_VALDEVMACH(bool) VolatileBuffer::IsQueueFull() const {
	if (Buffer::IsEmpty())
		return false;
	int sz = Buffer::GetQueueSizeBytes();
	int preferred_sz = preferred_fmt.GetFrameBytes() * 2;
	return sz >= preferred_sz;
}*/

/*TMPL_VALDEVMACH(void) VolatileBuffer::Exchange(Ex& e) {
	if (e.IsLoading()) {
		Value& aud = e.Source();
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		
		VolatileBuffer* vol_aud = CastPtr<VolatileBuffer>(&aud);
		if (vol_aud) {
			if (consumer.IsEmpty()) {
				consumer.Create();
				consumer->SetDestination(*this);
			}
			
			if (!consumer->HasLeftover() && (aud.GetQueueSize() == 0 || IsQueueFull())) {
				e.SetFail();
				return;
			}
			
			consumer->SetSource(*vol_aud);
			consumer->SetDestinationRealtime(conf.sync);
			consumer->ConsumeAll();
		}
		else {
			TODO
		}
	}
	else if (e.IsStoring()) {
		TODO
	}
	else
		Panic("Invalid Ex");
}*/







TMPL_VALDEVMACH(bool) PacketProducer::ProducePacket() {
	if (src->GetCount()) {
		auto iter = src->begin();
		TODO
	/*	for (; iter; ++iter)
			if (iter()->IsOffset(offset))
				break;*/
		if (!iter)
			return false;
		if (tmp_realtime) {
			dst->Clear();
			tmp_realtime = false;
		}
		Packet p = iter();
		p->CheckTracking(TrackerInfo(this, __FILE__, __LINE__));
		dst->Add(p);
		internal_written_bytes += p->GetSizeBytes();
		/*offset = p->GetOffset();
		++offset;*/
		packet_count++;
		last = p;
		return true;
	}
	return false;
}

TMPL_VALDEVMACH(void) PacketProducer::ProduceAll(bool blocking) {
	internal_written_bytes = 0;
	packet_count = 0;
	tmp_realtime = dst_realtime;
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

TMPL_VALDEVMACH(bool) PacketProducer::IsFinished() const {
	return dst->GetCount() >= packet_limit;
}







TMPL_VALDEVMACH(void) PacketConsumer::SetSource(PacketBuffer& src) {
	this->src_buf = &src;
}

TMPL_VALDEVMACH(void) PacketConsumer::SetDestination(const Format& fmt, void* dst, int dst_size) {
	dst_fmt = fmt;
	dst_mem = dst;
	dst_buf = 0;
	dst_buf_limit = 0;
	dst_iter = (byte*)dst;
	dst_iter_end = dst_iter + dst_size;
	this->dst_size = dst_size;
}

TMPL_VALDEVMACH(void) PacketConsumer::SetDestination(const Format& fmt, PacketBuffer& dst, int limit) {
	ASSERT(limit > 0);
	dst_fmt = fmt;
	dst_mem = 0;
	dst_buf = &dst;
	dst_buf_limit = limit;
	dst_iter = 0;
	dst_iter_end = 0;
	dst_size = 0;
}

TMPL_VALDEVMACH(void) PacketConsumer::ClearDestination() {
	dst_fmt.Clear();
	dst_mem = 0;
	dst_buf = 0;
	dst_buf_limit = 0;
	dst_iter = 0;
	dst_iter_end = 0;
	dst_size = 0;
}

/*TMPL_VALDEVMACH(void) PacketConsumer::TestSetOffset(off32 offset) {
	if (HasLeftover()) {
		if (this->offset != offset) {
			ClearLeftover();
			SetOffset(offset);
		}
	}
	else
		SetOffset(offset);
}*/

TMPL_VALDEVMACH(void) PacketConsumer::Consume(Packet& src, int src_data_shift) {
	Format src_fmt = src->GetFormat();
	
	if (dst_fmt.IsCopyCompatible(src_fmt)) {
		if (dst_iter) {
			const Vector<byte>& src_data = src->GetData();
			int copy_sz = src_data.GetCount() - src_data_shift;
			ASSERT(copy_sz > 0);
			int dst_remaining = dst_size - internal_written_bytes;
			if (copy_sz < dst_remaining) {
				memcpy(dst_iter, src_data.Begin() + src_data_shift, copy_sz);
				dst_iter += copy_sz;
				ASSERT(dst_iter != dst_iter_end);
			}
			else {
				copy_sz = dst_remaining;
				memcpy(dst_iter, src_data.Begin() + src_data_shift, copy_sz);
				dst_iter += copy_sz;
				ASSERT(dst_iter == dst_iter_end);
			}
			internal_written_bytes += copy_sz;
			leftover_size = src_data.GetCount() - src_data_shift - copy_sz;
			ASSERT(!leftover);
			ASSERT(leftover_size >= 0);
			if (leftover_size > 0)
				leftover = src;
			else {
				src->StopTracking(TrackerInfo(this, __FILE__, __LINE__));
				consumed_packets.Add(src);
			}
		}
		else {
			src->CheckTracking(TrackerInfo(this, __FILE__, __LINE__));
			internal_written_bytes += src->GetSizeBytes();
			if (consumed_packets.IsEmpty() && dst_realtime)
				dst_buf->Clear();
			dst_buf->Add(src);
			consumed_packets.Add(src);
		}
	}
	else {
		Packet src2 = ValMach::CreatePacket(src->GetOffset());
		src2->Set(dst_fmt, src->GetTime());
		Convert(src, src2);
		if (src_data_shift) {
			int src_sample = src_fmt.GetSampleSize();
			int dst_sample = dst_fmt.GetSampleSize();
			src_data_shift = src_data_shift * dst_sample / src_sample;
		}
		Consume(src2, src_data_shift);
	}
}

TMPL_VALDEVMACH(bool) PacketConsumer::ConsumePacket() {
	ASSERT(dst_buf || internal_written_bytes < dst_size);
	if (leftover) {
		RTLOG("PacketConsumer::ConsumePacket: consume leftover " << leftover->GetOffset().ToString() << ", " << leftover_size << " bytes");
		ASSERT(leftover_size > 0);
		int data_shift = leftover->GetData().GetCount() - leftover_size;
		Packet p;
		Swap(leftover, p);
		Consume(p, data_shift);
		return true;
	}
	else
	if (src_buf->GetCount()) {
		RTLOG("PacketConsumer::ConsumePacket: pick next");
		
		Packet p = src_buf->First();
		if (p) {
			src_buf->RemoveFirst();
			Consume(p, 0);
			return true;
		}
	}
	return false;
}

TMPL_VALDEVMACH(void) PacketConsumer::ConsumeAll(bool blocking) {
	consumed_packets.Clear();
	internal_written_bytes = 0;
	while (!IsFinished()) {
		if (!ConsumePacket()) {
			if (!blocking) {
				int dst_remaining = dst_size - internal_written_bytes;
				if (dst_iter)
					memset(dst_iter, 0, dst_remaining);
				break;
			}
			else {
				while (!src_buf->GetCount())
					Sleep(1);
			}
		}
	}
}

TMPL_VALDEVMACH(bool) PacketConsumer::IsFinished() const {
	if (dst_mem)
		return internal_written_bytes >= dst_size;
	else
		return dst_buf->GetCount() >= dst_buf_limit;
}

/*TMPL_VALDEVMACH(void) Ex::SetOffset(off32 packet_count) {
	//RTLOG("AudioEx::SetOffset: offset " << packet_count.ToString());
	this->offset = packet_count;
}*/

TMPL_VALDEVMACH(bool) Convert(const Format& src_fmt, const byte* src, const Format& dst_fmt, byte* dst) {
	TODO
}

TMPL_VALDEVMACH(bool) Convert(const Packet& src, Packet& dst) {
	TODO
}


bool AudioConvert(int src_ch_samples, const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst);

template <>
inline bool ScopeValDevMachT<CenterAudioSpec>::Convert(const AudioPacket& src, AudioPacket& dst) {
	AudioFormat src_fmt = src->GetFormat();
	AudioFormat dst_fmt = dst->GetFormat();
	int src_sample = src_fmt.GetSampleSize();
	int src_channels = src_fmt.channels;
	int dst_sample = dst_fmt.GetSampleSize();
	int dst_channels = dst_fmt.channels;
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
	return AudioConvert(src_ch_samples, src_fmt, src_data.Begin(), dst_fmt, dst_data.Begin());
}


NAMESPACE_TOPSIDE_END

#undef DataT