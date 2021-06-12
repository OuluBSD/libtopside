#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN



CustomerComponent::CustomerComponent() : src_stream(this) {
	
}

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

void CustomerComponent::CreateOrder(double dt) {
	cfg.Update(dt, src_value.IsQueueFull());
	for (FwdScope scope(this, cfg); scope; scope++)
		scope.Forward();
}

void CustomerComponent::AddPlan(EonPlan& ep) {
	plans.Add(ep);
}

void CustomerComponent::Forward(FwdScope& fwd) {
	using DevMach = ScopeDevMachT<CenterSpec>;
	using InternalPacketData = typename DevMach::InternalPacketData;
	
	OrderSource& val_src = *this;
	
	ASSERT(plans.GetCount() == val_src.GetConnections());
	int link_i = 0;
	for (auto& link : val_src.GetConnections()) {
		EonPlan& ep = plans[link_i];
		OrderSinkRef val_sink = link.dst;
		ASSERT(val_sink);
		
		Order& val = val_sink->GetValue(ORDCTX);
		SimpleBufferedOrder* buf = CastPtr<SimpleBufferedOrder>(&val);
		if (buf) {
			/*AccelComponentGroup& ag = CastRef<AccelComponentGroup>(gr);
			
			StageComponent* comp = CastPtr<StageComponent>(val_sink->AsComponentBase());
			if (!comp)
				return false;*/
			
			off32 off = gen.Create();
			OrderPacket p = CreateOrderPacket(off);
			
			OrderFormat fmt = ScopeDevLibT<CenterSpec>::StageComponent::GetDefaultFormat<OrderSpec>();
			RTLOG("CustomerComponent::Forward: sending packet in format: " << fmt.ToString());
			p->SetFormat(fmt);
			
			InternalPacketData& data = p->template SetData<InternalPacketData>();
			data.pos = 0;
			data.count = ep.plan.GetCount()-1;
			
			OrderPacketTracker::Track(TrackerInfo("CustomerComponent::Forward", __FILE__, __LINE__), *p);
			buf->AddPacket(p);
			
		}
		else {
			TODO
		}
		++link_i;
	}
	
}

void CustomerComponent::ForwardExchange(FwdScope& fwd) {
	OrderSource& src = *this;
	auto& conns = src.GetConnections();
	for(auto& link : conns) {
		ExchangePointRef expt = link.expt;
		ASSERT(expt);
		if (expt) {
			fwd.AddNext(*expt);
		}
	}
}






bool CustomerSystem::Initialize() {
	
	return true;
}

void CustomerSystem::Start() {
	
}

void CustomerSystem::Update(double dt) {
	
	for (CustomerComponentRef& customer : customers) {
		customer->CreateOrder(dt);
	}
	
}

void CustomerSystem::Stop() {
	
}

void CustomerSystem::Uninitialize() {
	customers.Clear();
}

void CustomerSystem::Add(CustomerComponentRef p) {
	customers.FindAdd(p);
}

void CustomerSystem::Remove(CustomerComponentRef p) {
	customers.RemoveKey(p);
}



NAMESPACE_TOPSIDE_END
