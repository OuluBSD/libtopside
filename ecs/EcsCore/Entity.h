#ifndef _EcsCore_Entity_h_
#define _EcsCore_Entity_h_


NAMESPACE_OULU_BEGIN


class Machine;
class EntityStore;
class Entity;
class EntityPool;
class Connector;
using SharedEntity = Shared<Entity>;
using SE = Shared<Entity>;



class Entity : public Destroyable, public Enableable, public EnableSharedFromThis<Entity> {
	int64 id = -1;
	String prefab;
	int64 created = 0;
	int64 changed = 0;
	
public:
	using EntityId = uint64_t;
	
	String GetPrefab() const {return prefab;}
	int64 GetId() const {return id;}
	int64 GetCreatedTick() const {return created;}
	int64 GetChangedTick() const {return changed;}
	
	void SetId(int64 i) {id = i;}
	void SetPrefab(String s) {prefab = s;}
	void SetCreated(int64 i) {created = i;}
	void SetChanged(int64 i) {changed = i;}
	
	void OnChange();
	
	template<typename T>
	Shared<T> GetShared() {
		return m_components.GetShared<T>();
	}
	
	template<typename T>
	T* Get() {
		return m_components.Get<T>();
	}
	
	template<typename T>
	Shared<T> FindShared() {
		return m_components.FindShared<T>();
	}
	
	template<typename T>
	T* Find() {
		return m_components.Find<T>();
	}
	
	template<typename T>
	T* FindInterface() {
		T* o = NULL;
		for(Shared<ComponentBase>& comp : m_components.GetValues())
			if ((o = comp->As<T>()))
				break;
		return o;
	}
	
	template<typename T>
	Vector<T*> FindInterfaces() {
		Vector<T*> v;
		T* o;
		for(Shared<ComponentBase>& comp : m_components.GetValues())
			if ((o = comp->As<T>()))
				v.Add(o);
		return v;
	}
	
	template<typename T> void Remove() {OnChange(); Remove0<T>();}
	template<typename T> T* Add() {OnChange(); return Add0<T>();}
	template<typename T> T* GetAdd() {T* o = Find<T>(); if (o) return o; OnChange(); return Add0<T>();}
	
	
	template<typename... ComponentTs>
	RTuple<ComponentTs*...> TryGetComponents() {
		return MakeRTuple(m_components.TryGet<ComponentTs>()...);
	}
	
	Entity(Pick<ComponentMap> components, EntityId id, EntityPool& pool);
	Entity(EntityId id, EntityPool& pool);
	virtual ~Entity();
	
	SharedEntity Clone() const;
	void InitializeComponents();
	void InitializeComponent(ComponentBase& comp);
	void UninitializeComponents();
	void ClearComponents();
	void ConnectAll(ConnectorArea a);
	
	EntityId Id() const {
		return m_id;
	}
	
	void Destroy() override;
	void SetEnabled(bool) override;
	
	Machine&			GetMachine();
	const Machine&		GetMachine() const;
	EntityPool&			GetPool() {return pool;}
	const EntityPool&	GetPool() const {return pool;}
	
	#define IFACE_(x, post)\
		x##post* Find##x##post() {\
			for(Shared<ComponentBase>& base : m_components.GetValues()) {\
				x##post* o = base->As##x##post();\
				if (o) return o;\
			}\
			return NULL;\
		}
	#define IFACE(x) IFACE_(x, Source) IFACE_(x, Sink)
	IFACE_LIST
	#undef IFACE
	#undef IFACE_
	
	
	ComponentMap& GetComponents() {return m_components;}
	const ComponentMap& GetComponents() const {return m_components;}
	Connector* GetConnector() const {return conn;}
	void RefreshConnectorPtr();
	void SetUpdateInterfaces();
	
protected:
	friend class EntityPool;
	friend class ConnectorSystem;
	
	void UpdateInterfaces();
	
private:
	ComponentMap m_components;
	EntityId m_id;
	EntityPool& pool;
	Connector* conn = 0;
	
	
	template<typename T>
	void Remove0() {
		m_components.Remove<T>();
		SetUpdateInterfaces();
	}
	
	template<typename T>
	T* Add0() {
		T* comp = m_components.Add<T>(GetMachine().Get<ComponentStore>()->CreateComponent<T>());
		InitializeComponent(*comp);
		SetUpdateInterfaces();
		return comp;
	}
	
};

template<> inline void Entity::Remove<Connector>() {ASSERT(conn); conn = 0; Remove0<Connector>();}
template<> inline Connector* Entity::Add<Connector>() {ASSERT(!conn); conn = Add0<Connector>(); return conn;}



template<typename... ComponentTs>
struct EntityPrefab {
	static_assert(AllComponents<ComponentTs...>::value, "All components should derive from Component");
	
	using Components = RTuple<ComponentTs...>;
	
	static ComponentMap Make(ComponentStore& store) {
		return store.CreateComponentMap<ComponentTs...>();
	}
};


NAMESPACE_OULU_END


#endif
