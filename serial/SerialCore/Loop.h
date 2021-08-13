#ifndef _SerialCore_Loop_h_
#define _SerialCore_Loop_h_

NAMESPACE_SERIAL_BEGIN


class Loop :
	public MetaExchangePoint,
	RTTIBase
{
	Machine*			machine = 0;
	BitField<dword>		freeze_bits;
	String				name;
	LoopId				id;
	
protected:
	friend class EntityStore;
	
	void SetId(LoopId i) {id = i;}
	
public:
	typedef Loop CLASSNAME;
	
	static LoopId GetNextId();
	
	RTTI_DECL_R1(Loop, MetaExchangePoint)
	Loop();
	~Loop();
	
	typedef enum {
		BIT_OVERLAP,
		BIT_TRANSFORM,
	} Bit;
	
	
	LoopId GetId() const {return id;}
	
	void SetName(String s)			{name = s;}
	void FreezeTransform()			{freeze_bits.Set(BIT_TRANSFORM, true);}
	void FreezeOverlap()			{freeze_bits.Set(BIT_OVERLAP, true);}
	bool IsFrozenTransform() const	{return freeze_bits.Is(BIT_TRANSFORM);}
	bool IsFrozenOverlap() const	{return freeze_bits.Is(BIT_OVERLAP);}
	
	void				ReverseEntities();
	void				Clear();
	void				UnlinkDeep();
	void				UnlinkExchangePoints();
	void				ClearInterfacesDeep();
	void				UnrefDeep();
	void				UninitializeComponentsDeep();
	void				ClearComponentsDeep();
	void				ClearDeep();
	void				PruneFromContainer();
	void				Dump();
	String				GetTreeString(int indent=0);
	
	Loop*				GetParent() const;
	Machine&			GetMachine();
	String				GetName() const {return name;}
	bool				HasEntities() const {return !objects.IsEmpty();}
	bool				HasLoops() const {return !pools.IsEmpty();}
	
	void				Initialize(Entity& e, String prefab="Custom");
	EntityRef			CreateEmpty();
	EntityRef			GetAddEmpty(String name);
	EntityRef			Clone(const Entity& e);
	
	bool Link(ComponentBaseRef src_comp, ComponentBaseRef dst_comp, ValDevCls iface);
	
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
	
	/*template<typename T>
	RefT_Loop<T> GetAdd() {
		RefT_Loop<T> c = comps.Find<T>();
		if (c)
			return c;
		return Add<T>();
	}
	
	template<typename T>
	RefT_Loop<T> Find() {
		return comps.Find<T>();
	}*/
	
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
	LoopVec& GetLoops() {return pools;}
	
	LoopRef AddLoop(String name="") {
		Loop& p = pools.Add();
		p.SetParent(LoopParent(0, this));
		p.SetName(name);
		p.SetId(GetNextId());
		return p;
	}
	
	LoopRef GetAddLoop(String name) {
		for (LoopRef& pool : pools)
			if (pool->GetName() == name)
				return pool;
		return AddLoop(name);
	}
	
	EntityVec::Iterator			begin()			{return objects.begin();}
	EntityVec::Iterator			end()			{return objects.end();}
	LoopVec::Iterator			BeginLoop()		{return pools.begin();}
	
	
	
	
	/*template<typename T>
	void Remove() {
		comps.Remove<T>(GetMachine().Get<ConnectorStore>());
	}
	
	template<typename T>
	RefT_Loop<T> Add() {
		T* comp = GetMachine().Get<ConnectorStore>()->CreateComponent<T>();
		ASSERT(comp);
		RefScopeParent<RefParent1<Loop>>* rp = comp;
		rp->SetParent(this);
		comps.Add(comp);
		InitializeComponent(*comp);
		return RefT_Loop<T>(this, comp);
	}*/
	
	void Visit(RuntimeVisitor& vis) {
		vis || objects || pools;
	}
private:
	EntityVec				objects;
	LoopVec					pools;
	
	/*ConnectorMap			comps;
	
	void InitializeComponent(ConnectorBase& comp);*/
	
};


class LoopHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(LoopHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};



template<typename T>
RefT_Entity<T> Entity::FindNearestEntityWith() {
	RefT_Entity<T> c = Find<T>();
	if (!c) {
		Loop* p = &GetLoop();
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

NAMESPACE_SERIAL_END

#endif
