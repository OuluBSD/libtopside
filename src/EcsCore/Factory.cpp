#include "EcsCore.h"

NAMESPACE_ECS_BEGIN



void ComponentFactory::Dump() {
	const auto& fns = CompDataMap();
	
	LOG("ComponentFactory::Dump:");
	LOG("\tcomponents (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name);
	}
}

ComponentBase* ComponentFactory::CreateComponent(TypeCls type) {
	int i = CompDataMap().Find(type);
	if (i < 0) return 0;
	CompData& d = CompDataMap()[i];
	return d.new_fn();
}

String ComponentFactory::GetComponentName(TypeCls type) {
	for (CompData& c : CompDataMap().GetValues()) {
		if (c.rtti_cls == type)
			return c.name;
	}
	return "";
}

TypeCls ComponentFactory::GetComponentType(String name) {
	for (CompData& c : CompDataMap().GetValues()) {
		if (c.name == name)
			return c.rtti_cls;
	}
	return TypeCls();
}



NAMESPACE_ECS_END
