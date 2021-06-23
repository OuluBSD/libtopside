#include "EcsCore.h"

NAMESPACE_ECS_BEGIN


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

ComponentBaseRef Entity::GetTypeCls(EcsTypeCls comp_type) {
	for (ComponentBaseRef& comp : comps) {
		TypeCls type = comp->GetTypeId();
		if (type == comp_type)
			return comp;
	}
	return ComponentBaseRef();
}

ComponentBaseRef Entity::GetAddTypeCls(EcsTypeCls comp_type) {
	ComponentBaseRef cb = FindTypeCls(comp_type);
	return cb ? cb : AddPtr(GetMachine().Get<ComponentStore>()->CreateComponentTypeCls(comp_type));
}

ComponentBaseRef Entity::FindTypeCls(EcsTypeCls comp_type) {
	for (ComponentBaseRef& comp : comps) {
		TypeCls type = comp->GetTypeId();
		if (type == comp_type)
			return comp;
	}
	return ComponentBaseRef();
}

ComponentBaseRef Entity::AddPtr(ComponentBase* comp) {
	comp->SetParent(this);
	comps.AddBase(comp);
	InitializeComponent(*comp);
	return ComponentBaseRef(this, comp);
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
		it().UninitializeWithExt();
		dbg_i++;
	}
}

void Entity::ClearComponents() {
	ComponentStoreRef sys = GetMachine().Get<ComponentStore>();
	for (auto iter = comps.rbegin(); iter; --iter)
		sys->ReturnComponent(comps.Detach(iter));
	ASSERT(comps.IsEmpty());
}

void Entity::ClearInterfaces() {
	for (auto iter = comps.rbegin(); iter; --iter)
		iter().ClearSinkSource();
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
		c->VisitSink(vis);
}

void Entity::VisitSources(RuntimeVisitor& vis){
	for(ComponentBaseRef& c : comps)
		c->VisitSource(vis);
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






bool EntityHashVisitor::OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) {
	if (derived == AsTypeCls<Entity>()) {
		Entity& e = *(Entity*)mem;
		ch.Put(1);
		ch.Put(e.GetId());
	}
	else if (derived == AsTypeCls<Pool>()) {
		Pool& p = *(Pool*)mem;
		ch.Put(2);
		ch.Put(p.GetId());
	}
	return true;
}


NAMESPACE_ECS_END
