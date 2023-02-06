#include "SerialMach.h"


NAMESPACE_SERIAL_BEGIN


void LinkBase::ForwardAtom(FwdScope& fwd) {
	RTLOG("LinkBase::ForwardAtom: " << GetDynamicName());
	
	atom->fwd_lock.Enter();
	last_cfg = &fwd.Cfg();
	
	ForwardPipe(fwd);
	
	atom->fwd_lock.Leave();
}

void LinkBase::Forward(FwdScope& fwd) {
	last_cfg = &fwd.Cfg();
}

void LinkBase::ForwardPipe(FwdScope& fwd) {
	#if 0
	POPO(Pol::Serial::Atom::ConsumerFirst);
	POPO(Pol::Serial::Atom::SkipDulicateExtFwd);
	#endif
	
	this->skipped_fwd_count = 0;
	
	AtomTypeCls type = atom->GetType();
	
	Forward(fwd);
	
	InterfaceSinkRef sink_iface = GetSink();
	InterfaceSourceRef src_iface = GetSource();
	int sink_ch_count = sink_iface->GetSinkCount();
	int src_ch_count = src_iface->GetSourceCount();
	ASSERT(src_ch_count);
	if (!src_ch_count) return;
	
	bool is_forwarded = false;
	
	while (1) {
		static thread_local PacketIO io;
		io.sinks.SetCount(sink_ch_count);
		io.srcs.SetCount(src_ch_count);
		io.Reset();
		for(int sink_ch = 0; sink_ch < sink_ch_count; sink_ch++) {
			if (sink_iface->GetValue(sink_ch).GetQueueSize() > 0) {
				io.sinks[sink_ch].filled = true;
				io.active_sink_mask |= 1 << sink_ch;
				io.nonempty_sinks++;
			}
		}
		
		if (io.active_sink_mask == 0) {
			RTLOG("LinkBase::ForwardPipe: skipping, all sinks are empty");
			break;
		}
		
		if (!(io.active_sink_mask & 1)) {
			RTLOG("LinkBase::ForwardPipe: skipping, primary sink is empty");
			break;
		}
		
		if (IsPrimarySourceFull()) {
			RTLOG("LinkBase::ForwardPipe: skipping, primary source is full");
			break;
		}
		
		
		// Set some channels directly (only primary channel currently)
		for (int src_ch = 0; src_ch < 1; src_ch++) {
			PacketIO::Source& iface = io.srcs[src_ch];
			iface.val = &src_iface->GetSourceValue(src_ch);
		}
		// Set side channels using far link
		for (Exchange& ex : side_sink_conn) {
			ASSERT(ex.local_ch_i > 0 && ex.local_ch_i < io.srcs.GetCount());
			PacketIO::Source& iface = io.srcs[ex.local_ch_i];
			InterfaceSinkRef sink_iface = ex.other->GetSink();
			iface.val = &sink_iface->GetValue(ex.other_ch_i);
		}
		// Make src full mask
		io.full_src_mask = 0;
		for (int src_ch = 0; src_ch < src_ch_count; src_ch++) {
			PacketIO::Source& iface = io.srcs[src_ch];
			if (!iface.val) {
				ASSERT(type.iface.src[src_ch].is_opt);
			}
			else if (iface.val->IsQueueFull()) {
				iface.is_full = true;
				io.full_src_mask |= (1 << src_ch);
			}
			
			//RTLOG("LinkBase::ForwardPipe: " << (iface.val ? "has val" : "no val") << (iface.is_full ? ", is full" : ", not full"));
		}
		
		
		if (!IsReady(io))
			break;
		
		
		for (int sink_ch = 0; sink_ch < sink_ch_count; sink_ch++) {
			PacketIO::Sink& iface = io.sinks[sink_ch];
			if (!iface.filled)
				continue;
			Value& sink_value = sink_iface->GetValue(sink_ch);
			PacketBuffer& sink_buf = sink_value.GetBuffer();
			ASSERT(!sink_buf.IsEmpty());
			iface.val = &sink_value;
			iface.buf = &sink_buf;
			
			iface.buf->EnterRead();
			iface.p = sink_buf.First();
			iface.may_remove = false;
			iface.buf->LeaveRead();
		}
		
		
		WhenEnterProcessPackets(*this, io);
		if (!ProcessPackets(io)) {
			RTLOG("LinkBase::ForwardPipe: failed to process packets");
		}
		WhenLeaveProcessPackets(*this, io);
		
		
		for (int sink_ch = 0; sink_ch < sink_ch_count; sink_ch++) {
			PacketIO::Sink& iface = io.sinks[sink_ch];
			if (iface.filled && iface.may_remove) {
				iface.buf->EnterWrite();
				iface.buf->RemoveFirst();
				iface.buf->LeaveWrite();
			}
			else if (iface.filled) {
				RTLOG("LinkBase::ForwardPipe: warning: NOT removing first in sink #" << sink_ch << " " << HexStr(iface.buf));
				ASSERT_(sink_ch > 0, "LinkBase::ForwardPipe: NOT removing first in primary sink");
			}
		}
		
		
		bool iter_forwarded = false;
		
		for (int src_ch = 0; src_ch < src_ch_count; src_ch++) {
			PacketIO::Source& iface = io.srcs[src_ch];
			Packet& sent = iface.p;
			if (sent) {
				ASSERT(iface.val);
				iter_forwarded = true;
				
				ASSERT(iface.from_sink_ch >= 0);
				Value& src_val = src_iface->GetSourceValue(src_ch);
				RTLOG("LinkBase::ForwardPipe: packet from sink #" << iface.from_sink_ch << " to #" << src_ch << " src_val=" << HexStr(&src_val) << " sink_val=" << HexStr(iface.val));
				ASSERT(!src_val.IsQueueFull());
				
				PacketBuffer& src_buf = src_val.GetBuffer();
				PacketTracker_Checkpoint("LinkBase::ForwardSource", __FILE__, __LINE__, *sent);
				#if HAVE_PACKETTRACKER
				sent->AddRouteData(iface.from_sink_ch);
				#endif
				src_buf.EnterWrite();
				src_buf.Add(sent);
				src_buf.LeaveWrite();
				is_forwarded = true;
			}
			else if (src_ch == 0) {
				Panic("internal error: no primary packet forwarded per iteration");
				return;
			}
		}
		
		
		if (iter_forwarded)
			ForwardSideConnections();
		
	}
	
	
	if (is_forwarded) {
		if (fwd.IsOnce())
			PostContinueForward();
	}
	else
		fwd.Break();
	
	
	
}

void LinkBase::PostContinueForward() {
	if (last_cfg)
		GetMachine().Get<LinkSystem>()->AddOnce(*this, *last_cfg);
}

void LinkBase::ForwardExchange(FwdScope& fwd) {
	ExchangeSourceProvider* src = CastPtr<ExchangeSourceProvider>(atom);
	ASSERT(src);
	ExchangePointRef expt = src->GetExPt();
	if (expt) {
		fwd.AddNext(*expt);
	}
}

String LinkBase::GetSecondaryName() {
	return atom ? atom->GetDynamicName() : "";
}

void* LinkBase::GetSecondaryPtr() {
	return atom ? &atom->GetRTTI() : 0;
}

bool LinkBase::IsPacketStuck() {
	AtomTypeCls type = GetAtomType();
	InterfaceSinkRef sink_iface = GetSink();
	int sink_c = sink_iface->GetSinkCount();
	for(int i = 0; i < sink_c; i++) {
		if (type.iface.sink[i].is_opt)
			continue;
		Value& val = sink_iface->GetValue(i);
		if (val.GetQueueSize() == 0) {
			RTLOG("LinkBase::IsPacketStuck: true: sink #" << i << " empty");
			return true;
		}
	}
	
	InterfaceSourceRef src_iface = GetSource();
	int src_c = src_iface->GetSourceCount();
	for(int i = 0; i < src_c; i++) {
		if (type.iface.src[i].is_opt)
			continue;
		Value& val = src_iface->GetSourceValue(i);
		if (val.IsQueueFull()) {
			RTLOG("LinkBase::IsPacketStuck: true: src #" << i << " full");
			return true;
		}
	}
	
	return false;
}

int LinkBase::GetSinkPacketCount() {
	InterfaceSinkRef sink_iface = GetSink();
	int sink_count = sink_iface->GetSinkCount();
	int c = 0;
	for(int i = 0; i < sink_count; i++)
		c += sink_iface->GetValue(i).GetQueueSize();
	return c;
}

int LinkBase::GetSourcePacketCount() {
	InterfaceSourceRef src_iface = GetSource();
	int src_count = src_iface->GetSourceCount();
	int c = 0;
	for(int i = 0; i < src_count; i++)
		c += src_iface->GetSourceValue(i).GetQueueSize();
	return c;
}

bool LinkBase::IsAllSideSourcesFull(const Vector<int>& src_chs) {
	auto it = src_chs.Begin();
	auto end = src_chs.End();
	while (it != end) {
		for (Exchange& ex : side_sink_conn) {
			int src_ch = *it;
			if (src_ch == 0) {
				if (!IsPrimarySourceFull())
					return false;
				if (++it == end)
					break;
			}
			if (src_ch == ex.local_ch_i) {
				InterfaceSinkRef sink_iface = ex.other->GetSink();
				Value& sink_val = sink_iface->GetValue(ex.other_ch_i);
				if (!sink_val.IsQueueFull())
					return false;
				if (++it == end)
					break;
			}
		}
	}
	return true;
}

bool LinkBase::IsAnySideSourceFull(const Vector<int>& src_chs) {
	auto it = src_chs.Begin();
	auto end = src_chs.End();
	while (it != end) {
		for (Exchange& ex : side_sink_conn) {
			int src_ch = *it;
			if (src_ch == 0) {
				if (IsPrimarySourceFull())
					return true;
				if (++it == end)
					break;
			}
			if (src_ch == ex.local_ch_i) {
				InterfaceSinkRef sink_iface = ex.other->GetSink();
				Value& sink_val = sink_iface->GetValue(ex.other_ch_i);
				if (sink_val.IsQueueFull())
					return true;
				if (++it == end)
					break;
			}
		}
	}
	return false;
}

bool LinkBase::IsPrimarySourceFull() {
	InterfaceSourceRef src_iface = GetSource();
	Value& src_val = src_iface->GetSourceValue(0);
	return src_val.IsQueueFull();
}

void LinkBase::ForwardSideConnections() {
	InterfaceSourceRef src_iface = GetSource();
	
	for (Exchange& ex : side_sink_conn) {
		ASSERT(ex.local_ch_i > 0 && ex.other_ch_i > 0);
		Value& src_val = src_iface->GetSourceValue(ex.local_ch_i);
		PacketBuffer& src_buf = src_val.GetBuffer();
		src_buf.EnterWrite();
		if (src_buf.GetCount()) {
			InterfaceSinkRef sink_iface = ex.other->GetSink();
			Value& sink_val = sink_iface->GetValue(ex.other_ch_i);
			RTLOG("LinkBase::ForwardSideConnections: #" << ex.local_ch_i << " src_val=" << HexStr(&src_val) << " sink_val=" << HexStr(&sink_val));
			if (sink_val.IsQueueFull())
				Panic("internal error: Atom sent packet to already full source interface. Improve custom atom IsReady function to prevent this.");
			PacketBuffer& sink_buf = sink_val.GetBuffer();
			
			#if 1
			Format sink_fmt = sink_val.GetFormat();
			while (src_buf.GetCount()) {
				Packet p = src_buf.First();
				src_buf.RemoveFirst();
				Packet to_p;
				
				Format in_fmt = p->GetFormat();
				if (sink_fmt.IsCopyCompatible(in_fmt)) {
					to_p = p;
				}
				else {
					to_p = CreatePacket(p->GetOffset());
					to_p->SetFormat(sink_fmt);
					#if HAVE_PACKETTRACKER
					to_p->CopyRouteData(*p);
					#endif
					if (Convert(p, to_p)) {
						RTLOG("LinkBase::ForwardSideConnections: converted packet: " << to_p->ToString());
					}
					else {
						RTLOG("LinkBase::ForwardSideConnections: packet conversion failed from " << to_p->ToString());
						to_p.Clear();
						break;
					}
				}
				
				sink_buf.EnterWrite();
				sink_buf.Add(to_p);
				sink_buf.LeaveWrite();
			}
			#else
			sink_buf.PickAppend(src_buf);
			ASSERT(src_buf.IsEmpty());
			#endif
		}
		src_buf.LeaveWrite();
	}
}



NAMESPACE_SERIAL_END
