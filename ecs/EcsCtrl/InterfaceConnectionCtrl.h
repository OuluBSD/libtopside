#ifndef _EcsCtrl_InterfaceConnectionCtrl_h_
#define _EcsCtrl_InterfaceConnectionCtrl_h_

NAMESPACE_TOPSIDE_BEGIN


class InterfaceConnectionGraph : public Ctrl {
	
	
public:
	RTTI_DECL1(InterfaceConnectionGraph, Ctrl)
	typedef InterfaceConnectionGraph CLASSNAME;
	InterfaceConnectionGraph();
	
	void Updated() override;
	
};



NAMESPACE_TOPSIDE_END

#endif
