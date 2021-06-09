#ifndef _EcsCore_ConnPoolComps_h_
#define _EcsCore_ConnPoolComps_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


template <class ValDevSpec>
class ConnectAllInterfaces :
	public Connector<ConnectAllInterfaces<ValDevSpec>>,
	public AnyConnector
{
	using ConnectorT = Connector<ConnectAllInterfaces<ValDevSpec>>;
	Ref<EntityStore> sys;
	
	
public:
	RTTI_DECL2(ConnectAllInterfaces, ConnectorT, MetaExchangePoint)
	COPY_PANIC(ConnectAllInterfaces);
	
	
	using Source	= typename ScopeValDevCoreT<ValDevSpec>::ValSource;
	using Sink		= typename Source::Sink;
	using ISource	= InterfaceSource<Source, Sink>;
	using ISink		= InterfaceSink<Sink>;
	using SourceRef	= RefT_Entity<Source>;
	using SinkRef	= RefT_Entity<Sink>;
	
	TypeCls GetType() const override {return AsTypeCls<ConnectAllInterfaces<ValDevSpec>>();}
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
	
	void Visit(PoolRef pool, LinkedList<LinkedList<Ref<Source>>>& src_stack);
	
};


NAMESPACE_TOPSIDE_END



#endif
#endif
