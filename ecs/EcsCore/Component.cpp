#include "EcsCore.h"

NAMESPACE_ECS_BEGIN








ComponentBase::ComponentBase() {
	DBG_CONSTRUCT
}

ComponentBase::~ComponentBase() {
	DBG_DESTRUCT
}

Machine& ComponentBase::GetMachine() {
	return GetParent()->GetMachine();
}

void ComponentBase::UninitializeWithExt() {
	ClearExtension();
	Uninitialize();
	ClearSinkSource();
}

EntityRef ComponentBase::GetEntity() {
	return GetParent()->AsRefT();
}

String ComponentBase::ToString() const {
	return GetDynamicName();
}

/*InterfaceSourceRef ComponentBase::FindSource(ValDevCls t) {
	CollectInterfacesVisitor vis;
	vis.Visit(*this);
	for (InterfaceSourceRef& r : vis.src_ifaces) {
		if (r->GetSourceCls() == t)
			return r;
	}
	return InterfaceSourceBaseRef();
}

InterfaceSinkRef ComponentBase::FindSink(ValDevCls t) {
	ASSERT(t != AsTypeCls<InterfaceSinkBase>());
	CollectInterfacesVisitor vis;
	vis.Visit(*this);
	for (InterfaceSinkBaseRef& r : vis.sink_ifaces) {
		if (r->GetSinkCls() == t)
			return r;
	}
	return InterfaceSinkBaseRef();
}*/

ComponentExtBaseRef ComponentBase::SetExtensionTypeCls(EcsTypeCls ext) {
	EcsTypeCls comp = GetType();
	const auto& cd = Ecs::Factory::CompDataMap().Get(comp);
	for (const auto& e : cd.ext.GetValues()) {
		if (e.cls == ext) {
			ComponentExtBase* b = e.new_fn();
			if (SetExtension(b))
				return GetExtension();
			break;
		}
	}
	return ComponentExtBaseRef();
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
