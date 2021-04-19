#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


ComponentMap ComponentStore::Clone(const ComponentMap& comp_map) {
	ComponentMap map;
	
	auto comp_type_it = comp_map.KeyBegin();
	for (auto& component : comp_map.GetValues()) {
		auto& componentType = *comp_type_it;
		auto new_component = CreateComponent(componentType);
		component->CopyTo(new_component.Get());
		map.GetAdd(componentType) = pick(new_component);
		comp_type_it++;
	}
	
	return map;
}

void ComponentStore::Update(float) {
	for (auto& components : m_components.GetValues()) {
		Destroyable::PruneFromContainer(&components);
	}
}

SharedComponent ComponentStore::CreateComponent(const TypeId& typeId) {
	int pos = m_producers.Find(typeId);
	
	ASSERT_(pos != -1, "Invalid to create non-existant component");
	
	auto it = m_producers.GetValues().Begin();
	it += pos;
	auto obj = (*it)();
	m_components.GetAdd(typeId).Add(obj);
	return obj;
}

void ComponentStore::Uninitialize() {
	/*for (auto components : m_components)
		for(auto& component : components.second)
			component->Uninitialize();*/
	m_components.Clear();
}

NAMESPACE_OULU_END

