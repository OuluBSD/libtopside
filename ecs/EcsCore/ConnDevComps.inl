#define TMPL(x) template <class T> x ConnectAllDevInterfaces<T>::
	
NAMESPACE_TOPSIDE_BEGIN



TMPL(void) Initialize() {
	Machine& m = ConnectorBase::GetPool()->GetMachine();
	sys = m.Get<EntityStore>();
	ASSERT_(sys, "EntityStore is required for MetaExchangePoints");
}

TMPL(void) Uninitialize() {
	UnlinkAll();
}

TMPL(void) UnlinkAll() {
	TODO
}

TMPL(void) Update(double dt) {
	LinkAll();
}

TMPL(bool) LinkAll() {
	tmp_link_count = 0;
	PoolRef pool = ConnectorBase::GetPool();
	LinkedList<LinkedList<InterfaceSourceBaseRef>> src_stack;
	Visit(pool, src_stack);
	return tmp_link_count > 0;
}

TMPL(void) Visit(PoolRef pool, LinkedList<LinkedList<InterfaceSourceBaseRef>>& src_stack) {
	using ExPt = typename ScopeDevEcsT<T>::ExchangePoint;
	
	LinkedList<InterfaceSourceBaseRef>* cur = 0;
	
	for (EntityRef& e : *pool) {
		for(ComponentBaseRef& comp : e->GetComponents().GetValues()) {
			CollectInterfacesVisitor vis;
			vis.Visit(*comp);
			for(InterfaceSourceBaseRef& src : vis.src_ifaces) {
				if (!cur)
					cur = &src_stack.Add();
				cur->Add(src);
			}
		}
	}
	
	for (EntityRef& e : *pool) {
		for(ComponentBaseRef& comp : e->GetComponents().GetValues()) {
			CollectInterfacesVisitor vis;
			vis.Visit(*comp);
			for(InterfaceSinkBaseRef& sink : vis.sink_ifaces) {
				if (sink) {
					TypeCls sink_cls = sink->GetSinkCls();
					for(LinkedList<InterfaceSourceBaseRef>& src_scope : src_stack) {
						for (InterfaceSourceBaseRef& src : src_scope) {
							TypeCls src_sink_cls = src->GetSinkCls();
							if (sink_cls == src_sink_cls) {
								CookieRef src_cookie, sink_cookie;
								if (src->Accept(sink, src_cookie, sink_cookie)) {
									Ref<ExPt> ep = MetaExchangePoint::Add<ExPt>();
									RTLOG("ConnectAllDevInterfaces<T>::Visit(pool,stack): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
									src->Link(ep, sink, src_cookie, sink_cookie);
									ep->Init(this);
									ep->Set(src, sink, src_cookie, sink_cookie);
									++tmp_link_count;
								}
							}
						}
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


NAMESPACE_TOPSIDE_END

#undef TMPL
