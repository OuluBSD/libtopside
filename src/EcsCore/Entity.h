#ifndef _EcsCore_Entity_h_
#define _EcsCore_Entity_h_


NAMESPACE_ECS_BEGIN



class Entity :
	public RefScopeEnabler<Entity,Pool>,
	public Destroyable,
	public Enableable
{
	EntityId id = -1;
	int64 created = 0;
	int64 changed = 0;

	String prefab;
	String name;
	
	ComponentMap comps;
	EntityId m_id;
	
protected:
	friend class Pool;
	
	void SetId(EntityId i) {id = i;}
	void SetCreated(int64 i) {created = i;}
	void SetChanged(int64 i) {changed = i;}
	
	void CopyHeader(const Entity& e) {
		prefab = e.prefab;
		name = e.name;
	}
	
public:
	typedef Entity CLASSNAME;
	RTTI_DECL_R2(Entity, Destroyable, Enableable)
	Entity();
	virtual ~Entity();
	
	static EntityId GetNextId();
	
	void Etherize(Ether& e);
	
	void SetPrefab(String s) {prefab = s;}
	String GetPrefab() const {return prefab;}
	String GetName() const {return name;}
	EntityId GetId() const {return id;}
	int64 GetCreatedTick() const {return created;}
	int64 GetChangedTick() const {return changed;}
	
	String ToString() const {return IntStr64(id) + " " + prefab + (name.GetCount() ? ": " + name : String());}
	String GetTreeString(int indent=0);
	void SetName(String s) {name = s;}
	void OnChange();
	void UnrefDeep();
	ComponentBaseRef GetTypeCls(TypeCls comp_type);
	ComponentBaseRef GetAddTypeCls(TypeCls cls);
	ComponentBaseRef FindTypeCls(TypeCls comp_type);
	
	template<typename T>
	RefT_Entity<T> Get() {
		return comps.Get<T>();
	}
	
	template<typename T>
	RefT_Entity<T> Find() {
		return comps.Find<T>();
	}
	
	template<typename T>
	RefT_Entity<T> FindNearestEntityWith();
	
	template<typename T>
	RefT_Pool<T> FindNearestPoolWith();
	
	template<typename T>
	RefT_Entity<T> FindCast() {
		RefT_Entity<T> o;
		for(Ref<ComponentBase>& comp : comps.GetValues()) {
			T* p = CastPtr<T>(&*comp);
			if (p) {
				o = RefT_Entity<T>(p->GetParent(), p);
				break;
			}
		}
		return o;
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
	LinkedList<RefT_Entity<T>> FindInterfaces() {
		LinkedList<RefT_Entity<T>> v;
		RefT_Entity<T> o;
		for(Ref<ComponentBase>& comp : comps.GetValues())
			if ((o = comp->As<T>()))
				v.Add(o);
		return v;
	}
	
	template<typename T> RefT_Pool<T> FindConnector();
	template<typename T> RefT_Pool<T> FindCommonConnector(EntityRef sink);
	int GetPoolDepth() const;
	bool HasPoolParent(PoolRef pool) const;
	
	template<typename T> void Remove() {
		OnChange();
		Remove0<T>();
	}
	template<typename T> RefT_Entity<T> Add() {
		OnChange();
		auto comp = Add0<T>(true);
		return comp;
	}
	template<typename T> RefT_Entity<T> GetAdd() {
		RefT_Entity<T> o = Find<T>();
		if (o)
			return o;
		OnChange();
		auto comp = Add0<T>(true);
		return comp;
	}
	
	
	
	template<typename... ComponentTs>
	RTuple<RefT_Entity<ComponentTs>...> TryGetComponents() {
		return MakeRTuple(comps.Find<ComponentTs>()...);
	}
	
	
	EntityRef			Clone() const;
	void				InitializeComponents();
	void				InitializeComponent(ComponentBase& comp);
	void				InitializeComponentRef(ComponentBaseRef comp) {return InitializeComponent(*comp);}
	void				UninitializeComponents();
	void				ClearComponents();
	
	EntityId			Id() const {return m_id;}
	
	void				Destroy() override;
	
	Engine&				GetEngine();
	const Engine&		GetEngine() const;
	Pool&				GetPool() const;
	
	ComponentMap&		GetComponents() {return comps;}
	const ComponentMap&	GetComponents() const {return comps;}
	
	template<typename... ComponentTs>
	RTuple<RefT_Entity<ComponentTs>...> CreateComponents() {
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all be a component");
		
		auto tuple =  RTuple<RefT_Entity<ComponentTs>...> {{
				Add0<ComponentTs>(false)
			}
			...
		};
		tuple.ForEach([this](auto& comp) {InitializeComponent(comp.GetMutable());});
		return tuple;
	}
	
	ComponentBaseRef CreateEon(String id);
	
	
	void Visit(RuntimeVisitor& vis) {vis || comps;}
	
private:
	
	template<typename T> void Remove0();
	template<typename T> RefT_Entity<T> Add0(bool initialize);
	
	
	ComponentBaseRef AddPtr(ComponentBase* comp);
	
	
};






template<typename... ComponentTs>
struct EntityPrefab {
	static_assert(AllComponents<ComponentTs...>::value, "All components should derive from Component");
	
	using Components = RTuple<RefT_Entity<ComponentTs>...>;
	
	static String GetComponentNames() {
		return RTuple<ComponentTs...>::GetTypeNames();
	}
	
    static String GetTypeName() {
        static auto s = "EntityPrefab<" + GetComponentNames() + ">" ; return s;
    }
    
	static Components Make(Entity& e) {
		return e.CreateComponents<ComponentTs...>();
	}
};


class EntityHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
	
public:
	RTTI_DECL1(EntityHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};


NAMESPACE_ECS_END


#endif
