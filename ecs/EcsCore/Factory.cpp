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




NAMESPACE_ECS_END
