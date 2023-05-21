#include "EcsCore.h"

NAMESPACE_ECS_BEGIN


Entity::Entity() {
	DBG_CONSTRUCT
}

Entity::~Entity() {
	UnrefDeep();
	UninitializeComponents();
	ClearComponents();
	DBG_DESTRUCT
}

void Entity::Etherize(Ether& e) {
	/*
	EntityId id = -1;
	int64 created = 0;
	int64 changed = 0;

	String prefab;
	String name;
	
	ComponentMap comps;
	EntityId m_id;
	*/
	
	GeomVar type;
	/*
	e % freeze_bits
	  % name
	  % id
	  ;
	*/
	if (e.IsLoading()) {
		TODO
		while (!e.IsEof()) {
			e.GetT(type);
			
		}
	}
	else {
		for (ComponentRef c : comps) {
			type = GEOMVAR_PUSH_COMPONENT;
			e.PutT(type);
			TypeCls cls = c->GetTypeId();
			String name = ComponentFactory::GetComponentName(cls);
			e.Put(name);
			
			c->Etherize(e);
			
			type = GEOMVAR_POP_COMPONENT;
			e.PutT(type);
		}
	}
}

void Entity::UnrefDeep() {
	RefClearVisitor vis;
	vis.Visit(*this);
}

EntityId Entity::GetNextId() {
	static Atomic next_id;
	return ++next_id;
}

String Entity::GetTreeString(int indent) {
	String s;
	
	s.Cat('\t', indent);
	
	s << (name.IsEmpty() ? (String)"unnamed" : "\"" + name + "\"") << ": " << prefab << "\n";
	
	for (ComponentBaseRef& c : comps) {
		s.Cat('\t', indent+1);
		s << c->ToString();
		s.Cat('\n');
	}
	
	return s;
}

void Entity::OnChange() {
	changed = GetEngine().GetTicks();
}

ComponentBaseRef Entity::GetTypeCls(TypeCls comp_type) {
	for (ComponentBaseRef& comp : comps) {
		TypeCls type = comp->GetTypeId();
		if (type == comp_type)
			return comp;
	}
	return ComponentBaseRef();
}

ComponentBaseRef Entity::GetAddTypeCls(TypeCls cls) {
	ComponentBaseRef cb = FindTypeCls(cls);
	return cb ? cb : AddPtr(GetEngine().Get<ComponentStore>()->CreateComponentTypeCls(cls));
}

ComponentBaseRef Entity::FindTypeCls(TypeCls comp_type) {
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
		it().Uninitialize();
		dbg_i++;
	}
}

void Entity::ClearComponents() {
	ComponentStoreRef sys = GetEngine().Get<ComponentStore>();
	for (auto iter = comps.rbegin(); iter; --iter)
		sys->ReturnComponent(comps.Detach(iter));
	ASSERT(comps.IsEmpty());
}

EntityRef Entity::Clone() const {
	EntityRef ent = GetPool().Clone(*this);
	ent->InitializeComponents();
	return ent;
}

ComponentBaseRef Entity::CreateEon(String id) {
	int i = ComponentFactory::CompEonIds().Find(id);
	if (i < 0)
		return ComponentBaseRef();
	
	const auto& d = ComponentFactory::CompDataMap()[i];
	return GetAddTypeCls(d.rtti_cls);
}

void Entity::Destroy() {
	Destroyable::Destroy();
	
	for (auto& component : comps.GetValues()) {
		component->Destroy();
	}
	
	if (auto es = GetEngine().TryGet<EntityStore>())
		es->AddToDestroyList(this);
	
}

Engine& Entity::GetEngine() {
	return GetPool().GetEngine();
}

const Engine& Entity::GetEngine() const {
	return GetPool().GetEngine();
}

Pool& Entity::GetPool() const {
	Pool* p = RefScopeParent<EntityParent>::GetParent().o;
	ASSERT(p);
	return *p;
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
