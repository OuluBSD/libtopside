#include "Internal.h"


NAMESPACE_SERIAL_BEGIN

// incomplete Script::Plan dtor in header
AtomBase::CustomerData::CustomerData() : cfg(gen) {}
AtomBase::CustomerData::~CustomerData() {}


AtomBase::AtomBase() {
	DBG_CONSTRUCT
}

AtomBase::~AtomBase() {
	DBG_DESTRUCT
}

Machine& AtomBase::GetMachine() {
	return GetParent()->GetMachine();
}

void AtomBase::UninitializeDeep() {
	AltUninitialize();
	Uninitialize();
	ClearSinkSource();
	UninitializeAtom();
}

void AtomBase::PostContinueForward() {
	ASSERT(last_cfg);
	if (last_cfg)
		GetMachine().Get<AtomSystem>()->AddOnce(*this, *last_cfg);
}

LoopRef AtomBase::GetLoop() {
	return GetParent()->AsRefT();
}

String AtomBase::ToString() const {
	return GetDynamicName();
}

void AtomBase::ForwardExchange(FwdScope& fwd) {
	ExchangeSourceProvider* src = CastPtr<ExchangeSourceProvider>(this);
	ASSERT(src);
	ExchangePointRef expt = src->GetExPt();
	ASSERT(expt || GetType().role == AtomRole::DRIVER);
	if (expt) {
		fwd.AddNext(*expt);
	}
}

void AtomBase::ForwardConsumed(FwdScope& fwd) {
	int src_ch_i = 0;
	int sink_ch_i = 0;
	
	Value& src_value = GetSource()->GetSourceValue(src_ch_i);
	Value& sink_value = GetSink()->GetValue(sink_ch_i);
	auto& sink_buf = sink_value.GetBuffer();
	auto& src_buf = src_value.GetBuffer();
	Format src_fmt = src_value.GetFormat();
	AtomTypeCls type = GetType();
	
	RealtimeSourceConfig& cfg = fwd.Cfg();
	
	lock.Enter();
	LinkedList<Packet> consumed_packets;
	MemSwap(this->consumed_packets, consumed_packets);
	lock.Leave();
	
	Index<dword> offs;
	for (auto& in : consumed_packets) {
		off32 off = in->GetOffset();
		if (offs.Find(off.value) >= 0) {
			// receipt is already sent
			continue;
		}
		offs.Add(off.value);
		
		RTLOG("AtomBase::ForwardSink: sending receipt for packet(" << off.ToString() << ")");
		Packet to = CreatePacket(off);
		ASSERT(to->GetOffset() == off);
		to->SetFormat(src_fmt);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		if (type.IsRoleSideSource()) {
			WhenEnterCreatedEmptyPacket(to);
			
			RTLOG("AtomBase::ForwardSink: sending empty packet in format: " << src_fmt.ToString());
			//to->SetFormat(src_fmt);
			
			WhenLeaveCreatedEmptyPacket();
		}
		else {
			WhenEnterStorePacket(*this, to);
			
			StorePacket(sink_ch_i, src_ch_i, to);
			
			if (!to->GetFormat().IsValid()) {DUMP(src_fmt); DUMP(to->GetFormat());}
			ASSERT(to->GetFormat().IsValid());
			
			WhenLeaveStorePacket(to);
		}
		
		PacketTracker::Track(TrackerInfo("AtomBase::ForwardSink", __FILE__, __LINE__), *to);
		src_buf.Add(to);
		packets_forwarded++;
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

bool AtomBase::LinkSideSink(AtomBaseRef sink, int local_ch_i, int other_ch_i) {
	//side_src = -1; // SetSideSrc(-1)
	ASSERT(sink);
	//ASSERT(!side_sink_conn);
	if (!sink)
		return false;
	
	AtomTypeCls type = sink->GetType();
	//DUMP(type);
	ASSERT(type.IsRoleSideSink() || type.IsRolePipe());
	if (PassLinkSideSink(sink)) {
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
	ASSERT(type.IsRoleSideSource() || type.IsRolePipe());
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


void AtomBase::PacketConsumed(const Packet& p) {
	lock.Enter();
	consumed_packets.Add(p);
	lock.Leave();
}

void AtomBase::PacketsConsumed(const LinkedList<Packet>& v) {
	lock.Enter();
	consumed_packets.Append(v);
	lock.Leave();
}

bool AtomBase::IsPacketStuck() {
	InterfaceSinkRef sink_iface = GetSink();
	int sink_c = sink_iface->GetSinkCount();
	for(int i = 0; i < sink_c; i++) {
		Value& val = sink_iface->GetValue(i);
		if (val.GetQueueSize() == 0) {
			RTLOG("AtomBase::IsPacketStuck: sink #" << i << " empty");
			return true;
		}
	}
	
	InterfaceSourceRef src_iface = GetSource();
	int src_c = src_iface->GetSourceCount();
	for(int i = 0; i < src_c; i++) {
		Value& val = src_iface->GetSourceValue(i);
		if (val.IsQueueFull()) {
			RTLOG("AtomBase::IsPacketStuck: src #" << i << " full");
			return true;
		}
	}
	
	return false;
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




NAMESPACE_SERIAL_END
