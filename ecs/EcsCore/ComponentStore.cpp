#include "EcsCore.h"


NAMESPACE_OULU_BEGIN

void ComponentStore::Clone(Entity& dst, const Entity& src) {
	const ComponentMap& src_comps = src.GetComponents();
	ComponentMap& dst_comps = dst.GetComponents();
	
	ComponentMap::Iterator iter = const_cast<ComponentMap&>(src_comps).begin();
	for (; iter; ++iter) {
		const TypeId& comp_type = iter.key();
		ComponentBase* new_component = CreateComponent(comp_type);
		dst.InitializeComponent(*new_component);
		iter.value().CopyTo(new_component);
		dst_comps.ComponentMapBase::Add(comp_type, new_component);
	}
}

/*void ComponentStore::Update(double) {

	for (Ref<RefLinkedList<ComponentBase>>& components : comps.GetValues()) {
		Destroyable::PruneFromContainer(*components);
	}
}*/
ComponentBase* ComponentStore::CreateComponent(const TypeId& typeId) {
	auto iter = producers.Find(typeId);
	ASSERT_(iter, "Invalid to create non-existant component");
	
	ComponentBase* obj = iter.value()();
	return obj;
}

/*void ComponentStore::Uninitialize() {
	comps.Clear();
}*/

void ComponentStore::ReturnComponent(ComponentBase* c) {
	ASSERT(c);
	TypeId type = c->GetType();
	
}


NAMESPACE_OULU_END

