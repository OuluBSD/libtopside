#ifndef _EcsCore_ConnDevComps_h_
#define _EcsCore_ConnDevComps_h_

NAMESPACE_TOPSIDE_BEGIN



template <class DevSpec>
class ConnectAllDevInterfaces :
	public Connector<ConnectAllDevInterfaces<DevSpec>>,
	public AnyConnector
{
	using ConnectorT = Connector<ConnectAllDevInterfaces<DevSpec>>;
	Ref<EntityStore> sys;
	
	int64 refresh_ticks = -1;
	int tmp_link_count = 0;
	
public:
	RTTI_DECL_2(ConnectAllDevInterfaces, ConnectorT, AnyConnector, "ConnectAll" + DevSpec::GetName() + "Interfaces")
	COPY_PANIC(ConnectAllDevInterfaces);
	
	void CopyTo(ConnectorBase* component) const override {}
	void Initialize() override;
	void Uninitialize() override;
	String ToString() const override {return MetaExchangePoint::ToString();}
	void UnlinkAll() override;
	void Update(double dt=0) override;
	void Visit(RuntimeVisitor& vis) override {
		vis & sys;
		MetaExchangePoint::Visit(vis);
	}
	TypeId GetType() const override {return AsTypeCls<ConnectAllDevInterfaces<DevSpec>>();}
	
	bool LinkAll();
	
	
private:
	
	void VisitUnlink(PoolRef pool);
	void Visit(PoolRef pool, LinkedList<LinkedList<InterfaceSourceBaseRef>>& src_stack);
	
	
};


#define DEV(x) using ConnectAll##x##Interfaces = ConnectAllDevInterfaces<x##Spec>;
DEV_LIST
#undef DEV


NAMESPACE_TOPSIDE_END

#endif
