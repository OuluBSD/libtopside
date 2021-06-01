#ifndef _EcsCore_ConnDevComps_h_
#define _EcsCore_ConnDevComps_h_

NAMESPACE_TOPSIDE_BEGIN



template <class T>
class ConnectAllDevInterfaces :
	public Connector<ConnectAllDevInterfaces<T>>,
	public MetaExchangePoint
{
	using ConnectorT = Connector<ConnectAllDevInterfaces<T>>;
	Ref<EntityStore> sys;
	
	int64 refresh_ticks = -1;
	int tmp_link_count = 0;
	
public:
	RTTI_DECL2(ConnectAllDevInterfaces, ConnectorT, MetaExchangePoint)
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
	bool LinkAll();
	
private:
	
	void Visit(PoolRef pool, LinkedList<LinkedList<InterfaceSourceBaseRef>>& src_stack);
	
	
};



NAMESPACE_TOPSIDE_END

#endif
