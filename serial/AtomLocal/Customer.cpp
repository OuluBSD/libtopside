#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


bool CustomerAtom::Initialize(const Script::WorldState& ws) {
	AtomT::Initialize(ws);
	packets_forwarded = 0;
	customer.Create();
	GetMachine().Get<AtomSystem>()->Add(AsRef<CustomerAtom>());
	return true;
}

void CustomerAtom::Uninitialize() {
	GetMachine().Get<AtomSystem>()->Remove(AsRef<CustomerAtom>());
}

void CustomerAtom::AddPlan(Script::Plan& sp) {
	ASSERT(!customer.IsEmpty());
	customer->plans.Add(sp);
}

void CustomerAtom::UpdateConfig(double dt) {
	ASSERT(customer);
	{
		InterfaceSourceRef ss = GetSource();
		InterfaceSource* o = ss.Get();
		TypeCls cls = AsTypeCls<DefaultInterfaceSource>();
		void* p = o->GetBasePtr(cls);
		DefaultInterfaceSource* pp = (DefaultInterfaceSource*)p;
	}
	DefaultInterfaceSourceRef src = GetSource();
	ASSERT(src);
	if (src) {
		Stream& str = src->GetStream();
		Value& val = str.Get();
		customer->cfg.Update(dt, val.IsQueueFull());
	}
}

void CustomerAtom::ForwardAtom(FwdScope& fwd) {
	ASSERT(this->customer);
	CustomerData& c = *this->customer;
	
	int read_i = fwd.GetPos();
	if (read_i == 0) {
		Value& src_value = GetSourceValue();
		
		if (src_value.IsQueueFull()) {
			RTLOG("CustomerAtom::ForwardCustomer: customer: skipping order, because queue is full");
			return;
		}
		
		off32 off = c.gen.Create();
		Packet p = CreatePacket(off);
		
		c.unfulfilled_offsets.Add(off.value);
		
		Format fmt = GetSourceValue().GetFormat();
		ASSERT(fmt.IsValid());
		RTLOG("CustomerAtom::ForwardCustomer: customer: sending order " << off.ToString() << " in format: " << fmt.ToString());
		p->SetFormat(fmt);
		
		//DUMP(c.plans.GetCount());
		ASSERT(c.plans.GetCount() == 1);
		Script::Plan& ep = c.plans[0];
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = ep.plan.GetCount()-1;
		
		WhenEnterCreatedEmptyPacket(p);
		WhenLeaveCreatedEmptyPacket();
		
		PacketTracker::Track(TrackerInfo("CustomerAtom::ForwardCustomer", __FILE__, __LINE__), *p);
		src_value.GetBuffer().Add(p);
		packets_forwarded++;
	}
	else {
		Value& sink_value = GetValue();
		
		PacketBuffer& buf = sink_value.GetBuffer();
		for (Packet& p : buf) {
			off32 off = p->GetOffset();
			c.unfulfilled_offsets.RemoveKey(off.value);
			RTLOG("CustomerAtom::ForwardCustomer: customer: removing fulfilled packet " << off.ToString());
		}
		buf.Clear();
		
		
		/*if (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled) {
			LOG("CustomerAtom::Forward: customer: error: too many unfulfilled packets");
			DUMPC(c.unfulfilled_offsets);
			while (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled)
				c.unfulfilled_offsets.Remove(0);
		}*/
	}
}

void CustomerAtom::ForwardExchange(FwdScope& fwd) {
	if (!packets_forwarded && GetSourceValue().GetBuffer().IsEmpty()) {
		RTLOG("CustomerAtom::ForwardExchange: no packets to forward, exiting FwdScope");
		return;
	}
	int read_i = fwd.GetPos();
	InterfaceSource& src = *this;
	
	ExchangePointRef expt = src.GetExPt();
	ASSERT(expt);
	if (expt) {
		fwd.AddNext(*expt);
	}
	else {
		RTLOG("CustomerAtom::ForwardExchange: source has no next exchange point");
	}
}



NAMESPACE_SERIAL_END
