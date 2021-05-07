#include "EcsCore.h"

NAMESPACE_OULU_BEGIN


ComponentBase::ComponentBase() {
	DBG_CONSTRUCT
}

ComponentBase::~ComponentBase() {
	DBG_DESTRUCT
}

Machine& ComponentBase::GetMachine() {
	return ent->GetMachine();
}




void ComponentMap::Dump() {
	auto iter = ComponentMapBase::begin();
	for(int i = 0; iter; ++iter, ++i) {
		LOG(i << ": " <<
			iter.key().CleanDemangledName() << ": \"" <<
			iter.value().ToString() << "\"");
	}
}

void ComponentMap::ReturnComponent(ComponentStore& s, ComponentBase* c) {
	s.ReturnComponent(c);
}


NAMESPACE_OULU_END
