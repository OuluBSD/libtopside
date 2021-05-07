#ifndef _EcsCore_Entity_h_
#define _EcsCore_Entity_h_


NAMESPACE_OULU_BEGIN



class Entity :
	public Destroyable,
	public Enableable,
	public RefScopeEnabler<Entity,Pool>
{
	EntityId id = -1;
	int64 created = 0;
	int64 changed = 0;

	String prefab;
	String name;
	
protected:
	friend class Pool;
	
	void Init(Pool* p, EntityId i) {pool = p; id = i;}
	//void SetId(EntityId i) {id = i;}
	void SetPrefab(String s) {prefab = s;}
	void SetCreated(int64 i) {created = i;}
	void SetChanged(int64 i) {changed = i;}
	
	void CopyHeader(const Entity& e) {
		prefab = e.prefab;
		name = e.name;
	}
	
public:
	Entity();
	virtual ~Entity();
	
	String GetPrefab() const {return prefab;}
	String GetName() const {return name;}
	EntityId GetId() const {return id;}
	int64 GetCreatedTick() const {return created;}
	int64 GetChangedTick() const {return changed;}
	
	String ToString() const {return IntStr64(id) + " " + prefab + (name.GetCount() ? ": " + name : "");}
	
	void SetName(String s) {name = s;}
	
	void OnChange();
	
	template<typename T>
	RefT_Entity<T> Get() {
		return comps.Get<T>();
	}
	
	template<typename T>
	RefT_Entity<T> Find() {
		return comps.Find<T>();
	}
	
	template<typename T>
	RefT_Entity<T> FindInterface() {
		RefT_Entity<T> o;
		for(Ref<ComponentBase>& comp : comps.GetValues())
			if ((o = comp->As<T>()))
				break;
		return o;
	}
	
	template<typename T>
	Vector<RefT_Entity<T>> FindInterfaces() {
		Vector<RefT_Entity<T>> v;
		RefT_Entity<T> o;
		for(Ref<ComponentBase>& comp : comps.GetValues())
			if ((o = comp->As<T>()))
				v.Add(o);
		return v;
	}
	
	template<typename T> void Remove() {
		OnChange();
		Remove0<T>();
	}
	template<typename T> RefT_Entity<T> Add() {
		OnChange();
		return Add0<T>();
	}
	template<typename T> RefT_Entity<T> GetAdd() {
		T* o = Find<T>();
		if (o)
			return o;
		OnChange();
		return Add0<T>();
	}
	
	
	
	template<typename... ComponentTs>
	RTuple<RefT_Entity<ComponentTs>...> TryGetComponents() {
		return MakeRTuple(comps.Find<ComponentTs>()...);
	}
	
	
	EntityRef Clone() const;
	void InitializeComponents();
	void InitializeComponent(ComponentBase& comp);
	void UninitializeComponents();
	void ClearComponents();
	
	EntityId Id() const {
		return m_id;
	}
	
	void Destroy() override;
	void SetEnabled(bool) override;
	
	Machine&			GetMachine();
	const Machine&		GetMachine() const;
	Pool&			GetPool() {return *pool;}
	const Pool&	GetPool() const {return *pool;}
	
	#define IFACE_(x, post, map)\
		RefT_Entity<x##post> Find##x##post() {\
			TypeRefMap<Exchange##post##Provider>::Iterator iter = map.begin(); \
			TypeId key(typeid(x##post)); \
			for(; iter; ++iter)\
				if (iter.key() == key) \
					return iter.value().AsRef<x##post>(); \
			return RefT_Entity<x##post>();\
		}
	#define IFACE(x) IFACE_(x, Source, srcs) IFACE_(x, Sink, sinks)
	IFACE_LIST
	#undef IFACE
	#undef IFACE_
	
	
	ComponentMap& GetComponents() {return comps;}
	const ComponentMap& GetComponents() const {return comps;}
	
	template<typename... ComponentTs>
	RTuple<RefT_Entity<ComponentTs>...> CreateComponents() {
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all be a component");
		
		return RTuple<RefT_Entity<ComponentTs>...> { { Add0<ComponentTs>() }... };
	}
	
	void CloneComponents(const Entity& e);
	
	
private:
	TypeRefMap<ExchangeSinkProvider> sinks;
	TypeRefMap<ExchangeSourceProvider> srcs;
	ComponentMap comps;
	EntityId m_id;
	Pool* pool = 0;
	
	
	template<typename T>
	void Remove0() {
		comps.Remove<T>(GetMachine().Get<ComponentStore>());
	}
	
	template<typename T>
	RefT_Entity<T> Add0() {
		T* comp = GetMachine().Get<ComponentStore>()->CreateComponent<T>();
		ASSERT(comp);
		comp->SetParent(this);
		comps.Add(comp);
		InitializeComponent(*comp);
		ASSERT(comp->GetEntityPtr());
		return RefT_Entity<T>(this, comp);
	}
	
};




template<typename... ComponentTs>
struct EntityPrefab {
	static_assert(AllComponents<ComponentTs...>::value, "All components should derive from Component");
	
	using Components = RTuple<RefT_Entity<ComponentTs>...>;
	
	static Components Make(Entity& e) {
		return e.CreateComponents<ComponentTs...>();
	}
};


NAMESPACE_OULU_END


#endif
