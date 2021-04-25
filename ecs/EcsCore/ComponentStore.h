#ifndef _EcsCore_ComponentStore_h_
#define _EcsCore_ComponentStore_h_

NAMESPACE_OULU_BEGIN
	

class ComponentStore :
	public System<ComponentStore>,
	public Factory<ComponentBase*, std::function<ComponentBase*()>, std::function<void(ComponentBase*)> >
{
	
public:
	using System::System;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	void ReturnComponent(ComponentBase* c);
	
	template<typename ComponentT>
	ComponentT* CreateComponent() {
		static_assert(IsComponent<ComponentT>::value, "T should be a component");
		
		const TypeId key(typeid(ComponentT));
		auto it = producers.Find(key);
		if (!it) {
			std::function<ComponentBase*()> p([] { return GetPool<ComponentT>().New();});
			std::function<void(ComponentBase*)> r([] (ComponentBase* b){ return GetPool<ComponentT>().Return(static_cast<ComponentT*>(b));});
			producers.Add(key) = p;
			refurbishers.Add(key) = r;
		}
		
		return static_cast<ComponentT*>(CreateComponent(typeid(ComponentT)));
	}
	
	void Clone(Entity& dst, const Entity& src);
	
	
protected:
	//void Update(double) override;
	//void Uninitialize() override;
	
private:
	
	ComponentBase* CreateComponent(const TypeId& type_id);
	
};


NAMESPACE_OULU_END

#endif
