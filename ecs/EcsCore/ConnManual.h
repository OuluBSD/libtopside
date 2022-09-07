#ifndef _EcsCore_ConnManual_h_
#define _EcsCore_ConnManual_h_

NAMESPACE_TOPSIDE_BEGIN


class ManualConnector :
	public MetaExchangePoint,
	virtual public ConnectorBase
{
	
public:
	RTTI_DECL1(ManualConnector, MetaExchangePoint)
	
	void Visit(RuntimeVisitor& vis) override {
		MetaExchangePoint::Visit(vis);
	}
	
	template <class ValDevSpec> bool LinkManually(
		typename ScopeValDevCoreT<ValDevSpec>::ValSourceRef src,
		typename ScopeValDevCoreT<ValDevSpec>::ValSinkRef sink) {
		using Source = typename ScopeValDevCoreT<ValDevSpec>::ValSource;
		using Sink = typename ScopeValDevCoreT<ValDevSpec>::ValSink;
		using SourceRef = typename ScopeValDevCoreT<ValDevSpec>::ValSourceRef;
		using SinkRef = typename ScopeValDevCoreT<ValDevSpec>::ValSinkRef;
		
		ASSERT(src	->AsComponentBase()->GetEntity()->HasPoolParent(ConnectorBase::GetPool()));
		ASSERT(sink	->AsComponentBase()->GetEntity()->HasPoolParent(ConnectorBase::GetPool()));
		CookieRef src_cookie, sink_cookie;
		if (src->Accept(sink, src_cookie, sink_cookie)) {
			Ref<typename Source::ExPt> ep = MetaExchangePoint::Add<typename Source::ExPt>();
			RTLOG("ManualConnector::LinkManually<ValDevSpec>: created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
			src->Link(ep, sink, src_cookie, sink_cookie);
			ep->Init(this);
			ep->Set(src, sink, src_cookie, sink_cookie);
			return true;
		}
		return false;
	}
	
	bool LinkManually(ComponentBaseRef src_comp, ComponentBaseRef dst_comp, TypeCls iface, TypeCls sink_iface);
	
};


class ConnectManuallyInterfaces :
	public Connector<ConnectManuallyInterfaces>,
	public ManualConnector
{
	using ConnectorT = Connector<ConnectManuallyInterfaces>;
	Ref<EntityStore> sys;
	
public:
	RTTI_DECL2(ConnectManuallyInterfaces, ConnectorT, ManualConnector)
	COPY_PANIC(ConnectManuallyInterfaces);
	
	void Initialize() override;
	void Uninitialize() override;
	String ToString() const override {return MetaExchangePoint::ToString();}
	void UnlinkAll() override;
	void Update(double dt=0) override;
	void Visit(RuntimeVisitor& vis) override {
		vis & sys;
		ManualConnector::Visit(vis);
	}
	
};

using ConnectManuallyInterfacesRef = RefT_Pool<ConnectManuallyInterfaces>;



template <class ValDevSpec, class T> bool ComponentBase::LinkManually(T& o, String* err_msg) {
	using ManConn = ManualConnector;
	using Source = typename ScopeValDevCoreT<ValDevSpec>::ValSource;
	using Sink = typename ScopeValDevCoreT<ValDevSpec>::ValSink;
	
	EntityRef src_e = GetEntity();
	EntityRef sink_e = o.GetEntity();
	
	RefT_Pool<ManConn> conn = src_e->FindCommonConnector<ManConn>(sink_e);
	if (!conn) {
		if (err_msg)
			*err_msg = "could not find common connector for ManualConnector";
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

#endif
