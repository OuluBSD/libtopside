#ifndef _EcsLib_Customer_h_
#define _EcsLib_Customer_h_

NAMESPACE_TOPSIDE_BEGIN



class CustomerComponent : public Component<CustomerComponent> {
	VIS_COMP_0_0
	
public:
	RTTI_COMP0(CustomerComponent)
	COPY_PANIC(CustomerComponent)
	void Visit(RuntimeVisitor& vis) override {}
	
	virtual void Initialize() override;
	virtual void Uninitialize() override;
	
};




PREFAB_BEGIN(Customer)
	CustomerComponent
PREFAB_END


NAMESPACE_TOPSIDE_END

#endif
