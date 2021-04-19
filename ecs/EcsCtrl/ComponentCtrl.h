#ifndef _EcsCtrl_ComponentCtrl_h_
#define _EcsCtrl_ComponentCtrl_h_


NAMESPACE_OULU_BEGIN


class ComponentCtrl : public ParentCtrl {
	
	
public:
	typedef ComponentCtrl CLASSNAME;
	ComponentCtrl() {}
	
	virtual void SetComponent(ComponentBase& c) = 0;
	
};

typedef ComponentCtrl*(*ComponentCtrlFactory)();
typedef VectorMap<TypeId, ComponentCtrlFactory> ComponentCtrlFactoryMap;

void RegisterComponentCtrlFactory(TypeId comp, ComponentCtrlFactory fac);
ComponentCtrl* NewComponentCtrl(TypeId comp);

template <class T> ComponentCtrl* ComponentCtrlFactoryFn() {return new T();}
template <class I, class C> void MakeComponentCtrlFactory() {
	RegisterComponentCtrlFactory(typeid(I), &ComponentCtrlFactoryFn<C>);
}

NAMESPACE_OULU_END


#endif
