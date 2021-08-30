#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


AtomBase::AtomBase() {
	DBG_CONSTRUCT
}

AtomBase::~AtomBase() {
	DBG_DESTRUCT
}

Machine& AtomBase::GetMachine() {
	return GetParent()->GetMachine();
}

void AtomBase::UninitializeWithExt() {
	ClearExtension();
	Uninitialize();
	ClearSinkSource();
}

LoopRef AtomBase::GetLoop() {
	return GetParent()->AsRefT();
}

String AtomBase::ToString() const {
	return GetDynamicName();
}

void AtomBase::ForwardAtom(FwdScope& fwd) {
	RTLOG("AtomBase::ForwardAtom");
	POPO(Pol::Serial::Atom::ConsumerFirst);
	POPO(Pol::Serial::Atom::SkipDulicateExtFwd);
	
	if (fwd.GetPos() > 0) {
		Forward(fwd);
	}
	else {
		RTLOG("AtomBase::ForwardAtom: skip duplicate extension forward");
	}
	
	ForwardConsumed(fwd);
}

void AtomBase::ForwardExchange(FwdScope& fwd) {
	Value& src_val = GetSource()->GetSourceValue();
	SimpleBufferedValue* src_buf = CastPtr<SimpleBufferedValue>(&src_val);
	if (src_buf && !src_buf->IsEmpty()) {
		ExchangeSourceProvider* src = CastPtr<ExchangeSourceProvider>(this);
		ASSERT(src);
		ExchangePointRef expt = src->GetExPt();
		ASSERT(expt);
		if (expt) {
			fwd.AddNext(*expt);
		}
	}
}

void AtomBase::ForwardConsumed(FwdScope& fwd) {
	Value& src_value = GetSource()->GetSourceValue();
	Value& sink_value = GetSink()->GetValue();
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
		off32 o = in->GetOffset();
		if (offs.Find(o.value) >= 0) {
			// receipt is already sent
			continue;
		}
		offs.Add(o.value);
		
		RTLOG("AtomBase::ForwardOutput: sending receipt for packet(" << o.ToString() << ")");
		Packet to = CreatePacket(o);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		if (type.IsSideSource()) {
			WhenEnterCreatedEmptyPacket(to);
			
			RTLOG("AtomBase::ForwardOutput: sending packet in format: " << src_fmt.ToString());
			to->SetFormat(src_fmt);
			
			WhenLeaveCreatedEmptyPacket();
		}
		else {
			WhenEnterStorePacket(*this, to);
			
			StorePacket(to);
			
			if (!to->GetFormat().IsValid()) {DUMP(src_fmt); DUMP(to->GetFormat());}
			ASSERT(to->GetFormat().IsValid());
			
			WhenLeaveStorePacket(to);
		}
		
		PacketTracker::Track(TrackerInfo("AtomBase::ForwardOutput", __FILE__, __LINE__), *to);
		src_buf.Add(to);
		packets_forwarded++;
	}
	
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
