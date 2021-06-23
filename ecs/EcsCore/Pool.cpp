#include "EcsCore.h"


NAMESPACE_ECS_BEGIN


//PoolRef GetConnectorBasePool(ConnectorBase* conn) {return conn->GetPool();}

Machine& GetPoolMachine(PoolRef pool) {return pool->GetMachine();}



Pool::Pool() {
	DBG_CONSTRUCT
}

Pool::~Pool() {
	DBG_DESTRUCT
}

PoolId Pool::GetNextId() {
	static Atomic next_id;
	return ++next_id;
}

Pool* Pool::GetParent() const {
	return RefScopeParent<PoolParent>::GetParent().b;
}

Machine& Pool::GetMachine() {
	if (machine)
		return *machine;
	Pool* p = this;
	int levels = 0;
	while (p && levels++ < 1000) {
		const PoolParent& par = p->RefScopeParent<PoolParent>::GetParent();
		if (par.a) {
			machine = &par.a->GetMachine();
			ASSERT(machine);
			return *machine;
		}
		ASSERT(p != par.b);
		p = par.b;
	}
	THROW(Exc("Machine ptr not found"));
}

void Pool::Initialize(Entity& e, String prefab) {
	uint64 ticks = GetMachine().GetTicks();
	e.SetPrefab(prefab);
	e.SetCreated(ticks);
	e.SetChanged(ticks);
	
}

EntityRef Pool::CreateEmpty() {
	Entity& e = objects.Add();
	e.SetParent(this);
	e.SetId(GetNextId());
	Initialize(e);
	return e;
}

EntityRef Pool::GetAddEmpty(String name) {
	EntityRef e = FindEntityByName(name);
	if (e)
		return e;
	e = CreateEmpty();
	e->SetName(name);
	return e;
}

EntityRef Pool::Clone(const Entity& c) {
	EntityRef e = CreateEmpty();
	e->CopyHeader(c);
	GetMachine().Get<ComponentStore>()->Clone(*e, c);
	return e;
}

bool Pool::Link(ComponentBaseRef src_comp, ComponentBaseRef dst_comp, ValDevCls src_iface, ValDevCls sink_iface) {
	InterfaceSourceRef src = src_comp->FindSource(src_iface);
	InterfaceSinkRef sink = dst_comp->FindSink(sink_iface);
	ASSERT(src && sink);
	if (!src || !sink)
		return false;
	ASSERT(src	->AsComponentBase()->GetEntity()->HasPoolParent(AsRefT()));
	ASSERT(sink	->AsComponentBase()->GetEntity()->HasPoolParent(AsRefT()));
	CookieRef src_cookie, sink_cookie;
	if (src->Accept(sink, src_cookie, sink_cookie)) {
		const auto& src_d = Ecs::Factory::SourceDataMap().Get(src_iface);
		if (src_d.sink_cls != sink_iface) {
			ASSERT(0);
			LOG("internal error: unexpected sink class type");
			return false;
		}
		
		TypeCls expt_type = src_d.expt_type;
		ASSERT(expt_type);
		ExchangePointRef ep = MetaExchangePoint::Add(expt_type);
		RTLOG("ManualConnector::LinkManually(TypeCls...): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
		src->Link(ep, sink, src_cookie, sink_cookie);
		ep->Init(this);
		ep->Set(src, sink, src_cookie, sink_cookie);
		return true;
	}
	return false;
}

void Pool::UnlinkExchangePoints() {
	for (ExchangePointRef& pt : pts) {
		pt->Source()	->ClearLink();
		pt->Sink()		->ClearLink();
		pt->Clear();
	}
	pts.Clear();
}

void Pool::UnlinkDeep() {
	for (auto it = pools.rbegin(); it != pools.rend(); --it) {
		it().UnlinkDeep();
	}
	
	UnlinkExchangePoints();
	
	/*for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().UnlinkAll();
	}*/
}

void Pool::ClearInterfacesDeep() {
	for (PoolRef& p : pools)
		p->ClearInterfacesDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().ClearInterfaces();
	}
}

void Pool::UnrefDeep() {
	RefClearVisitor vis;
	vis.Visit(*this);
}

void Pool::UninitializeComponentsDeep() {
	for (PoolRef& p : pools)
		p->UninitializeComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().UninitializeComponents();
	}
	
	/*for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().UninitializeWithExt();
	}*/
}

void Pool::ClearComponentsDeep() {
	for (PoolRef& p : pools)
		p->ClearComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().ClearComponents();
	}
	
	/*if (!comps.IsEmpty()) {
		ConnectorStoreRef sys = GetMachine().Get<ConnectorStore>();
		for (auto iter = comps.rbegin(); iter; --iter)
			sys->ReturnComponent(comps.Detach(iter));
		ASSERT(comps.IsEmpty());
	}*/
}

void Pool::ClearDeep() {
	for (PoolRef& p : pools)
		p->ClearDeep();
	pools.Clear();
	
	objects.Clear();
}

void Pool::ReverseEntities() {
	objects.Reverse();
}

void Pool::Clear() {
	// useless ClearInterfacesDeep();
	UnrefDeep();
	UnlinkDeep();
	UninitializeComponentsDeep();
	ClearComponentsDeep();
	ClearDeep();
}

void Pool::PruneFromContainer() {
	for (auto& pool : pools)
		pool->PruneFromContainer();
	Destroyable::PruneFromContainer(objects);
}

/*void Pool::InitializeComponent(ConnectorBase& comp) {
	comp.Initialize();
}*/

void Pool::Dump() {
	LOG(GetTreeString());
}

String Pool::GetTreeString(int indent) {
	String s;
	
	String pre;
	pre.Cat('\t', indent);
	
	s << ".." << name << "[" << id << "]\n";
	
	/*for (ConnectorRef& c : comps) {
		s.Cat('\t', indent+1);
		s << "." << c->ToString();
		s << "\n";
	}*/
	
	for (EntityRef& e : objects)
		s << e->GetTreeString(indent+1);
	
	for (PoolRef& p : pools)
		s << p->GetTreeString(indent+1);
	
	return s;
}




bool PoolHashVisitor::OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) {
	if (derived == AsTypeCls<Pool>()) {
		Pool& p = *(Pool*)mem;
		ch.Put(p.GetId());
	}
	return true;
}






NAMESPACE_ECS_END
