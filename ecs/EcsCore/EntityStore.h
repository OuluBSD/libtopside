#ifndef _EcsCore_EntityStore_h_
#define _EcsCore_EntityStore_h_


NAMESPACE_OULU_BEGIN

class EntityPool;


typedef RefLinkedList<Entity> EntityVec;
typedef RefLinkedList<EntityPool> EntityPoolVec;

class EntityPool : public LockedScopeEnabler<EntityPool> {
	Machine* machine = 0;
	EntityPool* parent = 0;
	BitField<dword> freeze_bits;
	String name;
	
	EntityRef CreateFromComponentMap(ComponentMap components);
	
public:
	typedef EntityPool CLASSNAME;
	EntityPool();
	
	typedef enum {
		BIT_CONNECTOR,
		BIT_CONNECTOR3D,
		BIT_TRANSFORM,
	} Bit;
	
	
	static EntityId GetNextId();
	
	void SetMachine(Machine& m)		{machine = &m;}
	void SetName(String s)			{name = s;}
	void FreezeConnector()			{freeze_bits.Set(BIT_CONNECTOR, true);}
	void FreezeOverlap()			{freeze_bits.Set(BIT_CONNECTOR3D, true);}
	bool IsFrozenConnector() const	{return freeze_bits.Is(BIT_CONNECTOR);}
	bool IsFrozenOverlap() const	{return freeze_bits.Is(BIT_CONNECTOR3D);}
	
	void				ReverseEntities();
	void				Clear();
	void				UnlinkDeep();
	void				UninitializeComponentsDeep();
	void				ClearComponentsDeep();
	void				ClearDeep();
	void				PruneFromContainer();
	
	EntityPool*			GetParent() const {return parent;}
	Machine&			GetMachine() {return *machine;}
	bool				HasEntities() const;
	bool				HasEntityPools() const;
	//int					GetPoolCount() const {return pools.GetCount();}
	//EntityPoolRef			GetPool(int i) {return pools[i];}
	//const EntityPoolRef	GetPool(int i) const {return pools[i];}
	//int					GetCount() const {return objects.GetCount();}
	//EntityRef		Get(int i) {return objects[i];}
	//const EntityRef	Get(int i) const {return objects[i];}
	String				GetName() const {return name;}
	
	void				Initialize(Entity& e, String prefab="Custom");
	EntityRef		CreateEmpty();
	EntityRef		Clone(const Entity& e);
	
	template<typename PrefabT>
	EntityRef Create() {
		static_assert(RTupleAllComponents<typename PrefabT::Components>::value, "Prefab should have a list of Components");
		
		EntityRef e = CreateFromComponentMap(PrefabT::Make(*machine->Get<ComponentStore>()));
		if (e)
			Initialize(*e, TypeId(typeid(PrefabT)).CleanDemangledName());
		
		return e;
	}
	
	template<typename PrefabT>
	EntityRef CreateConnectedArea(ConnectorArea a) {
		static_assert(RTupleAllComponents<typename PrefabT::Components>::value, "Prefab should have a list of Components");
		
		EntityRef e = CreateFromComponentMap(PrefabT::Make(*machine->Get<ComponentStore>()));
		if (e)
			Initialize(*e, TypeId(typeid(PrefabT)).CleanDemangledName());
		
		Connector* c = e->Find<Connector>();
		ASSERT_(c, "CreateConnected expected entity prefab, which includes Connector component");
		if (c)
			c->ConnectAll(a);
		
		return e;
	}
	
	template<typename PrefabT> EntityRef CreateConnectedCurrent()		{return CreateConnectedArea<PrefabT>(CONNAREA_POOL_CURRENT);}
	template<typename PrefabT> EntityRef CreateConnectedInternal()		{return CreateConnectedArea<PrefabT>(CONNAREA_INTERNAL);}
	template<typename PrefabT> EntityRef CreateConnectedChildrenOnly()	{return CreateConnectedArea<PrefabT>(CONNAREA_POOL_CHILDREN_ONLY);}
	template<typename PrefabT> EntityRef CreateConnectedParentsOnly()	{return CreateConnectedArea<PrefabT>(CONNAREA_POOL_PARENTS_ONLY);}
	
	template<typename... ComponentTs>
	Vector < RTuple < Entity*, ComponentTs*... >> GetComponentsWithEntity() {
		static_assert(sizeof...(ComponentTs) > 0, "Need at least one component");
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all derive from Component");
		
		Vector < RTuple < Entity*, ComponentTs*... >> components;
		
		for (auto& object : objects) {
			auto requested_components = object->TryGetComponents<ComponentTs...>();
			
			if (AllValidComponents(requested_components)) {
				RTuple<Entity*, ComponentTs*...> t(object.Get(), requested_components);
				components.Add(t);
				//components.Add(TupleCat(Tuple(object.Get()), Pick(requested_components)));
			}
		}
		
		return components;
	}
	
	template<typename... ComponentTs>
	Vector < RTuple < ComponentTs*... >> GetComponents() {
		static_assert(sizeof...(ComponentTs) > 0, "Need at least one component");
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all derive from Component");
		
		Vector < RTuple < ComponentTs*... >> components;
		
		for (auto& object : objects) {
			auto requested_components = object->TryGetComponents<ComponentTs...>();
			
			if (AllValidComponents(requested_components)) {
				components.Add(requested_components);
			}
		}
		
		return components;
	}
	
	template <class T>
	Entity* FindEntity(T* component) {
		if (!component)
			return 0;
		for (auto& object : objects) {
			T* t = object->Find<T>();
			if (t == component)
				return object.Get();
		}
		return 0;
	}
	
	EntityRef FindEntityByName(String name) {
		for (auto& object : objects)
			if (object->GetName() == name)
				return object;
		return EntityRef();
	}
	
	/*void ReleaseEntity(Entity& ent) {
		for (int i = 0; i < objects.GetCount(); i++) {
			if (objects[i].Get() == &ent)
				objects.Remove(i--);
		}
	}*/
	
	template<typename Tuple>
	bool AllValidComponents(const Tuple& components) {
		bool all_valid_components = true;
		components.ForEach([&](auto* component) {
			all_valid_components &= component != nullptr && !component->IsDestroyed() && component->IsEnabled();
		});
		return all_valid_components;
	}
	
	RefLinkedList<Entity>& GetEntities() {return objects;}
	RefLinkedList<EntityPool>& GetPools() {return pools;}
	
	EntityPoolRef AddPool(String name="") {
		EntityPoolRef p = pools.Add();
		p->SetMachine(*machine);
		p->parent = this;
		p->SetName(name);
		return p;
	}
	
	EntityPoolRef GetAddPool(String name) {
		for (EntityPoolRef& pool : pools)
			if (pool->GetName() == name)
				return pool;
		return AddPool(name);
	}
	
	RefLinkedList<Entity>::Iterator			begin();
	RefLinkedList<Entity>::Iterator			end();
	
	RefLinkedList<Entity>::Iterator			Begin();
	RefLinkedList<EntityPool>::Iterator		BeginPool();
	
private:
	
	RefLinkedList<Entity>			objects;
	RefLinkedList<EntityPool>		pools;
	
	void AddEntity(EntityRef obj);
	
};


class EntityVisitor {
	struct Item : Moveable<Item> {
		int pool_pos;
		EntityPoolVec::Iterator pool;
		EntityVec::Iterator ent;
		bool finished = false;
	};
	
	EntityPoolVec& base;
	BitField<dword> freeze_checks;
	Vector<Item> stack;
	EntityRef cur;
	int mode;
	
protected:
	bool FindNextDepthFirst();
	bool NewPoolNextDepthFirst();
	void PoolIncPopWhileTop();
	void PoolPushSub();
	bool PoolFindNextDepthFirst();
public:
	enum {
		POOL_CURRENT_AND_CHILDREN,
		POOL_CURRENT_ONLY,
		POOL_CHILDREN_ONLY
	};
	
	EntityVisitor(EntityPoolVec& pool, int mode=POOL_CURRENT_AND_CHILDREN);
	EntityVisitor(Machine& m, int mode=POOL_CURRENT_AND_CHILDREN);
	EntityVisitor(Entity& e, int mode=POOL_CURRENT_AND_CHILDREN);
	
	void Reset();
	void Skip(EntityPool::Bit entpool_bit);
	EntityRef GetCurrent() const {return cur;}
	
	Entity* operator->();
	EntityRef operator*();
	operator bool() const;
	void operator++(int);
	
};


class EntityDummyVisitor {
	Entity& e;
	bool once = true;
public:
	EntityDummyVisitor(Entity& e) : e(e) {}
	void Reset() {once = true;}
	Entity* GetCurrent() const {return &e;}
	Entity* operator->() {return once ? &e : 0;}
	Entity* operator*() {return once ? &e : 0;}
	operator bool() const {return once;}
	void operator++(int) {once = false;}
};

class EntityParentVisitor {
	EntityPool& base;
	BitField<dword> freeze_checks;
	EntityPool* cur_pool;
	EntityVec::Iterator cur;
	
	bool FindNextChildFirst();
	
public:
	EntityParentVisitor(Entity& e);
	EntityParentVisitor(EntityPool& pool);
	
	void Reset();
	void Skip(EntityPool::Bit entpool_bit);
	EntityRef GetCurrent() const {return *cur;}
	
	Entity* operator->();
	EntityRef operator*();
	operator bool() const;
	void operator++(int);
	
};

class EntityChildrenVisitor : public EntityVisitor {
	
public:
	EntityChildrenVisitor(EntityPoolVec& pool)	: EntityVisitor(pool, POOL_CHILDREN_ONLY) {}
	EntityChildrenVisitor(Machine& m)			: EntityVisitor(m, POOL_CHILDREN_ONLY) {}
	EntityChildrenVisitor(Entity& e)			: EntityVisitor(e, POOL_CHILDREN_ONLY) {}
	
};

class EntityCurrentVisitor : public EntityVisitor {
	
public:
	EntityCurrentVisitor(EntityPoolVec& pool)	: EntityVisitor(pool, POOL_CURRENT_ONLY) {}
	EntityCurrentVisitor(Machine& m)			: EntityVisitor(m, POOL_CURRENT_ONLY) {}
	EntityCurrentVisitor(Entity& e)				: EntityVisitor(e, POOL_CURRENT_ONLY) {}
	
};


template<typename... ComponentTs>
class EntityComponentVisitor : public EntityVisitor {
	RTuple<ComponentTs*...> cur_comps;
	
	bool FindComps() {
		Entity& e = *GetCurrent();
		cur_comps = e.TryGetComponents<ComponentTs...>();
		bool has_value = true;
		cur_comps.ForEach([&has_value](void* ptr){if (!ptr) has_value = false;});
		return has_value;
	}
	bool FindNextDepthFirstWithComps() {
		while (FindNextDepthFirst()) {
			if (FindComps())
				return true;
		}
		return false;
	}
	
	void Init() {
		if (!FindComps())
			FindNextDepthFirstWithComps();
	}
public:
	EntityComponentVisitor(EntityPoolVec& pool) : EntityVisitor(pool) {Init();}
	EntityComponentVisitor(Machine& m) : EntityVisitor(m) {Init();}
	
	
	template<typename ComponentT> ComponentT* Get() {return cur_comps.template Find<ComponentT>();}
	
	void operator++(int) {FindNextDepthFirstWithComps();}
	
};


class EntityStore : public System<EntityStore> {
	EntityPoolVec		root;
	
public:
	using System::System;
	
	EntityStore(Machine& m) : System<EntityStore>(m) {
		root.Add()->SetMachine(machine);
	}
	
	EntityPoolRef GetRoot()	{return *root.begin();}
	EntityPoolVec& GetRootVec()	{return root;}
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Uninitialize() override;
	
	
};

typedef Ref<EntityStore> EntityStoreRef;


NAMESPACE_OULU_END


#endif
