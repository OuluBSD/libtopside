#ifndef _EcsCore_ComponentStore_h_
#define _EcsCore_ComponentStore_h_

NAMESPACE_ECS_BEGIN


template<class T> using EcsTypeMap				= LinkedMap<EcsTypeCls, T>;




template<typename T, typename ProducerT, typename RefurbisherT>
class EcsFactory
{
public:
    using Type = T;
    using Producer = ProducerT;
    using Refurbisher = RefurbisherT;

    void RegisterProducer(const EcsTypeCls& typeId, Producer producer, Refurbisher refurbisher)
    {
        auto p = producers.find(typeId);
        AssertFalse(p != producers.end(), "multiple registrations for the same type is not allowed");
        producers.insert(p, { typeId, pick<Producer>(producer) });
        
        auto r = refurbishers.find(typeId);
        AssertFalse(r != refurbishers.end(), "multiple registrations for the same type is not allowed");
        refurbishers.insert(r, { typeId, pick<Refurbisher>(refurbisher) });
    }

protected:
    EcsTypeMap<ProducerT> producers;
    EcsTypeMap<RefurbisherT> refurbishers;
    
};



template <class Main, class Base>
class ComponentStoreT :
	public System<ComponentStoreT<Main,Base>>,
	public EcsFactory<Base*, std::function<Base*()>, std::function<void(Base*)> >
{
	
	
public:
	using ComponentStore = ComponentStoreT<Main,Base>;
	RTTI_DECL1(ComponentStoreT, System<ComponentStore>)
	SYS_CTOR(ComponentStoreT);
	SYS_DEF_VISIT
	
	using Parent = Machine;
	using Factory = EcsFactory<Base*, std::function<Base*()>, std::function<void(Base*)> >;
	template<typename T> using IsComponent = std::is_base_of<Base, T>;
	template<typename T> using IsConnector = std::is_base_of<Base, T>;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	ComponentBase* CreateComponentTypeCls(EcsTypeCls key);
	
	template<typename T>
	T* CreateComponent(ValDevCls vd) {
		static_assert(IsComponent<T>::value, "T should be a component");
		
		EcsTypeCls key  = AsEcsTypeCls<T>(vd);
		auto it = Factory::producers.Find(key);
		if (!it) {
			std::function<Base*()> p([] { return GetPool<T>().New();});
			std::function<void(Base*)> r([] (Base* b){ GetPool<T>().Return(CastPtr<T>(b));});
			Factory::producers.Add(key) = p;
			Factory::refurbishers.Add(key) = r;
		}
		
		return CastPtr<T>(CreateComponent(key));
	}
	
	void Clone(Main& dst, const Main& src) {
		const ComponentMap& src_comps = src.GetComponents();
		ComponentMap& dst_comps = dst.GetComponents();
		
		ComponentMap::Iterator iter = const_cast<ComponentMap&>(src_comps).begin();
		for (; iter; ++iter) {
			EcsTypeCls comp_type = iter.key();
			Base* new_component = CreateComponent(comp_type);
			dst.InitializeComponent(*new_component);
			iter.value().CopyTo(new_component);
			dst_comps.ComponentMapBase::Add(comp_type, new_component);
		}
	}
	
	void ReturnComponent(Base* c) {
		ASSERT(c);
		EcsTypeCls type = c->GetType();
		
		auto iter = Factory::refurbishers.Find(type);
		if (iter)
			iter.Get()(c);
	}

	
private:
	
	Base* CreateComponent(EcsTypeCls typeId) {
		auto iter = Factory::producers.Find(typeId);
		ASSERT_(iter, "Invalid to create non-existant component");
		
		Base* obj = iter.value()();
		obj->SetType(typeId);
		return obj;
	}
	
};

using ComponentStore = ComponentStoreT<Entity, ComponentBase>;

//using ConnectorStore = ComponentStoreT<Pool, ConnectorBase>;


NAMESPACE_ECS_END

#endif
