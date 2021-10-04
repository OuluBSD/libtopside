#include "EcsCore.h"

NAMESPACE_ECS_BEGIN








ComponentBase::ComponentBase() {
	DBG_CONSTRUCT
}

ComponentBase::~ComponentBase() {
	DBG_DESTRUCT
}

Engine& ComponentBase::GetEngine() {
	return GetParent()->GetEngine();
}

EntityRef ComponentBase::GetEntity() {
	return GetParent()->AsRefT();
}

String ComponentBase::ToString() const {
	return GetDynamicName();
}





void ComponentMap::Dump() {
	auto iter = ComponentMapBase::begin();
	for(int i = 0; iter; ++iter, ++i) {
		LOG(i << ": " <<
			iter.value().GetDynamicName() << ": \"" <<
			iter.value().ToString() << "\"");
	}
}

void ComponentMap::ReturnComponent(ComponentStore& s, ComponentBase* c) {
	s.ReturnComponent(c);
}




















NAMESPACE_ECS_END
