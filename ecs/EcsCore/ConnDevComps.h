#ifndef _EcsCore_ConnDevComps_h_
#define _EcsCore_ConnDevComps_h_

NAMESPACE_TOPSIDE_BEGIN



template <class DevSpec>
class ConnectAllDevInterfaces :
	public Connector<ConnectAllDevInterfaces<DevSpec>>,
	public MetaExchangePoint
{
	using ConnectorT = Connector<ConnectAllDevInterfaces<DevSpec>>;
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
	
	template <class ValSpec> bool LinkAny(typename ScopeValDevCoreT<VD<DevSpec,ValSpec>>::ValSourceRef src) {
		return ConnectAllInterfaces<VD<DevSpec,ValSpec>>().LinkAny(src);
	}
	
	template <class ValSpec> bool LinkManually(
		typename ScopeValDevCoreT<VD<DevSpec,ValSpec>>::ValSourceRef src,
		typename ScopeValDevCoreT<VD<DevSpec,ValSpec>>::ValSinkRef sink) {
		return ConnectAllInterfaces<VD<DevSpec,ValSpec>>().LinkManually(src, sink);
	}
	
private:
	
	void VisitUnlink(PoolRef pool);
	void Visit(PoolRef pool, LinkedList<LinkedList<InterfaceSourceBaseRef>>& src_stack);
	
	
};



NAMESPACE_TOPSIDE_END

#endif
