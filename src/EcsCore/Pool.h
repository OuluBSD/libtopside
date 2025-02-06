#ifndef _EcsCore_Pool_h_
#define _EcsCore_Pool_h_


NAMESPACE_ECS_BEGIN

class Pool;



class Pool :
	public RefScopeEnabler<Pool, EntityStore, PoolParent>,
	RTTIBase
{
	Engine*				machine = 0;
	BitField<dword>		freeze_bits;
	String				name;
	PoolId				id;
	EntityVec			objects;
	PoolVec				pools;
	
protected:
	friend class EntityStore;
	
	void SetId(PoolId i) {id = i;}
	
public:
	typedef Pool CLASSNAME;
	
	using RScope		= RefScopeEnabler<Pool, EntityStore, PoolParent>;
	
	static PoolId GetNextId();
	
	RTTI_DECL_R1(Pool, RScope)
	Pool();
	~Pool();
	
	typedef enum {
		BIT_OVERLAP,
		BIT_TRANSFORM,
	} Bit;
	
	void Etherize(Ether& e);
	
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
	Engine&				GetEngine();
	String				GetName() const {return name;}
	bool				HasEntities() const {return !objects.IsEmpty();}
	bool				HasPools() const {return !pools.IsEmpty();}
	
	void				Initialize(Entity& e, String prefab="Custom");
	EntityRef			CreateEmpty();
	EntityRef			GetAddEmpty(String name);
	EntityRef			Clone(const Entity& e);
	EntityRef			RealizeEntityPath(const Vector<String>& path);
	
	template<typename PrefabT>
	EntityRef Create() {
		static_assert(RTupleAllComponents<typename PrefabT::Components>::value, "Prefab should have a list of Components");
		
		Entity& e = objects.Add();
		e.SetParent(this);
		e.SetId(GetNextId());
		PrefabT::Make(e);
		Initialize(e, PrefabT::GetComponentNames());
		
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
				RTuple<EntityRef, RefT_Entity<ComponentTs>...> t(object, requested_components);
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
	
	
	void RemoveEntity(Entity* e);
	
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
	
	EntityRef FindEntityByName(String name);
	
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
	
	PoolRef FindPool(String name);
	PoolRef AddPool(String name="");
	PoolRef GetAddPool(String name);
	void RemovePool(String name);
	EntityVec::Iterator			begin()			{return objects.begin();}
	EntityVec::Iterator			end()			{return objects.end();}
	PoolVec::Iterator			BeginPool()		{return pools.begin();}
	
	ComponentBaseRef RealizeComponentPath(const Vector<String>& path);
	
	void Visit(RuntimeVisitor& vis) {
		vis || objects || pools;
	}
	
};


class PoolHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(PoolHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};



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


template <>
inline void ComponentBase::EtherizeRef(Ether& e, EntityRef& ref) {
	thread_local static Vector<String> path;
	bool has_ref = !ref.IsEmpty();
	e % has_ref;
	if (has_ref) {
		if (e.IsLoading()) {
			e % path;
			ASSERT_(path.GetCount() >= 1, "Entity path is required");
			if (path.GetCount() < 1) return;
			Pool& root = ref->GetRoot();
			ref = root.RealizeEntityPath(path);
			ASSERT_(ref, "Couldn't get etherized entity from path");
		}
		else {
			ref->GetEntityPath(path);
			e % path;
		}
	}
	else if (e.IsStoring())
		ref.Clear();
}

template <class T>
void ComponentBase::EtherizeRef(Ether& e, Ref<T>& ref) {
	thread_local static Vector<String> path;
	EntityRef ent = GetEntity();
	bool has_ref = !ref.IsEmpty();
	e % has_ref;
	if (has_ref) {
		if (e.IsLoading()) {
			e % path;
			ASSERT_(path.GetCount() >= 2, "Entity and Component paths is required");
			if (path.GetCount() < 2) return;
			Pool& root = ent->GetRoot();
			ComponentBaseRef comp = root.RealizeComponentPath(path);
			ASSERT_(comp, "Component path couldn't be realized");
			ref = comp->AsRef<T>();
			ASSERT_(ref, "Couldn't get etherized component from path");
		}
		else {
			ref->GetComponentPath(path);
			e % path;
		}
	}
	else {
		if (e.IsStoring())
			ref.Clear();
	}
}

template <class T>
void ComponentBase::EtherizeRefContainer(Ether& e, T& cont) {
	int d = cont.GetCount();
	e % d;
	cont.SetCount(d);
	for (auto& ref : cont) {
		EtherizeRef(e, ref);
	}
}


NAMESPACE_ECS_END

#endif
