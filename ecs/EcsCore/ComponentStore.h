#ifndef _EcsCore_ComponentStore_h_
#define _EcsCore_ComponentStore_h_

NAMESPACE_ECS_BEGIN


template<class T> using EcsTypeMap = LinkedMap<EcsTypeCls, T>;




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



class ComponentStore :
	public System<ComponentStore>,
	public EcsFactory<ComponentBase*, std::function<ComponentBase*()>, std::function<void(ComponentBase*)> >
{
	
	
public:
	using Main = Entity;
	using Base = ComponentBase;
	RTTI_DECL1(ComponentStore, System<ComponentStore>)
	SYS_CTOR(ComponentStore);
	SYS_DEF_VISIT
	
	using Parent = Machine;
	using Factory = EcsFactory<Base*, std::function<Base*()>, std::function<void(Base*)> >;
	template<typename T> using IsComponent = std::is_base_of<Base, T>;
	template<typename T> using IsConnector = std::is_base_of<Base, T>;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	ComponentBase* CreateComponentTypeCls(TypeCompCls cls);
	
	template<typename T>
	T* CreateComponent(CompCls cls) {
		static_assert(IsComponent<T>::value, "T should be a component");
		
		TypeCompCls t;
		t.side  = AsEcsTypeCls<T>(cls.side);
		auto it = EcsFactory::producers.Find(t.side);
		if (!it) {
			std::function<Base*()> p([] { return GetPool<T>().New();});
			std::function<void(Base*)> r([] (Base* b){ GetPool<T>().Return(CastPtr<T>(b));});
			EcsFactory::producers.Add(t.side) = p;
			EcsFactory::refurbishers.Add(t.side) = r;
		}
		
		return CastPtr<T>(CreateComponent(t));
	}
	
	void Clone(Main& dst, const Main& src);
	void ReturnComponent(Base* c);

	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::SYS_COMPONENTSTORE;}
	
private:
	
	Base* CreateComponent(TypeCompCls cls);
	
};





template<typename T>
void Entity::Remove0() {
	comps.Remove<T>(GetMachine().Get<ComponentStore>());
}

template<typename T>
RefT_Entity<T> Entity::Add0(CompCls cls) {
	auto comp = GetMachine().Get<ComponentStore>()->CreateComponent<T>(cls);
	ASSERT(comp);
	comp->SetParent(this);
	comps.Add(comp);
	return RefT_Entity<T>(this, comp);
}

NAMESPACE_ECS_END

#endif
