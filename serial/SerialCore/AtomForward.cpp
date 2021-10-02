#include "Internal.h"

NAMESPACE_SERIAL_BEGIN


int AtomBase::GetSinkPacketCount() {
	InterfaceSinkRef sink_iface = GetSink();
	int sink_count = sink_iface->GetSinkCount();
	int c = 0;
	for(int i = 0; i < sink_count; i++)
		c += sink_iface->GetValue(i).GetQueueSize();
	return c;
}

int AtomBase::GetSourcePacketCount() {
	InterfaceSourceRef src_iface = GetSource();
	int src_count = src_iface->GetSourceCount();
	int c = 0;
	for(int i = 0; i < src_count; i++)
		c += src_iface->GetSourceValue(i).GetQueueSize();
	return c;
}

void AtomBase::ForwardAtom(FwdScope& fwd) {
	RTLOG("AtomBase::ForwardAtom");
	
	fwd_lock.Enter();
	
	last_cfg = &fwd.Cfg();
	
	#ifdef flagDEBUG
	int ch_i = 0;
	int pre_sink_packet_count = GetSinkPacketCount();
	int pre_src_packet_count = GetSourcePacketCount();
	int pre_consumed = consumed_packets.GetCount();
	int pre_consumed_partial = IsConsumedPartialPacket();
	int pre_total =
		  pre_sink_packet_count
		  + pre_src_packet_count
		  + (pre_consumed - pre_consumed_partial); // partial packet stays in sink while fraction is consumed
	#endif
	
	
	ForwardPipe(fwd);
	ForwardSideConnections();
	
	
	#ifdef flagDEBUG
	AtomTypeCls type = GetType();
	int post_sink_packet_count = GetSinkPacketCount();
	int post_src_packet_count = GetSourcePacketCount();
	int post_consumed = consumed_packets.GetCount();
	int post_consumed_partial = IsConsumedPartialPacket();
	int post_total =
		  post_sink_packet_count
		+ post_src_packet_count
		+ skipped_fwd_count
		+ (post_consumed - post_consumed_partial);
	bool consumed_only_partial =
		pre_sink_packet_count == post_sink_packet_count &&
		pre_src_packet_count == post_src_packet_count &&
		pre_consumed == 0 && post_consumed == 0 &&
		pre_consumed_partial == 1 && post_consumed_partial == 0;
	if (type.role != CUSTOMER) {
		bool is_buffered_consumer = type.iface.content.val == ValCls::AUDIO; // todo: other value formats
		ASSERT_(
			pre_total == post_total ||
			dbg_async_race ||
			consumed_only_partial ||
			is_buffered_consumer,
			"Atom lost packets. Maybe alt class did not call PacketConsumed(...) for the packet?");
		/*
		On fail:
			- have you implemented "IsConsumedPartialPacket() override" while using Value?
		*/
	}
	#endif
	
	fwd_lock.Leave();
}

void AtomBase::ForwardDriver(FwdScope& fwd) {
	Forward(fwd);
}

void AtomBase::ForwardPipe(FwdScope& fwd) {
	POPO(Pol::Serial::Atom::ConsumerFirst);
	POPO(Pol::Serial::Atom::SkipDulicateExtFwd);
	
	this->skipped_fwd_count = 0;
	
	/*const int sink_ch_i = 0;
	const int side_src_ch_i = 1;
	const int side_sink_ch_i = 1;*/
	
	AtomTypeCls type = GetType();
	
	Forward(fwd);
	
	InterfaceSinkRef sink_iface = GetSink();
	InterfaceSourceRef src_iface = GetSource();
	int sink_ch_count = sink_iface->GetSinkCount();
	int src_ch_count = src_iface->GetSourceCount();
	ASSERT(src_ch_count);
	if (!src_ch_count) return;
	
	/*Value& sink_value = sink_iface->GetValue(sink_ch_i);
	auto& sink_buf = sink_value.GetBuffer();*/
	
	//Value& main_src_value = src_iface->GetSourceValue(0);
	
	/*InterfaceSinkRef side_sink_iface = side_sink_conn.First()->GetSink();
	Value& side_sink_value = side_sink_iface->GetValue(side_sink_ch_i);
	auto& side_sink_buf = side_sink_value.GetBuffer();
	Format side_sink_fmt = side_sink_value.GetFormat();*/
	
	bool is_forwarded = false;
	
	//while (sink_buf.GetCount()) {
	while (1) {
		if (!IsReady(type.iface.content))
			break;
		
		Vector<int> problem_chs;
		bool sink_all = true;
		for(int i = 0; i < sink_ch_count; i++) {
			Value& sink_value = sink_iface->GetValue(i);
			int sz = sink_value.GetQueueSize();
			if (!sz) {
				problem_chs << i;
				sink_all = false;
			}
		}
		if (!sink_all) {
			RTLOG("AtomBase::ForwardPipe: skipping, some sinks are empty: " << Join(problem_chs, ", "));
			break;
		}
		
		bool src_full = false;
		for(int i = 0; i < src_ch_count; i++) {
			Value& src_value = src_iface->GetSourceValue(i);
			if (src_value.IsQueueFull()) {
				problem_chs << i;
				src_full = true;
			}
		}
		if (src_full) {
			RTLOG("AtomBase::ForwardPipe: skipping, some sources are full: " << Join(problem_chs, ", "));
			break;
		}
		
		for (Exchange& ex : side_sink_conn) {
			Value& sink_val = ex.other->GetSink()->GetValue(ex.other_ch_i);
			if (sink_val.IsQueueFull()) {
				problem_chs << ex.local_ch_i;
				src_full = true;
				break;
			}
		}
		if (src_full) {
			RTLOG("AtomBase::ForwardPipe: skipping, some side sources are full: " << Join(problem_chs, ", "));
			break;
		}
		
		for(int i = sink_ch_count-1; i >= 0; i--) {
			Value& sink_value = sink_iface->GetValue(i);
			PacketBuffer& sink_buf = sink_value.GetBuffer();
			Packet in = sink_buf.First();
			sink_buf.RemoveFirst();
			off32 off = in->GetOffset();
			Format sink_fmt = in->GetFormat();
			
			if (!LoadPacket(i, in)) {
				RTLOG("AtomBase::ForwardPipe: skipping sink #" << i << " packet(" << off.ToString() << "), " << sink_fmt.ToString());
				continue;
			}
			else {
				RTLOG("AtomBase::ForwardPipe: receiving sink #" << i << " packet(" << off.ToString() << "), " << sink_fmt.ToString());
			}
			
			//consumed_packets.Add(in);
			packets_forwarded++;
			
			for(int j = src_ch_count-1; j >= 0; j--) {
				Value& src_val = src_iface->GetSourceValue(j);
				PacketBuffer& src_buf = src_val.GetBuffer();
				Format src_fmt = src_val.GetFormat();
				
				if (i > 0 && j == 0 /*&& src_fmt.vd.val == ValCls::RECEIPT*/) {
					skipped_fwd_count++;
					RTLOG("AtomBase::ForwardPipe: skipping side sink #" << i << ", src #" << j);
					continue;
				}
				
				RTLOG("AtomBase::ForwardPipe: sending sink #" << i << ", src #" << j << " packet(" << off.ToString() << "), " << src_fmt.ToString());
				
				if (1) {
					Packet to = CreatePacket(off);
					to->SetFormat(src_fmt);
					
					InternalPacketData& data = to->template SetData<InternalPacketData>();
					
					WhenEnterStorePacket(*this, to);
					StorePacket(i, j, to);
					WhenLeaveStorePacket(to);
					
					if (to) {
						PacketTracker::Checkpoint(TrackerInfo("AtomBase::ForwardSource", __FILE__, __LINE__), *to);
						src_buf.Add(to);
						is_forwarded = true;
					}
					else {
						RTLOG("AtomBase::ForwardPipe: error: StorePacket returned empty package");
						ASSERT(0);
					}
				}
				else {
					TODO
					/*if (in->GetFormat() != side_sink_fmt) {
						Packet dst = CreatePacket(off);
						dst->SetFormat(side_sink_fmt);
						Convert(in, dst);
						in = dst;
					}*/
				}
				
				//side_sink_buf.Add(in);
			}
		}
	}
	
	
	if (is_forwarded) {
		if (fwd.IsOnce())
			PostContinueForward();
	}
	else
		fwd.Break();
	
	//ForwardConsumed(fwd);
}

void AtomBase::ForwardSideConnections() {
	InterfaceSourceRef src_iface = GetSource();
	
	for (Exchange& ex : side_sink_conn) {
		Value& src_val = src_iface->GetSourceValue(ex.local_ch_i);
		PacketBuffer& src_buf = src_val.GetBuffer();
		if (src_buf.GetCount()) {
			InterfaceSinkRef sink_iface = ex.other->GetSink();
			Value& sink_val = sink_iface->GetValue(ex.other_ch_i);
			ASSERT(!sink_val.IsQueueFull());
			PacketBuffer& sink_buf = sink_val.GetBuffer();
			sink_buf.PickAppend(src_buf);
			ASSERT(src_buf.IsEmpty());
		}
	}
}

void AtomBase::ForwardAsync() {
	RTLOG("AtomBase::ForwardAsync " << HexStr(last_cfg));
	
	if (!last_cfg)
		return;
	
	FwdScope fwd(this, *last_cfg);
	fwd.SetOnce();
	fwd.Forward();
	
}

NAMESPACE_SERIAL_END
