#pragma once

#ifdef flagVR

NAMESPACE_TOPSIDE_BEGIN

////////////////////////////////////////////////////////////////////////////////
// ToolSystemBase
// Base abstract class for all ToolSystems
class ToolSystemBase : public SystemBase {
public:
	using SystemBase::SystemBase;
	
	virtual String GetInstructions() const = 0;
	virtual String GetDisplayName() const = 0;
	
	virtual EntityRef CreateToolSelector() const = 0;
	
	virtual void Register(const LinkedList<EntityRef>& entities) = 0;
	virtual void Unregister() = 0;
	virtual void Activate(EntityRef entity) = 0;
	virtual void Deactivate(EntityRef entity) = 0;
};

class ToolSelectorKey :
	public Component<ToolSelectorKey> {
	VIS_COMP_0_0
	
public:
	COPY_PANIC(ToolSelectorKey)
	void Visit(RuntimeVisitor& vis) override {}
	
	TypeId type { typeid(void) };
};

struct ToolSelectorPrefab :
	EntityPrefab <
	Transform,
	PbrRenderable,
	ToolSelectorKey,
	RigidBody,
	Easing
	> {
	
	static Components Make(Entity& e) {
		auto components = EntityPrefab::Make(e);
		components.Get<RigidBody>().angular_velocity = { 0.0f, -3.0f, 0.0f }; // Spin in place
		components.Get<RigidBody>().damping_factor = 1.0f;
		components.Get<Easing>().position_easing_factor = 0.1f;
		return components;
	}
};

// CRTP implementation helper
// Usage: class MyToolSystem : ToolSystem<MyToolSystem> { /* functions + data members */ };
// Adds functionality to automatically register to listeners and helpers to access entities
// that actually have the associated ToolComponent attached and enabled
template<typename T, typename ToolComponent>
class ToolSystem :
	public ToolSystemBase,
	public ISpatialInteractionListener
{
	
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	TypeId GetType() const override {return typeid(T);}
	
	using ToolComponentRef = Ref<ToolComponent, RefParent1<Entity>>;
	
	
protected:
	// System
	void Start() override {
		Machine& m = GetMachine();
		m.Get<ToolboxSystem>()->AddToolSystem(AsRef<ToolSystemBase>());
	}
	
	void Stop() override {
		Machine& m = GetMachine();
		m.Get<ToolboxSystem>()->RemoveToolSystem(AsRef<ToolSystemBase>());
	}
	
	// ToolSystemBase
	void Register(const LinkedList<EntityRef>& entities) override {
		m_entities <<= entities;
		
		for (auto& entity : m_entities) {
			entity->Add<ToolComponent>()->SetEnabled(false);
		}
		
		Machine& m = GetMachine();
		m.Get<SpatialInteractionSystem>()->AddListener(AsRef<ISpatialInteractionListener>());
	}
	
	void Unregister() override {
		Machine& m = GetMachine();
		m.Get<SpatialInteractionSystem>()->RemoveListener(AsRef<ISpatialInteractionListener>());
		
		for (auto& entity : m_entities) {
			entity->Remove<ToolComponent>();
		}
		
		m_entities.Clear();
	}
	
	void Activate(EntityRef entity) override {
		entity->Get<ToolComponent>()->SetEnabled(true);
	}
	
	void Deactivate(EntityRef entity) override {
		entity->Get<ToolComponent>()->SetEnabled(false);
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
		for (auto& entity : m_entities) {
			auto comp = entity->Get<ToolComponent>();
			
			if (comp->IsEnabled()) {
				if (entity->Get<MotionControllerComponent>()->IsSource(source)) {
					return RTuple<EntityRef, ToolComponentRef>(entity, comp);
				}
			}
		}
		
		return null_opt;
	}
	
	LinkedList<EntityRef> m_entities;
};

NAMESPACE_TOPSIDE_END

#endif
