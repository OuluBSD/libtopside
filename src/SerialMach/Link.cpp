#include "SerialMach.h"



NAMESPACE_SERIAL_BEGIN


LinkBase::LinkBase() {
	DBG_CONSTRUCT
}

LinkBase::~LinkBase() {
	DBG_DESTRUCT
}

Parallel::AtomBase* LinkBase::GetAtom() {
	return atom;
}

Parallel::Machine& LinkBase::GetMachine() {
	return atom->GetMachine();
}

String LinkBase::ToString() const {
	return GetDynamicName();
}

AtomTypeCls LinkBase::GetAtomType() const {
	return atom->GetType();
}

LinkTypeCls LinkBase::GetLinkType() const {
	TODO
}

ISourceRef LinkBase::GetSource() {
	return atom->GetSource();
}

ISinkRef LinkBase::GetSink() {
	return atom->GetSink();
}

void LinkBase::AddLinkToUpdateList() {
	LinkBase::GetMachine().template Get<LinkSystem>()->AddUpdated(LinkBase::AsRefT());
}

void LinkBase::RemoveLinkFromUpdateList() {
	LinkBase::GetMachine().template Get<LinkSystem>()->RemoveUpdated(LinkBase::AsRefT());
}

int LinkBase::GetId() const {
	return id;
}

void LinkBase::ForwardAsync() {
	RTLOG("LinkBase::ForwardAsync " << HexStr(last_cfg));
	
	if (!last_cfg)
		return;
	
	FwdScope fwd(this, *last_cfg);
	fwd.SetOnce();
	fwd.Forward();
}

bool LinkBase::NegotiateSourceFormat(int src_ch, const Format& fmt) {
	if (src_ch > 0) {
		Exchange* e = 0;
		for (Exchange& ex : side_sink_conn)
			if (ex.local_ch_i == src_ch)
				e = &ex;
		if (!e) {
			//int dbg_i = 0; for (auto& e : side_sink_conn) {LOG(dbg_i++ << ": " << e.ToString());}
			LOG("LinkBase::NegotiateSourceFormat: error: exchange not found");
			return false;
		}
		
		if (!e->other->NegotiateSinkFormat(e->other_ch_i, fmt, false)) {
			LOG("LinkBase::NegotiateSourceFormat: error: format negotiation failed");
			return false;
		}
	}
	else {
		DUMP(*prim_link_sink);
		if (!prim_link_sink->NegotiateSinkFormat(0, fmt, false)) {
			LOG("LinkBase::NegotiateSourceFormat: error: format negotiation failed");
			return false;
		}
	}
	Value& src = GetSource()->GetSourceValue(src_ch);
	src.SetFormat(fmt);
	
	
	return true;
}

void LinkBase::UpdateLinkedExchangeFormats(int src_ch, const Format& fmt) {
	
	for (Exchange& e : side_sink_conn) {
		if (e.local_ch_i == src_ch) {
			ISinkRef sink = e.other->GetSink();
			Value& val = sink->GetValue(e.other_ch_i);
			val.SetFormat(fmt);
		}
	}
	
	ISinkRef sink = prim_link_sink->GetSink();
	Value& val = sink->GetValue(0);
	val.SetFormat(fmt);
	
}

bool LinkBase::NegotiateSinkFormat(int sink_ch, const Format& fmt, bool chk_other) {
	if (!chk_other) {
		if (!atom->NegotiateSinkFormat(*this, sink_ch, fmt))
			return false;
		return true;
	}
	
	// Negotiation is started from the linked source (not this link)
	if (sink_ch > 0) {
		Exchange* e = 0;
		for (Exchange& ex : side_src_conn)
			if (ex.local_ch_i == sink_ch)
				e = &ex;
		if (!e) {
			LOG("LinkBase::NegotiateSinkFormat: error: exchange not found");
			return false;
		}
		
		if (!e->other->NegotiateSourceFormat(e->other_ch_i, fmt)) {
			LOG("LinkBase::NegotiateSinkFormat: error: format negotiation failed");
			return false;
		}
	}
	else {
		DUMP(*prim_link_sink);
		if (!prim_link_sink->NegotiateSourceFormat(0, fmt)) {
			LOG("LinkBase::NegotiateSinkFormat: error: format negotiation failed");
			return false;
		}
	}
	
	return true;
}

Packet LinkBase::InitialPacket(int src_ch, off32 off) {
	Format src_fmt = GetSource()->GetSourceValue(src_ch).GetFormat();
	Packet to = CreatePacket(off);
	to->SetFormat(src_fmt);
	InternalPacketData& data = to->template SetData<InternalPacketData>();
	return to;
}

Packet LinkBase::ReplyPacket(int src_ch, const Packet& in) {
	Format src_fmt = GetSource()->GetSourceValue(src_ch).GetFormat();
	off32 off = in->GetOffset();
	Packet to = CreatePacket(off);
	to->SetFormat(src_fmt);
	#if HAVE_PACKETTRACKER
	to->CopyRouteData(*in);
	#endif
	InternalPacketData& data = to->template SetData<InternalPacketData>();
	PacketTracker_Track("LinkBase::ReplyPacket", __FILE__, __LINE__, *to);
	return to;
}

Packet LinkBase::ReplyPacket(int src_ch, const Packet& in, Packet content) {
	Format content_fmt = content->GetFormat();
	Format src_fmt = GetSource()->GetSourceValue(src_ch).GetFormat();
	off32 off = in->GetOffset();
	Packet to;
	if (content_fmt.IsCopyCompatible(src_fmt)) {
		to = content;
		to->SetOffset(off);
	}
	else {
		Packet to = CreatePacket(off);
		to->SetFormat(src_fmt);
		Convert(content, to);
	}
	#if HAVE_PACKETTRACKER
	to->CopyRouteData(*in);
	#endif
	PacketTracker_Track("LinkBase::ReplyPacket", __FILE__, __LINE__, *to);
	return to;
}

void LinkBase::SetPrimarySinkQueueSize(int i) {
	GetSink()->GetValue(0).SetMinQueueSize(i);
}

String LinkBase::GetInlineConnectionsString() const {
	String s;
	s << "sink(";
	int i = 0;
	for (Exchange& ex : side_sink_conn) {
		if (i++ > 0) s << ", ";
		s << HexStr(&*ex.other);
	}
	s << "), src(";
	i = 0;
	for (Exchange& ex : side_src_conn) {
		if (i++ > 0) s << ", ";
		s << HexStr(&*ex.other);
	}
	s << ")";
	return s;
}

bool LinkBase::LinkSideSink(LinkBaseRef sink, int local_ch_i, int other_ch_i) {
	ASSERT(sink);
	if (!sink)
		return false;
	
	AtomTypeCls type = sink->GetAtomType();
	ASSERT(type.IsRolePipe());
	if (PassLinkSideSink(sink) && sink->PassLinkSideSource(AsRefT())) {
		RTLOG("LinkBase::LinkSideSink: local " << local_ch_i << " other " << other_ch_i << ": " << GetLinkType().ToString());
		
		{
			Exchange& ex = side_sink_conn.Add();
			ex.other = sink;
			ex.local_ch_i = local_ch_i;
			ex.other_ch_i = other_ch_i;
		}
		
		{
			Exchange& ex = sink->side_src_conn.Add();
			ex.other = AsRefT();
			ex.local_ch_i = other_ch_i;
			ex.other_ch_i = local_ch_i;
		}
		
		// as in LinkBase::LinkSideSink
		
		InterfaceSourceRef src_iface = GetSource();
		InterfaceSinkRef sink_iface = sink->GetSink();
		Value& src_val = src_iface->GetSourceValue(local_ch_i);
		Value& sink_val = sink_iface->GetValue(other_ch_i);
		int src_max_packets = src_val.GetMaxPackets();
		int src_min_packets = src_val.GetMinPackets();
		int sink_max_packets = sink_val.GetMaxPackets();
		int sink_min_packets = sink_val.GetMinPackets();
		int max_packets = min(sink_max_packets, src_max_packets);
		int min_packets = max(sink_min_packets, src_min_packets);
		
		if (min_packets > max_packets) {
			max_packets = min_packets;
		}
		
		LOG("LinkBase::LinkSideSink: min=" << min_packets << ", max=" << max_packets);
		
		src_val.SetMinQueueSize(min_packets);
		src_val.SetMaxQueueSize(max_packets);
		sink_val.SetMinQueueSize(min_packets);
		sink_val.SetMaxQueueSize(max_packets);
		
		return true;
	}
	else {
		LOG("LinkBase::LinkSideSink: error: failed to like side-channel");
	}
	
	return false;
}

String LinkBase::Exchange::ToString() const {
	String s;
	s << other.ToString() << ", local=" << local_ch_i << ", other=" << other_ch_i;
	return s;
}


bool Serial_Link_ForwardAsyncMem(Link* l, byte* data, int size) {
	ASSERT(l);
	return l ? l->ForwardAsyncMem(data, size) : 0;
}

void Serial_Link_PostContinueForward(Link* l) {
	ASSERT(l);
	if (l)
		l->PostContinueForward();
}



NAMESPACE_SERIAL_END
