#include "EcsCore.h"

NAMESPACE_ECS_BEGIN



/*CustomerComponent::CustomerComponent() : src_stream(this), cfg(gen) {
	DumpRuntimeDiagnostics(this);
}*/

void CustomerComponent::Initialize() {
	CustomerSystemRef sys = GetMachine().TryGet<CustomerSystem>();
	if (sys)
		sys->Add(AsRef<CustomerComponent>());
}

void CustomerComponent::Uninitialize() {
	CustomerSystemRef sys = GetMachine().TryGet<CustomerSystem>();
	if (sys)
		sys->Remove(AsRef<CustomerComponent>());
}

void CustomerComponent::UpdateConfig(double dt) {
	cfg.Update(dt, src_value.IsQueueFull());
}

void CustomerComponent::AddPlan(Eon::Plan& ep) {
	plans.Add(ep);
}

void CustomerComponent::Forward(FwdScope& fwd) {
	TODO
	#if 0
	if (ext)
		ext->Forward(fwd);
	
	int read_i = fwd.GetPos();
	if (read_i == 0) {
		using DevMach = ScopeDevMachT<CenterSpec>;
		using InternalPacketData = typename DevMach::InternalPacketData;
		
		if (src_value.IsQueueFull())
			return;
		
		SimpleOrder& src_buf = src_value;
		
		off32 off = gen.Create();
		OrderPacket p = CreateOrderPacket(off);
		
		unfulfilled_offsets.Add(off.value);
		
		OrderFormat fmt = ScopeDevCoreT<CenterSpec>::GetDefaultFormat<OrderSpec>();
		RTLOG("CustomerComponent::Forward: sending packet " << off.ToString() << " in format: " << fmt.ToString());
		p->SetFormat(fmt);
		
		ASSERT(plans.GetCount() == 1);
		Eon::Plan& ep = plans[0];
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = ep.plan.GetCount()-1;
		
		OrderPacketTracker::Track(TrackerInfo("CustomerComponent::Forward", __FILE__, __LINE__), *p);
		src_buf.AddPacket(p);
	}
	else {
		ReceiptPacketBuffer& buf = sink_value.GetBuffer();
		for (ReceiptPacket& p : buf) {
			off32 off = p->GetOffset();
			unfulfilled_offsets.RemoveKey(off.value);
			RTLOG("CustomerComponent::Forward: removing fulfilled packet " << off.ToString());
		}
		buf.Clear();
		
		
		if (unfulfilled_offsets.GetCount() > max_unfulfilled) {
			LOG("CustomerComponent::Forward: error: too many unfulfilled packets");
			while (unfulfilled_offsets.GetCount() > max_unfulfilled)
				unfulfilled_offsets.Remove(0);
		}
	}
	#endif
}

void CustomerComponent::ForwardExchange(FwdScope& fwd) {
	int read_i = fwd.GetPos();
	if (read_i > 0)
		return;
	ValSource& src = *this;
	
	ExchangePointRef expt = src.GetExPt();
	ASSERT(expt);
	if (expt) {
		fwd.AddNext(*expt);
	}
}






bool CustomerSystem::Initialize() {
	
	return true;
}

void CustomerSystem::Start() {
	
}

void CustomerSystem::Update(double dt) {
	LinkedList<Once> cbs;
	lock.Enter();
	MemSwap(cbs, once_cbs);
	lock.Leave();
	
	for (Once& o : cbs) {
		for (FwdScope scope(o.fwd, *o.cfg); scope; scope++)
			scope.Forward();
	}
	
	for (CustomerComponentRef& c : customers) {
		c->UpdateConfig(dt);
		for (FwdScope scope(*c, c->cfg); scope; scope++)
			scope.Forward();
	}
	
}

void CustomerSystem::Stop() {
	
}

void CustomerSystem::Uninitialize() {
	once_cbs.Clear();
	customers.Clear();
}

void CustomerSystem::Add(CustomerComponentRef p) {
	customers.FindAdd(p);
}

void CustomerSystem::Remove(CustomerComponentRef p) {
	customers.RemoveKey(p);
}

void CustomerSystem::AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg) {
	lock.Enter();
	Once& o = once_cbs.Add();
	o.fwd = &fwd;
	o.cfg = &cfg;
	lock.Leave();
}



NAMESPACE_ECS_END
