#ifndef _EcsCore_ConnPoolComps_h_
#define _EcsCore_ConnPoolComps_h_


NAMESPACE_TOPSIDE_BEGIN


template <class T>
class ConnectAllInterfaces :
	public Connector<ConnectAllInterfaces<T>>,
	public MetaExchangePoint
{
	using ConnectorT = Connector<ConnectAllInterfaces<T>>;
	Ref<EntityStore> sys;
	
	int64 refresh_ticks = -1;
	
	
public:
	RTTI_DECL2(ConnectAllInterfaces, ConnectorT, MetaExchangePoint)
	COPY_PANIC(ConnectAllInterfaces);
	
	using Source	= T;
	using Sink		= typename T::SinkClass;
	using ISource	= InterfaceSource<Source, Sink>;
	using ISink		= InterfaceSink<Sink>;
	using SourceRef	= RefT_Entity<Source>;
	using SinkRef	= RefT_Entity<Sink>;
	
	void Refresh() {if (sys) refresh_ticks = sys->PostRefresh(refresh_ticks, this);}
	TypeId GetType() const override {return AsTypeCls<ConnectAllInterfaces<T>>();}
	void CopyTo(ConnectorBase* component) const override {}
	void Initialize() override;
	void Uninitialize() override;
	String ToString() const override {return MetaExchangePoint::ToString();}
	void UnlinkAll() override;
	void Update(double dt) override;
	void Visit(RuntimeVisitor& vis) override {
		vis & sys;
		MetaExchangePoint::Visit(vis);
	}
		
	bool LinkManually(SourceRef src, SinkRef sink);
	
	
private:
	
	void Visit(PoolRef pool, LinkedList<LinkedList<Ref<T>>>& src_stack);
	
};

template <class Source, class T> bool ComponentBase::LinkManually(T& o) {
	using ConnAll = ConnectAllInterfaces<T>;
	using Sink = typename Source::Sink;
	EntityRef src_e = GetEntity();
	EntityRef sink_e = o.GetEntity();
	
	RefT_Pool<ConnAll> conn = src_e->FindConnector<ConnAll>(sink_e);
	if (!conn)
		return false;
	
	RefT_Entity<Source> src		= src_e		->FindInterface<Source>();
	if (!src)
		return false;
	
	RefT_Entity<Sink> sink		= sink_e	->FindInterface<Sink>();
	if (!sink)
		return false;
	
	return conn->LinkManually(src, sink);
}


NAMESPACE_TOPSIDE_END


#include "ConnPoolComps.inl"

#endif
