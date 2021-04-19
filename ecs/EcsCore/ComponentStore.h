#ifndef _EcsCore_ComponentStore_h_
#define _EcsCore_ComponentStore_h_

NAMESPACE_OULU_BEGIN
	

class ComponentStore : public System<ComponentStore>, public Factory < SharedComponent, std::function<SharedComponent()>> {

public:
	using System::System;
	
	template<typename... ComponentTs>
	ComponentMap CreateComponentMap() {
		static_assert(AllComponents<ComponentTs...>::value, "Ts should all be a component");
		
		return ComponentMap { { typeid(ComponentTs), CreateComponent<ComponentTs>() }... };
	}
	
	template<typename ComponentT>
	SharedComponent CreateComponent() {
		static_assert(IsComponent<ComponentT>::value, "T should be a component");
		
		const TypeId key(typeid(ComponentT));
		
		int pos = m_producers.Find(key);
		
		if (pos == -1) {
			std::function<SharedComponent()> fn([] { return MakeSharedBase<ComponentBase, ComponentT>(); });
			m_producers.Add(key) = fn;
		}
		
		return CreateComponent(typeid(ComponentT));
	}
	
	ComponentMap Clone(const ComponentMap& comp_map);
	
	
protected:
	void Update(float) override;
	void Uninitialize() override;
	
private:
	UnorderedTypeMap < Vector < SharedComponent >> m_components;
	
	SharedComponent CreateComponent(const TypeId& typeId);
};


NAMESPACE_OULU_END

#endif
