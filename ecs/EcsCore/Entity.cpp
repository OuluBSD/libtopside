#include "EcsCore.h"

NAMESPACE_OULU_BEGIN


Entity::Entity() {
	
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

void Entity::ClearComponents() {
	TODO // exchange point?
	/*if (conn) {
		conn->UnlinkAll();
		conn = 0;
	}*/
	comps.Clear();
}

EntityRef Entity::Clone() const {
	EntityRef ent = pool->Clone(*this);
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
	return pool->GetMachine();
}

const Machine& Entity::GetMachine() const {
	return pool->GetMachine();
}

	
NAMESPACE_OULU_END
