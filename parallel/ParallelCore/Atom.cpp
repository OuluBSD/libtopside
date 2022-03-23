#include "Internal.h"


NAMESPACE_PARALLEL_BEGIN

// incomplete Script::Plan dtor in header
AtomBase::CustomerData::CustomerData() : cfg(gen) {}
AtomBase::CustomerData::~CustomerData() {}


AtomBase::AtomBase() {
	DBG_CONSTRUCT
}

AtomBase::~AtomBase() {
	DBG_DESTRUCT
}

bool AtomBase::ProcessPackets(PacketIO& io) {
	PacketIO::Sink& sink = io.sink[0];
	PacketIO::Source& src = io.src[0];
	sink.may_remove = true;
	src.from_sink_ch = 0;
	src.p = ReplyPacket(0, sink.p);
	src.p->AddRouteData(src.from_sink_ch);
	return true;
}

Machine& AtomBase::GetMachine() {
	return GetParent().GetMachine();
}

void AtomBase::UninitializeDeep() {
	Uninitialize();
	ClearSinkSource();
	UninitializeAtom();
}

void AtomBase::PostContinueForward() {
	if (last_cfg)
		GetMachine().Get<AtomSystem>()->AddOnce(*this, *last_cfg);
}

void AtomBase::SetPrimarySinkQueueSize(int i) {
	GetSink()->GetValue(0).SetMinQueueSize(i);
}

LoopRef AtomBase::GetLoop() {
	return GetParent().AsRefT();
}

Loop& AtomBase::GetParent() {
	return *((SP*)this)->GetParent().AsStatic<Loop>();
}

String AtomBase::ToString() const {
	return GetDynamicName();
}

void AtomBase::ForwardExchange(FwdScope& fwd) {
	ExchangeSourceProvider* src = CastPtr<ExchangeSourceProvider>(this);
	ASSERT(src);
	ExchangePointRef expt = src->GetExPt();
	//ASSERT(expt || GetType().role == AtomRole::DRIVER);
	if (expt) {
		fwd.AddNext(*expt);
	}
}

String AtomBase::GetInlineConnectionsString() const {
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

void AtomBase::SetInterface(const IfaceConnTuple& iface) {
	this->iface = iface;
}

bool AtomBase::LinkSideSink(AtomBaseRef sink, int local_ch_i, int other_ch_i) {
	ASSERT(sink);
	if (!sink)
		return false;
	
	AtomTypeCls type = sink->GetType();
	//DUMP(type);
	ASSERT(type.IsRolePipe());
	if (PassLinkSideSink(sink)) {
		RTLOG("AtomBase::LinkSideSink: local " << local_ch_i << " other " << other_ch_i << ": " << GetType().ToString());
		
		Exchange& ex = side_sink_conn.Add();
		ex.other = sink;
		ex.local_ch_i = local_ch_i;
		ex.other_ch_i = other_ch_i;
		RTLOG(HexStr((void*)this) << " connections: " << GetInlineConnectionsString());
		
		
		// as in AtomBase::LinkSideSink
		
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
		
		LOG("AtomBase::LinkSideSink: min=" << min_packets << ", max=" << max_packets);
		
		src_val.SetMinQueueSize(min_packets);
		src_val.SetMaxQueueSize(max_packets);
		sink_val.SetMinQueueSize(min_packets);
		sink_val.SetMaxQueueSize(max_packets);
		
		return true;
	}
	return false;
}

bool AtomBase::LinkSideSource(AtomBaseRef src, int local_ch_i, int other_ch_i) {
	//side_sink = -1; // SetSideSink(-1)
	ASSERT(src);
	if (!src)
		return false;
	
	AtomTypeCls type = src->GetType();
	//DUMP(type);
	ASSERT(type.IsRolePipe());
	if (PassLinkSideSource(src)) {
		Exchange& ex = side_src_conn.Add();
		ex.other = src;
		ex.local_ch_i = local_ch_i;
		ex.other_ch_i = other_ch_i;
		RTLOG(HexStr((void*)this) << " connections: " << GetInlineConnectionsString());
		return true;
	}
	return false;
}

bool AtomBase::IsPacketStuck() {
	AtomTypeCls type = GetType();
	InterfaceSinkRef sink_iface = GetSink();
	int sink_c = sink_iface->GetSinkCount() - type.user_sink_count;
	for(int i = 0; i < sink_c; i++) {
		Value& val = sink_iface->GetValue(i);
		if (val.GetQueueSize() == 0) {
			RTLOG("AtomBase::IsPacketStuck: true: sink #" << i << " empty");
			return true;
		}
	}
	
	InterfaceSourceRef src_iface = GetSource();
	int src_c = src_iface->GetSourceCount() - type.user_src_count;
	for(int i = 0; i < src_c; i++) {
		Value& val = src_iface->GetSourceValue(i);
		if (val.IsQueueFull()) {
			RTLOG("AtomBase::IsPacketStuck: true: src #" << i << " full");
			return true;
		}
	}
	
	return false;
}

bool AtomBase::NegotiateSourceFormat(int src_ch, const Format& fmt) {
	if (src_ch > 0) {
		Exchange* e = 0;
		for (Exchange& ex : side_sink_conn)
			if (ex.local_ch_i == src_ch)
				e = &ex;
		if (!e) {
			LOG("AtomBase::NegotiateSourceFormat: error: exchange not found");
			return false;
		}
		
		if (!e->other->NegotiateSinkFormat(e->other_ch_i, fmt)) {
			LOG("AtomBase::NegotiateSourceFormat: error: audio format negotiation failed");
			return false;
		}
	}
	else {
		DUMP(*prim_link_sink);
		if (!prim_link_sink->NegotiateSinkFormat(0, fmt)) {
			LOG("AtomBase::NegotiateSourceFormat: error: audio format negotiation failed");
			return false;
		}
	}
	Value& src = GetSource()->GetSourceValue(src_ch);
	src.SetFormat(fmt);
	return true;
}








void AtomMap::Dump() {
	auto iter = AtomMapBase::begin();
	for(int i = 0; iter; ++iter, ++i) {
		LOG(i << ": " <<
			iter.value().GetDynamicName() << ": \"" <<
			iter.value().ToString() << "\"");
	}
}

void AtomMap::ReturnAtom(AtomStore& s, AtomBase* c) {
	s.ReturnAtom(c);
}




NAMESPACE_PARALLEL_END
