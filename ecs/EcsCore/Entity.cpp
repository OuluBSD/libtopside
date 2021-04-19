#include "EcsCore.h"

NAMESPACE_OULU_BEGIN



Entity::Entity(Pick<ComponentMap> components, EntityId id, EntityPool& pool) :
		m_components(components),
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
	for(auto& comp : m_components.GetValues())
		InitializeComponent(*comp);
}

void Entity::InitializeComponent(ComponentBase& comp) {
	comp.ent = this;
	comp.Initialize();
}

void Entity::UninitializeComponents() {
	Array<SharedComponent>& comps = m_components.GetValues();
	Array<SharedComponent>::Iterator end = comps.End();
	Array<SharedComponent>::Iterator begin = comps.Begin();
	Array<SharedComponent>::Iterator it = end - 1;
	int i = comps.GetCount() - 1;
	for (auto it = end - 1; it != begin - 1; --it) {
		(**it).Uninitialize();
		i--;
	}
}

void Entity::ConnectAll() {
	Connector* conn = Find<Connector>();
	if (conn)
		conn->ConnectAll();
}

void Entity::ClearComponents() {
	if (conn) {
		conn->UnlinkAll();
		conn = 0;
	}
	m_components.Clear();
}

SharedEntity Entity::Clone() const {
	SharedEntity ent = pool.Clone(*this);
	ent->InitializeComponents();
	return ent;
}

void Entity::Destroy() {
	Destroyable::Destroy();
	
	for (auto& component : m_components.GetValues()) {
		component->Destroy();
	}
}

void Entity::SetEnabled(bool enable) {
	Enableable::SetEnabled(enable);
	
	for (auto& component : m_components.GetValues()) {
		component->SetEnabled(enable);
	}
}

void Entity::SetUpdateInterfaces() {
	if (conn)
		conn->SetUpdateInterfaces();
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
