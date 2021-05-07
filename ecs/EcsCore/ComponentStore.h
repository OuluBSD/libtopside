#ifndef _EcsCore_ComponentStore_h_
#define _EcsCore_ComponentStore_h_

NAMESPACE_OULU_BEGIN


template <class Main, class Base>
class ComponentStoreT :
	public System<ComponentStoreT<Main,Base>>,
	public Factory<Base*, std::function<Base*()>, std::function<void(Base*)> >
{
	
public:
	using Parent = Machine;
	using System<ComponentStoreT<Main,Base>>::System;
	using Factory = Oulu::Factory<Base*, std::function<Base*()>, std::function<void(Base*)> >;
	template<typename T> using IsComponent = std::is_base_of<Base, T>;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	template<typename T>
	T* CreateComponent() {
		static_assert(IsComponent<T>::value, "T should be a component");
		
		const TypeId key(typeid(T));
		auto it = Factory::producers.Find(key);
		if (!it) {
			std::function<Base*()> p([] { return GetPool<T>().New();});
			std::function<void(Base*)> r([] (Base* b){ return GetPool<T>().Return(static_cast<T*>(b));});
			Factory::producers.Add(key) = p;
			Factory::refurbishers.Add(key) = r;
		}
		
		return static_cast<T*>(CreateComponent(typeid(T)));
	}
	
	void Clone(Main& dst, const Main& src) {
		const ComponentMap& src_comps = src.GetComponents();
		ComponentMap& dst_comps = dst.GetComponents();
		
		ComponentMap::Iterator iter = const_cast<ComponentMap&>(src_comps).begin();
		for (; iter; ++iter) {
			const TypeId& comp_type = iter.key();
			Base* new_component = CreateComponent(comp_type);
			dst.InitializeComponent(*new_component);
			iter.value().CopyTo(new_component);
			dst_comps.ComponentMapBase::Add(comp_type, new_component);
		}
	}
	
	void ReturnComponent(Base* c) {
		ASSERT(c);
		TypeId type = c->GetType();
		
		auto iter = Factory::refurbishers.Find(type);
		if (iter)
			iter.Get()(c);
	}

	
private:
	
	Base* CreateComponent(const TypeId& typeId) {
		auto iter = Factory::producers.Find(typeId);
		ASSERT_(iter, "Invalid to create non-existant component");
		
		Base* obj = iter.value()();
		return obj;
	}
	
};

using ComponentStore = ComponentStoreT<Entity, ComponentBase>;
using ConnectorStore = ComponentStoreT<Pool, ConnectorBase>;


NAMESPACE_OULU_END

#endif
