#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


Pool::Pool() {
	DBG_CONSTRUCT
}

Pool::~Pool() {
	DBG_DESTRUCT
}

EntityId Pool::GetNextId() {
	static Atomic64 next_id;
	return ++next_id;
}

Pool* Pool::GetParent() const {
	return RefScopeParent<PoolParent>::GetParent().b;
}

Machine& Pool::GetMachine() {
	if (machine)
		return *machine;
	Pool* p = this;
	while (p) {
		const PoolParent& par = RefScopeParent<PoolParent>::GetParent();
		if (par.a) {
			machine = &par.a->GetMachine();
			ASSERT(machine);
			return *machine;
		}
		p = par.b;
	}
	throw Exc("Machine ptr not found");
}

void Pool::Initialize(Entity& e, String prefab) {
	uint64 ticks = GetMachine().GetTicks();
	e.SetPrefab(prefab);
	e.SetCreated(ticks);
	e.SetChanged(ticks);
	
}

EntityRef Pool::Clone(const Entity& c) {
	Entity& e = objects.Add();
	e.SetParent(this);
	e.Init(GetNextId());
	Initialize(e);
	e.CopyHeader(c);
	GetMachine().Get<ComponentStore>()->Clone(e, c);
	return e;
}
	
void Pool::UnlinkDeep() {
	for (auto it = pools.rbegin(); it != pools.rend(); --it) {
		it().UnlinkDeep();
	}
	
	for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().UnlinkAll();
	}
}

void Pool::UninitializeComponentsDeep() {
	for (PoolRef& p : pools)
		p->UninitializeComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().UninitializeComponents();
	}
	
	for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().Uninitialize();
	}
}

void Pool::ClearComponentsDeep() {
	for (PoolRef& p : pools)
		p->ClearComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().ClearComponents();
	}
	
	comps.Clear();
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

void Pool::InitializeComponent(ConnectorBase& comp) {
	comp.pool = this;
	comp.Initialize();
}


NAMESPACE_OULU_END
