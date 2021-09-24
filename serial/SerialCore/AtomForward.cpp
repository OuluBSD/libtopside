#include "Internal.h"

NAMESPACE_SERIAL_BEGIN


void AtomBase::ForwardAtom(FwdScope& fwd) {
	RTLOG("AtomBase::ForwardAtom");
	
	last_cfg = &fwd.Cfg();
	
	
	#ifdef flagDEBUG
	int ch_i = 0;
	int pre_sink_packet_count = GetSink()->GetValue(ch_i).GetQueueSize();
	int pre_src_packet_count = GetSource()->GetStream(ch_i).Get().GetQueueSize();
	int pre_consumed = consumed_packets.GetCount();
	int pre_consumed_partial = IsConsumedPartialPacket();
	int pre_total =
		  pre_sink_packet_count
		  + pre_src_packet_count
		  + (pre_consumed - pre_consumed_partial); // partial packet stays in sink while fraction is consumed
	#endif
	
	
	AtomTypeCls type = GetType();
	switch (type.role) {
		case DRIVER:		ForwardDriver(fwd);		break;
		case CUSTOMER:		ForwardCustomer(fwd);	break;
		case SOURCE:		ForwardSource(fwd);		break;
		case SINK:			ForwardSink(fwd);		break;
		case CONVERTER:		ForwardSource(fwd);		break;
		case SIDE_SOURCE:	ForwardSideSource(fwd);	break;
		case SIDE_SINK:		ForwardSideSink(fwd);	break;
		default: ASSERT_(0, "Invalid AtomTypeCls role"); break;
	}
	
	
	#ifdef flagDEBUG
	int post_sink_packet_count = GetSink()->GetValue(ch_i).GetQueueSize();
	int post_src_packet_count = GetSource()->GetStream(ch_i).Get().GetQueueSize();
	int post_consumed = consumed_packets.GetCount();
	int post_consumed_partial = IsConsumedPartialPacket();
	int post_total =
		  post_sink_packet_count
		+ post_src_packet_count
		+ (post_consumed - post_consumed_partial);
	bool consumed_only_partial =
		pre_sink_packet_count == post_sink_packet_count &&
		pre_src_packet_count == post_src_packet_count &&
		pre_consumed == 0 && post_consumed == 0 &&
		pre_consumed_partial == 1 && post_consumed_partial == 0;
	if (type.role != CUSTOMER) {
		bool is_buffered_consumer = type.iface.content.val == ValCls::AUDIO; // todo: other value formats
		ASSERT_(
			dbg_async_race ||
			pre_total == post_total ||
			consumed_only_partial ||
			is_buffered_consumer,
			"Atom lost packets. Maybe alt class did not call PacketConsumed(...) for the packet?");
		/*
		On fail:
			- have you implemented "IsConsumedPartialPacket() override" while using PacketConsumer?
		*/
	}
	#endif
}

void AtomBase::ForwardDriver(FwdScope& fwd) {
	Forward(fwd);
}

void AtomBase::ForwardCustomer(FwdScope& fwd) {
	CustomerData* p = GetCustomerData();
	ASSERT(p);
	if (!p) return;
	
	const int src_ch_i = 0;
	const int sink_ch_i = 0;
	
	CustomerData& c = *p;
	
	int read_i = fwd.GetPos();
	if (read_i == 0) {
		Value& src_value = GetSource()->GetSourceValue(src_ch_i);
		
		if (src_value.IsQueueFull()) {
			RTLOG("AtomBase::ForwardCustomer: skipping order, because queue is full");
			return;
		}
		
		if (c.unfulfilled_offsets.GetCount() >= c.max_unfulfilled) {
			RTLOG("AtomBase::ForwardCustomer: warning: receipt packets are not getting through or unfulfilled limit is too low");
			GetMachine().WarnDeveloper("receipt packets are not getting through or unfulfilled limit is too low");
			return;
		}
		
		
		off32 off = c.gen.Create();
		Packet p = CreatePacket(off);
		
		ASSERT(c.unfulfilled_offsets.GetCount() < c.max_unfulfilled);
		c.unfulfilled_offsets.Add(off.value);
		
		Format fmt = src_value.GetFormat();
		ASSERT(fmt.IsValid());
		RTLOG("AtomBase::ForwardCustomer: sending order " << off.ToString() << " in format: " << fmt.ToString());
		p->SetFormat(fmt);
		
		//DUMP(c.plans.GetCount());
		ASSERT(c.plans.GetCount() == 1);
		Script::Plan& ep = c.plans[0];
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = ep.plan.GetCount()-1;
		
		WhenEnterCreatedEmptyPacket(p);
		WhenLeaveCreatedEmptyPacket();
		
		PacketTracker::Track(TrackerInfo("AtomBase::ForwardCustomer", __FILE__, __LINE__), *p);
		src_value.GetBuffer().Add(p);
		packets_forwarded++;
	}
	else {
		Value& sink_value = GetSink()->GetValue(sink_ch_i);
		
		PacketBuffer& buf = sink_value.GetBuffer();
		for (Packet& p : buf) {
			off32 off = p->GetOffset();
			c.unfulfilled_offsets.RemoveKey(off.value);
			RTLOG("AtomBase::ForwardCustomer: customer: removing fulfilled packet " << off.ToString());
		}
		buf.Clear();
		
		
		/*if (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled) {
			LOG("AtomBase::Forward: customer: error: too many unfulfilled packets");
			DUMPC(c.unfulfilled_offsets);
			while (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled)
				c.unfulfilled_offsets.Remove(0);
		}*/
	}
}

void AtomBase::ForwardSource(FwdScope& fwd) {
	const int sink_ch_i = 0;
	
	Forward(fwd);
	
	// From source
	InterfaceSinkRef iface_sink = GetSink();
	Value& sink_val = iface_sink->GetValue(sink_ch_i);
	SimpleBufferedValue* sink_buf_val;
	SimpleValue* sink_sval;
	PacketBuffer* sink_buf;
	if ((sink_buf_val = CastPtr<SimpleBufferedValue>(&sink_val))) {
		sink_buf = &sink_buf_val->GetBuffer();
	}
	else if ((sink_sval = CastPtr<SimpleValue>(&sink_val))) {
		sink_buf = &sink_sval->GetBuffer();
	}
	else TODO
	
	ForwardSourceBuffer(fwd, *sink_buf);
}


void AtomBase::ForwardSourceBuffer(FwdScope& fwd, PacketBuffer& sink_buf) {
	const int src_ch_i = 0;
	
	// To sink
	InterfaceSourceRef iface_src = GetSource();
	Value& val = iface_src->GetStream(src_ch_i).Get();
	SimpleValue* sval;
	SimpleBufferedValue* sbcal;
	PacketBuffer* pbuf;
	Format src_fmt = val.GetFormat();
	
	if ((sval = CastPtr<SimpleValue>(&val))) {
		pbuf = &sval->GetBuffer();
	}
	else if ((sbcal = CastPtr<SimpleBufferedValue>(&val))) {
		pbuf = &sbcal->GetBuffer();
	}
	else TODO
	
	RTLOG("AtomBase::ForwardSource: pre sink=" << sink_buf.GetCount() << ", src=" << val.GetBuffer().GetCount());
	Format fmt = val.GetFormat();
	
	while (sink_buf.GetCount() && !val.IsQueueFull()) {
		if (!IsReady(fmt.vd))
			break;
		Packet in = sink_buf.First();
		sink_buf.RemoveFirst();
		
		//int c = sink_buf.IsEmpty() ? 100 : 1;
		
		//for(int i = 0; i < c && !val.IsQueueFull(); i++) {
		off32 off = in->GetOffset();
		RTLOG("AtomBase::ForwardSource: play packet " << off.ToString());
		
		Packet to = CreatePacket(off);
		ASSERT(to->GetOffset() == off);
		to->SetFormat(src_fmt);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		if (1) {
			LoadPacket(in);
			
			WhenEnterStorePacket(*this, to);
			StorePacket(to);
			WhenLeaveStorePacket(to);
		}
		else {
			WhenEnterCreatedEmptyPacket(to);
			
			RTLOG("AtomBase::ForwardSource: sending packet in format: " << fmt.ToString());
			to->SetFormat(fmt);
			
			WhenLeaveCreatedEmptyPacket();
		}
		
		PacketTracker::Track(TrackerInfo("AtomBase::ForwardSource", __FILE__, __LINE__), *to);
		pbuf->Add(to);
		packets_forwarded++;
		//}
	}
	
	
	/* BREAKS OFFSET CHECKING!
	if (InterfaceSink::iface.val.type == ValCls::ORDER) {
		sink_buf->Clear();
		RTLOG("AtomBase::ForwardSource: cleared order-sink buffer");
	}*/
	
	{
		int src_total = 0;
		int src_ch_samples = 0;
		for (Packet& p : *pbuf) {
			src_total += p->GetSizeBytes();
			src_ch_samples += p->GetSizeChannelSamples();
		}
		RTLOG("AtomBase::ForwardSource: post sink=" << sink_buf.GetCount() << ", src=" << val.GetBuffer().GetCount() << " (total " << src_total << " bytes, " << src_ch_samples << " ch-samples)");
	}
	
}

void AtomBase::ForwardSink(FwdScope& fwd) {
	POPO(Pol::Serial::Atom::ConsumerFirst);
	POPO(Pol::Serial::Atom::SkipDulicateExtFwd);
	
	Forward(fwd);
	
	ForwardConsumed(fwd);
}

/*void AtomBase::ForwardConverter(FwdScope& fwd) {
	POPO(Pol::Serial::Atom::ConsumerFirst);
	POPO(Pol::Serial::Atom::SkipDulicateExtFwd);
	
		if (this->ext)
			this->ext->Forward(fwd);
	
	
	ForwardConsumed(fwd);
}*/


void AtomBase::ForwardSideSink(FwdScope& fwd) {
	POPO(Pol::Serial::Atom::ConsumerFirst);
	POPO(Pol::Serial::Atom::SkipDulicateExtFwd);
	
	const int sink_ch_i = 0;
	const int src_ch_i = 0;
	const int side_sink_ch_i = 1;
	
	Forward(fwd);

	Value& sink_value = GetSink()->GetValue(sink_ch_i);
	auto& sink_buf = sink_value.GetBuffer();
	Format sink_fmt = sink_value.GetFormat();
	
	Value& side_sink_value = GetSink()->GetValue(side_sink_ch_i);
	auto& side_sink_buf = side_sink_value.GetBuffer();
	Format side_sink_fmt = side_sink_value.GetFormat();
	
	Value& src_value = GetSource()->GetSourceValue(src_ch_i);
	auto& src_buf = src_value.GetBuffer();
	Format src_fmt = src_value.GetFormat();
	
	while (sink_buf.GetCount() && side_sink_buf.GetCount() && !src_value.IsQueueFull()) {
		Packet side_p = side_sink_buf.First();
		Packet sink_p = sink_buf.First();
		side_sink_buf.RemoveFirst();
		sink_buf.RemoveFirst();
		
		PacketTracker::StopTracking(TrackerInfo("AtomBase::ForwardSideSink", __FILE__, __LINE__), sink_p);
		off32 off = sink_p->GetOffset();
		sink_p.Clear();
		
		RTLOG("AtomBase::ForwardSideSink: forwarding side packet in format: " << side_p->GetFormat().ToString());
		
		if (side_p->GetFormat() == src_fmt) {
			side_p->SetOffset(off);
			src_buf.Add(side_p);
		}
		else {
			Packet dst = CreatePacket(off);
			if (Convert(side_p, dst))
				src_buf.Add(dst);
			else {
				RTLOG("AtomBase::ForwardSideSink: error: packet conversion failed");
			}
		}
	}
}

void AtomBase::ForwardSideSource(FwdScope& fwd) {
	POPO(Pol::Serial::Atom::ConsumerFirst);
	POPO(Pol::Serial::Atom::SkipDulicateExtFwd);
	
	const int sink_ch_i = 0;
	const int side_src_ch_i = 1;
	const int side_sink_ch_i = 1;
	
	Forward(fwd);
	
	Value& sink_value = GetSink()->GetValue(sink_ch_i);
	auto& sink_buf = sink_value.GetBuffer();
	
	InterfaceSinkRef side_sink_iface = side_sink_conn.First()->GetSink();
	Value& side_sink_value = side_sink_iface->GetValue(side_sink_ch_i);
	auto& side_sink_buf = side_sink_value.GetBuffer();
	Format side_sink_fmt = side_sink_value.GetFormat();
	
	while (sink_buf.GetCount() && !side_sink_value.IsQueueFull()) {
		Packet in = sink_buf.First();
		sink_buf.RemoveFirst();
		
		off32 o = in->GetOffset();
		
		RTLOG("AtomBase::ForwardSideSource: sending side-out packet(" << o.ToString() << ")");
		
		consumed_packets.Add(in);
		
		if (in->GetFormat() != side_sink_fmt) {
			Packet dst = CreatePacket(o);
			dst->SetFormat(side_sink_fmt);
			Convert(in, dst);
			in = dst;
		}
		
		side_sink_buf.Add(in);
	}
	
	
	ForwardConsumed(fwd);
}


void AtomBase::ForwardVoidSink(FwdScope& fwd) {
	const int src_ch_i = 0;
	const int sink_ch_i = 0;
	
	Value& src_value = GetSource()->GetSourceValue(src_ch_i);
	Stream& src_stream = GetSource()->GetStream(src_ch_i);
	Value& sink_value = GetSink()->GetValue(sink_ch_i);
	auto& sink_buf = sink_value.GetBuffer();
	auto& src_buf = src_value.GetBuffer();
	RealtimeSourceConfig& cfg = fwd.Cfg();
	AtomTypeCls type = GetType();
	
	lock.Enter();
	
	Index<dword> offs;
	for (auto& in : consumed_packets) {
		off32 o = in->GetOffset();
		if (offs.Find(o.value) >= 0)
			continue;
		offs.Add(o.value);
		
		Packet to = CreatePacket(o);
	
		Format fmt = GetDefaultFormat(type.iface.src());
		RTLOG("AtomBase::ForwardVoidSink: sending packet in format: " << fmt.ToString());
		to->SetFormat(fmt);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		StorePacket(to);
		
		PacketTracker::Track(TrackerInfo("AtomBase::ForwardVoidSink", __FILE__, __LINE__), *to);
		src_buf.Add(to);
	}
	
	lock.Leave();
}

bool AtomBase::ForwardMem(void* mem, size_t mem_size) {
	const int src_ch_i = 0;
	const int sink_ch_i = 0;
	
	Value& sink_value = GetSink()->GetValue(sink_ch_i);
	Value& src_value = GetSource()->GetSourceValue(src_ch_i);
	
	if (consumer.IsEmptySource())
		consumer.SetSource(sink_value.GetBuffer());
	
	if (mem) {
		Format fmt = sink_value.GetFormat();
		
		int size = fmt.GetFrameSize();
		if (size != mem_size) {
			RTLOG("AtomBase::ForwardMem: error: memsize mismatch (" << size << " != " << (int)mem_size << ")");
			return false;
		}
		
		int qsize = sink_value.GetQueueSize();
		if (qsize > 0 || consumer.HasLeftover()) {
			
			/*off32 begin_offset = buf.GetOffset();
			if (0) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: trying to consume " << begin_offset.ToString());
				RTLOG("BufferedAudioDeviceStream::SinkCallback: dumping");
				buf.Dump();
			}*/
			
			consumer.SetDestination(fmt, mem, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			int csize = consumer.GetLastMemoryBytes();
			int consumed_count = consumer.GetCount();
			if (csize != size) {
				RTLOG("AtomBase::ForwardMem: error: consumed " << csize << " (expected " << size << "), packets=" << consumed_count);
			}
			else {
				RTLOG("AtomBase::ForwardMem:  consumed " << csize << ", packets=" << consumed_count);
			}
			
			PacketsConsumed(consumer.consumed_packets);
			//PostContinueForward();
			
			
			/*off32 end_offset = consumer.GetOffset();
			off32 diff = off32::GetDifference(begin_offset, end_offset);
			if (diff) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed count=" << diff.ToString());
				buf.RemoveFirst(diff.value);
			}
			else if (consumer.HasLeftover()) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed packet partially");
			}
			else if (!consumer.HasLeftover()) {
				RTLOG("error: BufferedAudioDeviceStream::SinkCallback: device error");
			}*/
			return true;
		}
		else {
			#if DEBUG_RT_PIPE
			RTLOG("error: AtomBase::ForwardMem: got empty data");
			#endif
			
			memset(mem, 0, size);
		}
	}
	return false;
}


NAMESPACE_SERIAL_END
