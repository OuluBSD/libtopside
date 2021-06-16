#ifndef _EcsCore_Pool_h_
#define _EcsCore_Pool_h_


NAMESPACE_TOPSIDE_BEGIN

class Pool;



class Pool :
	public RefScopeEnabler<Pool,EntityStore,RefParent2<EntityStore, Pool>>
{
	Machine*			machine = 0;
	BitField<dword>		freeze_bits;
	String				name;
	PoolId				id;
	
protected:
	friend class EntityStore;
	
	void SetId(PoolId i) {id = i;}
	
public:
	typedef Pool CLASSNAME;
	
	static PoolId GetNextId();
	
	RTTI_DECL_R0(Pool)
	Pool();
	~Pool();
	
	typedef enum {
		BIT_OVERLAP,
		BIT_TRANSFORM,
	} Bit;
	
	
	PoolId GetId() const {return id;}
	
	void SetName(String s)			{name = s;}
	void FreezeTransform()			{freeze_bits.Set(BIT_TRANSFORM, true);}
	void FreezeOverlap()			{freeze_bits.Set(BIT_OVERLAP, true);}
	bool IsFrozenTransform() const	{return freeze_bits.Is(BIT_TRANSFORM);}
	bool IsFrozenOverlap() const	{return freeze_bits.Is(BIT_OVERLAP);}
	
	void				ReverseEntities();
	void				Clear();
	void				UnlinkDeep();
	void				UnrefDeep();
	void				UninitializeComponentsDeep();
	void				ClearComponentsDeep();
	void				ClearDeep();
	void				PruneFromContainer();
	void				Dump();
	String				GetTreeString(int indent=0);
	
	Pool*				GetParent() const;
	Machine&			GetMachine();
	String				GetName() const {return name;}
	bool				HasEntities() const {return !objects.IsEmpty();}
	bool				HasPools() const {return !pools.IsEmpty();}
	
	void				Initialize(Entity& e, String prefab="Custom");
	EntityRef			CreateEmpty();
	EntityRef			GetAddEmpty(String name);
	EntityRef			Clone(const Entity& e);
	
	template<typename PrefabT>
	EntityRef Create() {
		static_assert(RTupleAllComponents<typename PrefabT::Components>::value, "Prefab should have a list of Components");
		
		Entity& e = objects.Add();
		e.SetParent(this);
		e.SetId(GetNextId());
		PrefabT::Make(e);
		Initialize(e, AsTypeName<PrefabT>());
		
		return e.AsRefT();
	}
	
	template<typename... ComponentTs>
	Vector<RTuple<EntityRef,RefT_Entity<ComponentTs>...>> GetComponentsWithEntity() {
		static_assert(sizeof...(ComponentTs) > 0, "Need at least one component");
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all derive from Component");
		
		Vector<RTuple<EntityRef,RefT_Entity<ComponentTs>...>> components;
		
		for (EntityRef object : objects) {
			auto requested_components = object->TryGetComponents<ComponentTs...>();
			
			if (AllValidComponents(requested_components)) {
				RTuple<EntityRef, RefT_Entity<ComponentTs>...> t(object.Get(), requested_components);
				components.Add(t);
			}
		}
		
		return components;
	}
	
	template<typename... ComponentTs>
	Vector<RTuple<RefT_Entity<ComponentTs>...>> GetComponents() {
		static_assert(sizeof...(ComponentTs) > 0, "Need at least one component");
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all derive from Component");
		
		Vector<RTuple<RefT_Entity<ComponentTs>...>> components;
		
		for (EntityRef object : objects) {
			auto requested_components = object->TryGetComponents<ComponentTs...>();
			
			if (AllValidComponents(requested_components)) {
				components.Add(requested_components);
			}
		}
		
		return components;
	}
	
	template<typename T>
	RefT_Pool<T> GetAdd() {
		RefT_Pool<T> c = comps.Find<T>();
		if (c)
			return c;
		return Add<T>();
	}
	
	template<typename T>
	RefT_Pool<T> Find() {
		return comps.Find<T>();
	}
	
	template <class T>
	EntityRef FindEntity(T* component) {
		if (!component)
			return EntityRef();
		for (EntityRef object : objects) {
			RefT_Entity<T> t = object->Find<T>();
			if (t == component)
				return object;
		}
		return EntityRef();
	}
	
	EntityRef FindEntityByName(String name) {
		for (EntityRef object : objects)
			if (object->GetName() == name)
				return object;
		return EntityRef();
	}
	
	template<typename Tuple>
	bool AllValidComponents(const Tuple& components) {
		bool all_valid_components = true;
		components.ForEach([&](auto& component) {
			all_valid_components &= component && !component->IsDestroyed() && component->IsEnabled();
		});
		return all_valid_components;
	}
	
	EntityVec& GetEntities() {return objects;}
	PoolVec& GetPools() {return pools;}
	
	PoolRef AddPool(String name="") {
		Pool& p = pools.Add();
		p.SetParent(PoolParent(0, this));
		p.SetName(name);
		p.SetId(GetNextId());
		return p;
	}
	
	PoolRef GetAddPool(String name) {
		for (PoolRef& pool : pools)
			if (pool->GetName() == name)
				return pool;
		return AddPool(name);
	}
	
	EntityVec::Iterator			begin()			{return objects.begin();}
	EntityVec::Iterator			end()			{return objects.end();}
	PoolVec::Iterator			BeginPool()		{return pools.begin();}
	
	
	
	
	template<typename T>
	void Remove() {
		comps.Remove<T>(GetMachine().Get<ConnectorStore>());
	}
	
	template<typename T>
	RefT_Pool<T> Add() {
		T* comp = GetMachine().Get<ConnectorStore>()->CreateComponent<T>();
		ASSERT(comp);
		RefScopeParent<RefParent1<Pool>>* rp = comp;
		rp->SetParent(this);
		comps.Add(comp);
		InitializeComponent(*comp);
		return RefT_Pool<T>(this, comp);
	}
	
	void Visit(RuntimeVisitor& vis) {
		vis || objects || pools;
	}
private:
	EntityVec				objects;
	PoolVec					pools;
	
	ConnectorMap			comps;
	
	void InitializeComponent(ConnectorBase& comp);
	
};


class PoolHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(PoolHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};



template<typename T>
RefT_Pool<T> Entity::FindConnector() {
	RefT_Pool<T> r;
	Pool* p = &GetPool();
	while (p) {
		r = p->Find<T>();
		if (r) break;
		p = p->GetParent();
	}
	return r;
}

template<typename T>
RefT_Pool<T> Entity::FindCommonConnector(EntityRef sink) {
	RefT_Pool<T> ret;
	int src_depth = GetPoolDepth();
	int sink_depth = sink->GetPoolDepth();
	Pool* src_pool = &GetPool();
	Pool* sink_pool = &sink->GetPool();
	while (src_depth > sink_depth) {src_pool = src_pool->GetParent(); --src_depth;}
	while (sink_depth > src_depth) {sink_pool = sink_pool->GetParent(); --sink_depth;}
	while (src_pool && sink_pool) {
		if (src_pool == sink_pool) {
			ret = src_pool->Find<T>();
			if (ret) break;
		}
		src_pool = src_pool->GetParent();
		sink_pool = sink_pool->GetParent();
	}
	return ret;
}


template<typename T>
RefT_Entity<T> Entity::FindNearestEntityWith() {
	RefT_Entity<T> c = Find<T>();
	if (!c) {
		Pool* p = &GetPool();
		while (p && !c) {
			for (EntityRef& e : *p) {
				c = e->Find<T>();
				if (c) break;
			}
			p = p->GetParent();
		}
	}
	return c;
}

template<typename T>
RefT_Pool<T> Entity::FindNearestPoolWith() {
	RefT_Pool<T> c;
	Pool* p = &GetPool();
	while (p) {
		c = p->Find<T>();
		if (c) break;
		p = p->GetParent();
	}
	return c;
}

NAMESPACE_TOPSIDE_END

#endif
