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
	int tmp_link_count = 0;
	
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
	
	bool LinkAll();
	bool LinkAny(SourceRef src);
	bool LinkManually(SourceRef src, SinkRef sink);
	
	
private:
	
	void Visit(PoolRef pool, LinkedList<LinkedList<Ref<T>>>& src_stack);
	void Visit(SourceRef src, PoolRef pool);
	
};

template <class Source, class T> bool ComponentBase::LinkManually(T& o, String* err_msg) {
	using ConnAll = ConnectAllInterfaces<Source>;
	using Sink = typename Source::SinkClass;
	EntityRef src_e = GetEntity();
	EntityRef sink_e = o.GetEntity();
	
	RefT_Pool<ConnAll> conn = src_e->FindCommonConnector<ConnAll>(sink_e);
	if (!conn) {
		if (err_msg)
			*err_msg = "could not find common connector for ConnectAllInterfaces<" + AsTypeString<Source>() + ">";
		return false;
	}
	
	RefT_Entity<Source> src		= src_e		->FindInterface<Source>();
	if (!src) {
		if (err_msg)
			*err_msg = "could not find source interface " + AsTypeString<Source>();
		return false;
	}
	
	RefT_Entity<Sink> sink		= sink_e	->FindInterface<Sink>();
	if (!sink) {
		if (err_msg)
			*err_msg = "could not find sink interface for " + AsTypeString<Sink>();
		return false;
	}
	
	return conn->LinkManually(src, sink);
}


NAMESPACE_TOPSIDE_END


#include "ConnPoolComps.inl"

#endif
