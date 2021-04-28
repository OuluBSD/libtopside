
NAMESPACE_OULU_BEGIN


template <class T>
void ConnectAllInterfaces<T>::Visit(Ref<EntityPool> pool, Vector<Vector<Ref<T>>>& src_stack) {
	using Sink = typename T::Sink;
	Vector<Ref<T>>* cur = 0;
	//int parent_scope_count = src_stack.GetCount();
	
	for (EntityRef& e : *pool) {
		
		Ref<T> src = e->FindInterface<T>();
		
		if (src) {
			LOG("src");
			if (!cur)
				cur = &src_stack.Add();
			
			cur->Add(src);
		}
	}
	
	for (EntityRef& e : *pool) {
		Ref<Sink> sink = e->FindInterface<Sink>();
		if (sink) {
			LOG("sink");
			//int i = 0;
			for(Vector<Ref<T>>& parent_scope : src_stack) {
				//if (i++ >= parent_scope_count)
				//	break;
				for (Ref<T>& parent : parent_scope) {
					LOG("link");
					parent->LinkManually(*sink);
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
	EntityPool& pool = PoolComponentBase::GetPool();
	Vector<Vector<Ref<T>>> src_stack;
	
	Visit(pool, src_stack);
	
}



NAMESPACE_OULU_END
