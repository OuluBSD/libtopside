#include "EcsCore.h"

NAMESPACE_TOPSIDE_BEGIN


Entity::Entity() {
	DBG_CONSTRUCT
}

Entity::~Entity() {
	Destroy();
	DBG_DESTRUCT
}

EntityId Entity::GetNextId() {
	static Atomic next_id;
	return ++next_id;
}

String Entity::GetTreeString(int indent) {
	String s;
	
	s.Cat('\t', indent);
	
	s << (name.IsEmpty() ? "unnamed" : "\"" + name + "\"") << ": " << prefab << "\n";
	
	for (ComponentBaseRef& c : comps) {
		s.Cat('\t', indent+1);
		s << c->ToString();
		s.Cat('\n');
	}
	
	return s;
}

void Entity::OnChange() {
	changed = GetMachine().GetTicks();
}

ComponentBaseRef Entity::GetAddTypeCls(TypeCls comp_type) {
	for (ComponentBaseRef& comp : comps) {
		TypeCls type = comp->GetTypeId();
		if (type == comp_type)
			return comp;
	}
	return AddPtr(EcsFactory::CompDataMap().Get(comp_type).new_fn());
}

void Entity::InitializeComponents() {
	for(auto& comp : comps.GetValues())
		InitializeComponent(*comp);
}

void Entity::InitializeComponent(ComponentBase& comp) {
	comp.SetParent(this);
	comp.Initialize();
}

void Entity::UninitializeComponents() {
	auto& comps = this->comps.GetValues();
	int dbg_i = 0;
	for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().Uninitialize();
		dbg_i++;
	}
}

void Entity::ClearComponents() {
	ComponentStoreRef sys = GetMachine().Get<ComponentStore>();
	for (auto iter = comps.rbegin(); iter; --iter)
		sys->ReturnComponent(comps.Detach(iter));
	ASSERT(comps.IsEmpty());
}

EntityRef Entity::Clone() const {
	EntityRef ent = GetPool().Clone(*this);
	ent->InitializeComponents();
	return ent;
}

void Entity::Destroy() {
	Destroyable::Destroy();
	
	for (auto& component : comps.GetValues()) {
		component->Destroy();
	}
}

void Entity::SetEnabled(bool enable) {
	Enableable::SetEnabled(enable);
	
	for (auto& component : comps.GetValues()) {
		component->SetEnabled(enable);
	}
}

Machine& Entity::GetMachine() {
	return GetPool().GetMachine();
}

const Machine& Entity::GetMachine() const {
	return GetPool().GetMachine();
}

Pool& Entity::GetPool() const {
	Pool* p = RefScopeParent<EntityParent>::GetParent().o;
	ASSERT(p);
	return *p;
}

void Entity::VisitSinks(RuntimeVisitor& vis) {
	for(ComponentBaseRef& c : comps)
		c->VisitSinks(vis);
}

void Entity::VisitSources(RuntimeVisitor& vis){
	for(ComponentBaseRef& c : comps)
		c->VisitSources(vis);
}

int Entity::GetPoolDepth() const {
	int d = 0;
	Pool* p = &GetPool();
	while (1) {
		p = p->GetParent();
		if (!p) break;
		++d;
	}
	return d;
}

bool Entity::HasPoolParent(PoolRef pool) const {
	Pool* p = &GetPool();
	while (p) {
		if (p == &*pool)
			return true;
		p = p->GetParent();
	}
	return false;
}






bool EntityHashVisitor::OnEntry(const RTTI& type, void* mem, LockedScopeRefCounter* ref) {
	if (type == AsTypeCls<Entity>()) {
		Entity& e = *(Entity*)mem;
		ch.Put(1);
		ch.Put(e.GetId());
	}
	else if (type == AsTypeCls<Pool>()) {
		Pool& p = *(Pool*)mem;
		ch.Put(2);
		ch.Put(p.GetId());
	}
	return true;
}


NAMESPACE_TOPSIDE_END
