#include "EcsCore.h"


NAMESPACE_ECS_BEGIN


void ComponentStore::Clone(Main& dst, const Main& src) {
	const ComponentMap& src_comps = src.GetComponents();
	ComponentMap& dst_comps = dst.GetComponents();
	
	ComponentMap::Iterator iter = const_cast<ComponentMap&>(src_comps).begin();
	for (; iter; ++iter) {
		TypeCls comp_type = iter.key();
		TypeCls cls; TODO
		
		Base* new_component = CreateComponent(cls);
		dst.InitializeComponent(*new_component);
		iter.value().CopyTo(new_component);
		dst_comps.ComponentMapBase::Add(comp_type, new_component);
	}
}

void ComponentStore::ReturnComponent(Base* c) {
	ASSERT(c);
	TypeCls type = c->GetTypeId();
	
	auto iter = EcsFactory::refurbishers.Find(type);
	if (iter)
		iter.Get()(c);
}

ComponentBase* ComponentStore::CreateComponent(TypeCls cls) {
	auto iter = EcsFactory::producers.Find(cls);
	ASSERT_(iter, "Invalid to create non-existant component");
	
	ComponentBase* obj = iter.value()();
	return obj;
}

ComponentBase* ComponentStore::CreateComponentTypeCls(TypeCls cls) {
	auto it = Factory::producers.Find(cls);
	if (!it) {
		auto new_fn = Ecs::ComponentFactory::CompDataMap().Get(cls).new_fn;
		std::function<ComponentBase*()> p([new_fn] { return new_fn();});
		std::function<void(ComponentBase*)> r([] (Base* b){ delete b;});
		Factory::producers.Add(cls) = p;
		Factory::refurbishers.Add(cls) = r;
	}
	
	return CreateComponent(cls);
}



NAMESPACE_ECS_END

