#ifndef _EcsLib_Component_h_
#define _EcsLib_Component_h_

NAMESPACE_TOPSIDE_BEGIN



template<typename DevSpec, typename ValSpec, typename T, class Sink, class Source, class Ext>
class DevComponent :
	public Component<T,Sink,Source,Ext>,
	public ScopeDevMachT<DevSpec>::DevComponent
{
	bool is_open = false;
public:
	using ComponentT = Component<T,Sink,Source,Ext>;
	using DevComponentT = typename ScopeDevMachT<DevSpec>::DevComponent;
	
	RTTI_DECL2(DevComponent, ComponentT, DevComponentT);
	
	
	void Initialize() override {ASSERT(!is_open); ScopeDevMachT<DevSpec>::DevComponent::Initialize(); is_open = true;}
	void Uninitialize() override {ASSERT(is_open); ScopeDevMachT<DevSpec>::DevComponent::Uninitialize(); is_open = false;}
	
	TypeCls GetValSpec() const override {return AsTypeCls<ValSpec>();}
	void ForwardPackets(double dt) override;
	
};





class GeneratorComponentBase : RTTIBase {
	
protected:
	RealtimeSourceConfig cfg;
	off32_gen gen;
	
public:
	RTTI_DECL0(GeneratorComponentBase)
	GeneratorComponentBase() : cfg(gen) {}
	
	
};



NAMESPACE_TOPSIDE_END

#endif
