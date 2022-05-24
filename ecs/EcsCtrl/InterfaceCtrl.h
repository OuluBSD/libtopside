#ifndef _EcsCtrl_InterfaceCtrl_h_
#define _EcsCtrl_InterfaceCtrl_h_


NAMESPACE_TOPSIDE_BEGIN


class InterfaceCtrl : public ParentCtrl {
	
	
public:
	typedef InterfaceCtrl CLASSNAME;
	InterfaceCtrl() {}
	
	virtual void SetInterface(Ecs::ComponentBaseRef c, ExchangeProviderBaseRef b) = 0;
	
};

typedef InterfaceCtrl*(*InterfaceCtrlFactory)();
typedef VectorMap<TypeId, InterfaceCtrlFactory> InterfaceCtrlFactoryMap;

void RegisterInterfaceCtrlFactory(TypeId iface, InterfaceCtrlFactory fac);
InterfaceCtrl* NewInterfaceCtrl(TypeId iface);

template <class T> InterfaceCtrl* InterfaceCtrlFactoryFn() {return new T();}
template <class I, class C> void MakeInterfaceCtrlFactory() {
	RegisterInterfaceCtrlFactory(AsTypeCls<I>(), &InterfaceCtrlFactoryFn<C>);
}

NAMESPACE_TOPSIDE_END

#endif
