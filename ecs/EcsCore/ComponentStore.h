#ifndef _EcsCore_ComponentStore_h_
#define _EcsCore_ComponentStore_h_

NAMESPACE_OULU_BEGIN
	

class ComponentStore : public System<ComponentStore>, public Factory<ComponentRef, std::function<ComponentRef()>> {

public:
	using System::System;
	
	template<typename... ComponentTs>
	ComponentMap CreateComponentMap();/* {
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all be a component");
		
		return ComponentMap { { typeid(ComponentTs), CreateComponent<ComponentTs>() }... };
	}*/
	
	template<typename ComponentT>
	ComponentRef CreateComponent();/* {
		static_assert(IsComponent<ComponentT>::value, "T should be a component");
		
		const TypeId key(typeid(ComponentT));
		
		auto it = producers.FindIter(key);
		
		if (!it) {
			std::function<ComponentRef()> fn([] { return MakeSharedBase<ComponentBase, ComponentT>(); });
			producers.Add(key) = fn;
		}
		
		return CreateComponent(typeid(ComponentT));
	}*/
	
	ComponentMap Clone(const ComponentMap& comp_map);
	
	
protected:
	void Update(double) override;
	void Uninitialize() override;
	
private:
	//RefTypeMap<RefLinkedList<ComponentBase>> comps;
	
	ComponentRef CreateComponent(const TypeId& typeId);
};


NAMESPACE_OULU_END

#endif
