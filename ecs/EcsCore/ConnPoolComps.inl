
NAMESPACE_OULU_BEGIN


template <class T>
void ConnectAllInterfaces<T>::Initialize() {
	MetaExchangePoint::Init(this);
	Machine& m = ConnectorBase::GetPool().GetMachine();
	sys = m.Get<EntityStore>();
	ASSERT_(sys, "EntityStore is required for MetaExchangePoints");
	Refresh();
}


template <class T>
void ConnectAllInterfaces<T>::Uninitialize() {
	UnlinkAll();
}

template <class T>
void ConnectAllInterfaces<T>::UnlinkAll() {
	MetaExchangePoint::UnlinkAll();
}

template <class T>
void ConnectAllInterfaces<T>::Visit(Ref<Pool> pool, Vector<Vector<Ref<T>>>& src_stack) {
	
	Vector<Ref<T>>* cur = 0;
	//int src_scope_count = src_stack.GetCount();
	
	for (EntityRef& e : *pool) {
		
		Ref<T> src = e->FindInterface<T>();
		
		if (src) {
			if (!cur)
				cur = &src_stack.Add();
			
			cur->Add(src);
		}
	}
	
	for (EntityRef& e : *pool) {
		Ref<Sink> sink = e->FindInterface<Sink>();
		if (sink) {
			for(Vector<Ref<T>>& src_scope : src_stack) {
				for (Ref<T>& src : src_scope) {
					if (src->LinkManually(*sink)) {
						ExchangePointRef ep = MetaExchangePoint::Add();
						
						ep->Set(&*src, &*sink);
					}
				}
			}
		}
	}
	
	for (auto iter = pool->BeginPool(); iter; ++iter) {
		Visit(*iter, src_stack);
	}
	
	if (cur)
		src_stack.Remove(src_stack.GetCount()-1);
	
}


template <class T>
void ConnectAllInterfaces<T>::Update(double dt) {
	Pool& pool = ConnectorBase::GetPool();
	Vector<Vector<Ref<T>>> src_stack;
	
	Visit(pool, src_stack);
	
}


NAMESPACE_OULU_END
