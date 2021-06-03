NAMESPACE_TOPSIDE_BEGIN


template <class ValDevSpec>
void ConnectAllInterfaces<ValDevSpec>::Initialize() {
	Machine& m = ConnectorBase::GetPool()->GetMachine();
	sys = m.Get<EntityStore>();
	ASSERT_(sys, "EntityStore is required for MetaExchangePoints");
}


template <class ValDevSpec>
void ConnectAllInterfaces<ValDevSpec>::Uninitialize() {
	UnlinkAll();
}

template <class ValDevSpec>
void ConnectAllInterfaces<ValDevSpec>::UnlinkAll() {
	Machine& mach = ConnectorBase::GetPool()->GetMachine();
	
	if (!mach.IsRunning()) {
		for (ExchangePointRef& pt : pts) {
			pt->Source()	->UnlinkAll();
			pt->Sink()		->UnlinkAll();
		}
	}
	else {
		for (ExchangePointRef& pt : pts) {
			pt->Source()	->Unlink(pt->Sink());
		}
	}
	
	pts.Clear();
}

template <class ValDevSpec>
void ConnectAllInterfaces<ValDevSpec>::Visit(PoolRef pool, LinkedList<LinkedList<Ref<Source>>>& src_stack) {
	LinkedList<Ref<Source>>* cur = 0;
	
	for (EntityRef& e : *pool) {
		Ref<Source> src = e->FindInterface<Source>();
		if (src) {
			if (!cur)
				cur = &src_stack.Add();
			cur->Add(src);
		}
	}
	
	for (EntityRef& e : *pool) {
		auto sink = e->FindInterface<Sink>();
		if (sink) {
			for(LinkedList<Ref<Source>>& src_scope : src_stack) {
				for (Ref<Source>& src : src_scope) {
					CookieRef src_cookie, sink_cookie;
					if (src->Accept(sink, src_cookie, sink_cookie)) {
						Ref<typename Source::ExPt> ep = MetaExchangePoint::Add<typename Source::ExPt>();
						RTLOG("ConnectAllInterfaces<ValDevSpec>::Visit(pool,stack): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
						src->Link(ep, sink, src_cookie, sink_cookie);
						ep->Init(this);
						ep->Set(src, sink, src_cookie, sink_cookie);
						++tmp_link_count;
					}
				}
			}
		}
	}
	
	for (auto iter = pool->BeginPool(); iter; ++iter) {
		Visit(*iter, src_stack);
	}
	
	if (cur)
		src_stack.RemoveLast();
}

template <class ValDevSpec>
void ConnectAllInterfaces<ValDevSpec>::Visit(SourceRef src, PoolRef pool) {
	for (EntityRef& e : *pool) {
		auto sink = e->FindInterface<Sink>();
		if (sink) {
			CookieRef src_cookie, sink_cookie;
			if (src->Accept(sink, src_cookie, sink_cookie)) {
				Ref<typename Source::ExPt> ep = MetaExchangePoint::Add<typename Source::ExPt>();
				RTLOG("ConnectAllInterfaces<ValDevSpec>::Visit(src,pool): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
				src->Link(ep, sink, src_cookie, sink_cookie);
				ep->Init(this);
				ep->Set(src, sink, src_cookie, sink_cookie);
				++tmp_link_count;
			}
		}
	}
	
	for (auto iter = pool->BeginPool(); iter; ++iter) {
		Visit(src, *iter);
	}
}


template <class ValDevSpec>
void ConnectAllInterfaces<ValDevSpec>::Update(double dt) {
	LinkAll();
}

template <class ValDevSpec>
bool ConnectAllInterfaces<ValDevSpec>::LinkAll() {
	tmp_link_count = 0;
	PoolRef pool = ConnectorBase::GetPool();
	LinkedList<LinkedList<Ref<Source>>> src_stack;
	Visit(pool, src_stack);
	return tmp_link_count > 0;
}

template <class ValDevSpec>
bool ConnectAllInterfaces<ValDevSpec>::LinkAny(SourceRef src) {
	tmp_link_count = 0;
	PoolRef pool = ConnectorBase::GetPool();
	Visit(src, pool);
	return tmp_link_count > 0;
}

template <class ValDevSpec>
bool ConnectAllInterfaces<ValDevSpec>::LinkManually(SourceRef src, SinkRef sink) {
	ASSERT(src	->AsComponentBase()->GetEntity()->HasPoolParent(ConnectorBase::GetPool()));
	ASSERT(sink	->AsComponentBase()->GetEntity()->HasPoolParent(ConnectorBase::GetPool()));
	CookieRef src_cookie, sink_cookie;
	if (src->Accept(sink, src_cookie, sink_cookie)) {
		Ref<typename Source::ExPt> ep = MetaExchangePoint::Add<typename Source::ExPt>();
		RTLOG("ConnectAllInterfaces<ValDevSpec>::LinkManually: created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
		src->Link(ep, sink, src_cookie, sink_cookie);
		ep->Init(this);
		ep->Set(src, sink, src_cookie, sink_cookie);
		return true;
	}
	return false;
}


NAMESPACE_TOPSIDE_END
