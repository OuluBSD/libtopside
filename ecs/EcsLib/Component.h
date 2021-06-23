#ifndef _EcsLib_Component_h_
#define _EcsLib_Component_h_

NAMESPACE_ECS_BEGIN



template<typename T, class Ext>
class DevComponent :
	public Component<T,Ext>,
	public DevComponentBase
{
	bool is_open = false;
public:
	using ComponentT = Component<T,Ext>;
	
	RTTI_DECL2(DevComponent, ComponentT, DevComponentBase);
	
	DevComponent(ValDevCls vd);
	void Initialize() override {ASSERT(!is_open); DevComponentBase::Initialize(); is_open = true;}
	void Uninitialize() override {ASSERT(is_open); DevComponentBase::Uninitialize(); is_open = false;}
	
	TypeCls GetValSpec() const override; // {return AsTypeCls<ValSpec>();}
	void ForwardPackets(double dt) override;
	
};


NAMESPACE_ECS_END

#endif
