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

InterfaceSourceRef ComponentBase::FindSource(ValDevCls t) {
	TODO
	/*ASSERT(t != AsTypeCls<InterfaceSourceBase>());
	CollectInterfacesVisitor vis;
	vis.Visit(*this);
	for (InterfaceSourceBaseRef& r : vis.src_ifaces) {
		void* r_ptr = &*r;
		void* type_ptr = r->GetBasePtrOver(t, r_ptr);
		if (type_ptr)
			return r;
	}
	return InterfaceSourceBaseRef();*/
}

InterfaceSinkRef ComponentBase::FindSink(ValDevCls t) {
	TODO
	/*ASSERT(t != AsTypeCls<InterfaceSinkBase>());
	CollectInterfacesVisitor vis;
	vis.Visit(*this);
	for (InterfaceSinkBaseRef& r : vis.sink_ifaces) {
		void* r_ptr = &*r;
		void* type_ptr = r->GetBasePtrOver(t, r_ptr);
		if (type_ptr)
			return r;
	}
	return InterfaceSinkBaseRef();*/
}

ComponentExtBaseRef ComponentBase::SetExtensionTypeCls(TypeCls ext) {
	TypeCls comp = GetTypeId();
	TODO
	/*const auto& cd = Ecs::Factory::CompDataMap().Get(comp);
	for (const auto& e : cd.ext.GetValues()) {
		if (e.cls == ext) {
			ComponentExtBase* b = e.new_fn();
			if (SetExtension(b))
				return GetExtension();
			break;
		}
	}
	return ComponentExtBaseRef();*/
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
