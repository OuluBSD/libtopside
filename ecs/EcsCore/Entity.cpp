#include "EcsCore.h"

NAMESPACE_OULU_BEGIN



Entity::Entity(Pick<ComponentMap> components, EntityId id, EntityPool& pool) :
		comps(components),
		m_id(id),
		pool(pool) {
	InitializeComponents();
}

Entity::Entity(EntityId id, EntityPool& pool) : m_id(id), pool(pool) {
	
}

Entity::~Entity() {
	Destroy();
}

void Entity::OnChange() {
	changed = GetMachine().GetTicks();
}

void Entity::InitializeComponents() {
	for(auto& comp : comps.GetValues())
		InitializeComponent(*comp);
}

void Entity::InitializeComponent(ComponentBase& comp) {
	comp.ent = this;
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

void Entity::ConnectAll(ConnectorArea a) {
	Connector* conn = Find<Connector>();
	if (conn)
		conn->ConnectAll(a);
}

void Entity::ClearComponents() {
	if (conn) {
		conn->UnlinkAll();
		conn = 0;
	}
	comps.Clear();
}

EntityRef Entity::Clone() const {
	EntityRef ent = pool.Clone(*this);
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

void Entity::SetUpdateInterfaces() {
	if (conn)
		conn->SetUpdateInterfaces();
}

void Entity::UpdateInterfaces() {
	if (conn) {
		#define IFACE(x) \
		for(x##Source*  in:  FindInterfaces<x##Source>())  conn->AddSourceInterface(in); \
		for(x##Sink*   out:  FindInterfaces<x##Sink>())    conn->AddSinkInterface(out);
		IFACE_LIST
		#undef IFACE
	}
}

void Entity::RefreshConnectorPtr() {
	conn = Find<Connector>();
}

Machine& Entity::GetMachine() {
	return pool.GetMachine();
}

const Machine& Entity::GetMachine() const {
	return pool.GetMachine();
}

	
NAMESPACE_OULU_END
