#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


EntityPool::EntityPool() {
	
}

EntityId EntityPool::GetNextId() {
	static Atomic64 next_id;
	return ++next_id;
}

void EntityPool::Initialize(Entity& e, String prefab) {
	uint64 ticks = GetMachine().GetTicks();
	e.SetPrefab(prefab);
	e.SetCreated(ticks);
	e.SetChanged(ticks);
	
}

EntityRef EntityPool::Clone(const Entity& c) {
	EntityRef e = objects.Add();
	e->Init(this, GetNextId());
	Initialize(*e);
	e->CopyHeader(c);
	GetMachine().Get<ComponentStore>()->Clone(*e, c);
	return e;
}
	
void EntityPool::UnlinkDeep() {
	for (auto it = pools.rbegin(); it != pools.rend(); --it) {
		it().UnlinkDeep();
	}
	
	for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().UnlinkAll();
	}
}

void EntityPool::UninitializeComponentsDeep() {
	for (EntityPoolRef& p : pools)
		p->UninitializeComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().UninitializeComponents();
	}
	
	for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().Uninitialize();
	}
}

void EntityPool::ClearComponentsDeep() {
	for (EntityPoolRef& p : pools)
		p->ClearComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().ClearComponents();
	}
	
	comps.Clear();
}

void EntityPool::ClearDeep() {
	for (EntityPoolRef& p : pools)
		p->ClearDeep();
	pools.Clear();
	
	objects.Clear();
}

void EntityPool::ReverseEntities() {
	objects.Reverse();
}

void EntityPool::Clear() {
	UnlinkDeep();
	UninitializeComponentsDeep();
	ClearComponentsDeep();
	ClearDeep();
}

void EntityPool::PruneFromContainer() {
	for (auto& pool : pools)
		pool->PruneFromContainer();
	Destroyable::PruneFromContainer(objects);
}

void EntityPool::InitializeComponent(PoolComponentBase& comp) {
	comp.pool = this;
	comp.Initialize();
}


NAMESPACE_OULU_END
