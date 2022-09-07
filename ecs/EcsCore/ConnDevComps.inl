#if 0
#define TMPL(x) template <class DevSpec> x ConnectAllDevInterfaces<DevSpec>::
	
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
	PoolRef pool = ConnectorBase::GetPool();
	VisitUnlink(pool);
}

TMPL(void) VisitUnlink(PoolRef pool) {
	for (EntityRef& e : *pool) {
		for(ComponentBaseRef& comp : e->GetComponents().GetValues()) {
			CollectInterfacesVisitor vis;
			vis.Visit(*comp);
			for(InterfaceSourceBaseRef& src : vis.src_ifaces) {
				src->UnlinkAll();
			}
			for(InterfaceSinkBaseRef& src : vis.sink_ifaces) {
				src->UnlinkAll();
			}
		}
	}
	
	for (auto iter = pool->BeginPool(); iter; ++iter) {
		VisitUnlink(*iter);
	}
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
	LinkedList<InterfaceSourceBaseRef>* cur = 0;
	
	for (EntityRef& e : *pool) {
		for(ComponentBaseRef& comp : e->GetComponents().GetValues()) {
			CollectInterfacesVisitor vis;
			vis.Visit(*comp);
			for(InterfaceSourceBaseRef& src : vis.src_ifaces) {
				if (!cur)
					cur = &src_stack.Add();
				if (src->GetDevSpec() == AsTypeCls<DevSpec>())
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
							//LOG(IntStr64(sink_cls) << " == " << IntStr64(src_sink_cls));
							if (sink_cls == src_sink_cls) {
								TypeCls valdev_spec = sink->GetValDevSpec();
								ASSERT(valdev_spec == (TypeCls)src->GetValDevSpec());
								CookieRef src_cookie, sink_cookie;
								if (src->Accept(sink, src_cookie, sink_cookie)) {
									ValExchangePointBaseRef ep =
										MetaExchangePoint::Add<ValExchangePointBase>(ValExchangePointBase::Create(valdev_spec));
									ASSERT(ep);
									RTLOG("ConnectAllDevInterfaces<DevSpec>::Visit(pool,stack): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
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
#endif
