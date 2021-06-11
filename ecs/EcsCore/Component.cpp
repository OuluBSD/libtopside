#include "EcsCore.h"

NAMESPACE_TOPSIDE_BEGIN


ComponentBase::ComponentBase() {
	DBG_CONSTRUCT
}

ComponentBase::~ComponentBase() {
	DBG_DESTRUCT
}

Machine& ComponentBase::GetMachine() {
	return GetParent()->GetMachine();
}

EntityRef ComponentBase::GetEntity() {
	return GetParent()->AsRefT();
}

String ComponentBase::ToString() const {
	return GetDynamicName();
}

InterfaceSourceBaseRef ComponentBase::FindSource(TypeCls t) {
	TODO
}

InterfaceSinkBaseRef ComponentBase::FindSink(TypeCls t) {
	TODO
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


NAMESPACE_TOPSIDE_END
