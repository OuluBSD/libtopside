#ifndef _EcsLib_Component_h_
#define _EcsLib_Component_h_

NAMESPACE_TOPSIDE_BEGIN



template<typename DevSpec, typename ValSpec, typename T>
struct DevComponent :
	Component<T>,
	ScopeDevMachT<DevSpec>::DevComponent
{
	using ComponentT = Component<T>;
	using DevComponentT = typename ScopeDevMachT<DevSpec>::DevComponent;
	
	RTTI_DECL2(DevComponent, ComponentT, DevComponentT);
	
	TypeCls GetValSpec() const override {return AsTypeCls<ValSpec>();}
	
};



NAMESPACE_TOPSIDE_END

#endif
