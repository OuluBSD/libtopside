#ifndef _EcsCore_ComponentStore_h_
#define _EcsCore_ComponentStore_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Main, class Base>
class ComponentStoreT :
	public System<ComponentStoreT<Main,Base>>,
	public Factory<Base*, std::function<Base*()>, std::function<void(Base*)> >
{
	
	
public:
	using ComponentStore = ComponentStoreT<Main,Base>;
	RTTI_DECL1(ComponentStoreT, System<ComponentStore>)
	SYS_CTOR(ComponentStoreT);
	SYS_DEF_VISIT
	
	using Parent = Machine;
	using Factory = TS::Factory<Base*, std::function<Base*()>, std::function<void(Base*)> >;
	template<typename T> using IsComponent = std::is_base_of<Base, T>;
	template<typename T> using IsConnector = std::is_base_of<Base, T>;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	ComponentBase* CreateComponentTypeCls(TypeCls key);
	
	template<typename T>
	T* CreateComponent() {
		static_assert(IsComponent<T>::value, "T should be a component");
		
		TypeCls key(AsTypeCls<T>());
		auto it = Factory::producers.Find(key);
		if (!it) {
			std::function<Base*()> p([] { return GetPool<T>().New();});
			std::function<void(Base*)> r([] (Base* b){ GetPool<T>().Return(CastPtr<T>(b));});
			Factory::producers.Add(key) = p;
			Factory::refurbishers.Add(key) = r;
		}
		
		return CastPtr<T>(CreateComponent(AsTypeCls<T>()));
	}
	
	void Clone(Main& dst, const Main& src) {
		const ComponentMap& src_comps = src.GetComponents();
		ComponentMap& dst_comps = dst.GetComponents();
		
		ComponentMap::Iterator iter = const_cast<ComponentMap&>(src_comps).begin();
		for (; iter; ++iter) {
			TypeCls comp_type = iter.key();
			Base* new_component = CreateComponent(comp_type);
			dst.InitializeComponent(*new_component);
			iter.value().CopyTo(new_component);
			dst_comps.ComponentMapBase::Add(comp_type, new_component);
		}
	}
	
	void ReturnComponent(Base* c) {
		ASSERT(c);
		TypeCls type = c->GetType();
		
		auto iter = Factory::refurbishers.Find(type);
		if (iter)
			iter.Get()(c);
	}

	
private:
	
	Base* CreateComponent(TypeCls typeId) {
		auto iter = Factory::producers.Find(typeId);
		ASSERT_(iter, "Invalid to create non-existant component");
		
		Base* obj = iter.value()();
		return obj;
	}
	
};

using ComponentStore = ComponentStoreT<Entity, ComponentBase>;
using ConnectorStore = ComponentStoreT<Pool, ConnectorBase>;


NAMESPACE_TOPSIDE_END

#endif
