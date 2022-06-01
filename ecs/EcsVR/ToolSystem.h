#ifndef _EcsVR_ToolSystem_h_
#define _EcsVR_ToolSystem_h_

NAMESPACE_ECS_BEGIN


// CRTP implementation helper
// Usage: class MyToolSystem : ToolSystem<MyToolSystem> { /* functions + data members */ };
// Adds functionality to automatically register to listeners and helpers to access entities
// that actually have the associated ToolComponent attached and enabled
template<typename T, typename ToolComponent>
class ToolSystemHoloT :
	public ToolSystemBaseT<T>,
	public SpatialInteractionListener
{
	
public:
	RTTI_DECL2(ToolSystem, ToolSystemBase, SpatialInteractionListener)
	void Visit(RuntimeVisitor& vis) override {TODO}
	TypeCls GetType() const override {return AsTypeCls<T>();}
	
	using ToolComponentRef = Ref<ToolComponent, RefParent1<Entity>>;
	
	
protected:
	
	// ToolSystemBase
	void Register(const LinkedList<EntityRef>& entities) override {
		ToolSystemBaseT<T>::Register(entities);
		
		Engine& m = GetEngine();
		m.Get<SpatialInteractionSystem>()->AddListener(AsRefT<SpatialInteractionListener>());
	}
	
	void Unregister() override {
		Engine& m = GetEngine();
		TODO //m.Get<SpatialInteractionSystem>()->RemoveListener(AsRef<ISpatialInteractionListener>());
		
		ToolSystemBaseT<T>::Unregister();
	}
	
	// Internal helpers
	Vector<RTuple<EntityRef, ToolComponentRef>> GetEnabledEntities() const {
		Vector<RTuple<EntityRef, ToolComponentRef>> entities;
		
		for (auto& entity : m_entities) {
			auto comp = entity->Get<ToolComponent>();
			
			if (comp->IsEnabled()) {
				entities.Add(RTuple<EntityRef, ToolComponentRef>(entity, comp));
			}
		}
		
		return entities;
	}
	
	Optional<RTuple<EntityRef, ToolComponentRef>> TryGetEntityFromSource(const SpatialInteractionSource& source) const {
		TODO
		/*for (auto& entity : m_entities) {
			auto comp = entity->Get<ToolComponent>();
			
			if (comp->IsEnabled()) {
				if (entity->Get<MotionControllerComponent>()->IsSource(source)) {
					return RTuple<EntityRef, ToolComponentRef>(entity, comp);
				}
			}
		}
		
		return null_opt;*/
	}
	
};

NAMESPACE_ECS_END

#endif
