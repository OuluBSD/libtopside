#ifndef _EcsCore_ConnAny_h_
#define _EcsCore_ConnAny_h_

NAMESPACE_TOPSIDE_BEGIN


class AnyConnector :
	public ManualConnector,
	virtual public ConnectorBase
{
	
protected:
	int tmp_link_count = 0;
	
	template <class ValDevSpec>
	void Visit(typename ScopeValDevCoreT<ValDevSpec>::ValSourceRef src, PoolRef pool) {
		using Source = typename ScopeValDevCoreT<ValDevSpec>::ValSource;
		using Sink = typename ScopeValDevCoreT<ValDevSpec>::ValSink;
		
		for (EntityRef& e : *pool) {
			auto sink = e->FindInterface<Sink>();
			if (sink) {
				CookieRef src_cookie, sink_cookie;
				if (src->Accept(sink, src_cookie, sink_cookie)) {
					Ref<typename Source::ExPt> ep = MetaExchangePoint::Add<typename Source::ExPt>();
					RTLOG("AnyConnector::Visit<ValDevSpec>(src,pool): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
					src->Link(ep, sink, src_cookie, sink_cookie);
					ep->Init(this);
					ep->Set(src, sink, src_cookie, sink_cookie);
					++tmp_link_count;
				}
			}
		}
		
		for (auto iter = pool->BeginPool(); iter; ++iter) {
			Visit<ValDevSpec>(src, *iter);
		}
	}

	
public:
	RTTI_DECL1(ManualConnector, MetaExchangePoint)
	
	template <class ValDevSpec>
	bool LinkAny(typename ScopeValDevCoreT<ValDevSpec>::ValSourceRef src) {
		tmp_link_count = 0;
		PoolRef pool = ConnectorBase::GetPool();
		Visit<ValDevSpec>(src, pool);
		return tmp_link_count > 0;
	}
	
};


NAMESPACE_TOPSIDE_END

#endif
