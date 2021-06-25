#include "EcsLib.h"


NAMESPACE_ECS_BEGIN



ExtComponent::ExtComponent() :
	src_stream(this),
	sink_value(this)
{
	//DumpRuntimeDiagnostics(this);
	ValDevCls vd(DevCls::CENTER, ValCls::ORDER);
	SetSinkType(vd);
	SetSourceType(vd);
}

ExtComponent::~ExtComponent() {ASSERT(ext.IsEmpty());}

void ExtComponent::Initialize() {
	ExtSystemRef sys = GetMachine().TryGet<ExtSystem>();
	if (sys)
		sys->Add(AsRef<ExtComponent>());
}

void ExtComponent::Uninitialize() {
	ExtSystemRef sys = GetMachine().TryGet<ExtSystem>();
	if (sys)
		sys->Remove(AsRef<ExtComponent>());
}

void ExtComponent::UpdateConfig(double dt) {
	//if (cfg.IsEmpty())
	//	cfg.Create(new RealtimeSourceConfig(gen));
	customer->cfg.Update(dt, src_value.IsQueueFull());
}

/*void ExtComponent::AddPlan(Eon::Plan& ep) {
	plans.Add(ep);
}*/

void ExtComponent::Forward(FwdScope& fwd) {
	if (ext)
		ext->Forward(fwd);
	
	CustomerData& c = *this->customer;
	
	int read_i = fwd.GetPos();
	if (read_i == 0) {
		if (src_value.IsQueueFull())
			return;
		
		SimpleValue& src_buf = src_value;
		
		off32 off = c.gen.Create();
		Packet p = CreatePacket(off);
		
		c.unfulfilled_offsets.Add(off.value);
		
		Format fmt = GetDefaultFormat(VD(CENTER, ORDER));
		RTLOG("ExtComponent::Forward: sending packet " << off.ToString() << " in format: " << fmt.ToString());
		p->SetFormat(fmt);
		
		ASSERT(c.plans.GetCount() == 1);
		Eon::Plan& ep = c.plans[0];
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = ep.plan.GetCount()-1;
		
		PacketTracker::Track(TrackerInfo("ExtComponent::Forward", __FILE__, __LINE__), *p);
		src_buf.AddPacket(p);
	}
	else {
		PacketBuffer& buf = sink_value.GetBuffer();
		for (Packet& p : buf) {
			off32 off = p->GetOffset();
			c.unfulfilled_offsets.RemoveKey(off.value);
			RTLOG("ExtComponent::Forward: removing fulfilled packet " << off.ToString());
		}
		buf.Clear();
		
		
		if (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled) {
			LOG("ExtComponent::Forward: error: too many unfulfilled packets");
			while (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled)
				c.unfulfilled_offsets.Remove(0);
		}
	}
}

void ExtComponent::ForwardExchange(FwdScope& fwd) {
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

bool ExtComponent::SetExtension(ComponentExtBase* c) {
	ext.Clear();
	ext = c;
	c->SetParent(this);
	c->Initialize();
	return true;
}

void ExtComponent::ClearExtension() {
	if (ext) {
		ext->Uninitialize();
		ext.Clear();
	}
}

ComponentExtBaseRef ExtComponent::GetExtension() {
	return ext ? ext->template AsRef<ComponentExtBase>() : ComponentExtBaseRef();
}


InterfaceSourceRef ExtComponent::GetSource() {
	return InterfaceSourceRef(GetParentUnsafe(), (InterfaceSource*)this);
}

InterfaceSinkRef ExtComponent::GetSink() {
	return InterfaceSinkRef(GetParentUnsafe(), (InterfaceSink*)this);
}




















bool ExtSystem::Initialize() {
	
	return true;
}

void ExtSystem::Start() {
	
}

void ExtSystem::Update(double dt) {
	LinkedList<Once> cbs;
	lock.Enter();
	MemSwap(cbs, once_cbs);
	lock.Leave();
	
	for (Once& o : cbs) {
		for (FwdScope scope(o.fwd, *o.cfg); scope; scope++)
			scope.Forward();
	}
	
	for (ExtComponentRef& c : customers) {
		c->UpdateConfig(dt);
		for (FwdScope scope(*c, c->customer->cfg); scope; scope++)
			scope.Forward();
	}
	
}

void ExtSystem::Stop() {
	
}

void ExtSystem::Uninitialize() {
	once_cbs.Clear();
	customers.Clear();
}

void ExtSystem::Add(ExtComponentRef p) {
	customers.FindAdd(p);
}

void ExtSystem::Remove(ExtComponentRef p) {
	customers.RemoveKey(p);
}

void ExtSystem::AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg) {
	lock.Enter();
	Once& o = once_cbs.Add();
	o.fwd = &fwd;
	o.cfg = &cfg;
	lock.Leave();
}











TypeCompCls AsTypeCompCls(TypeExtCls e) {
	TypeCompCls c;
	c.sub = e.sub;
	c.side.vd = e.side;
	c.side.type = ExtComponent::GetEcsType();
	c.sink = e.sink;
	c.src  = e.src;
	return c;
}

NAMESPACE_ECS_END
