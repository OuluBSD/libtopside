#pragma once

#if 1

NAMESPACE_ECS_BEGIN

// ToolSystemBase
// Base abstract class for all ToolSystems
class ToolSystemBase : public SystemBase {
public:
	RTTI_DECL1(ToolSystemBase, SystemBase);
	using SystemBase::SystemBase;
	
	void Visit(RuntimeVisitor& vis) override {}
	
	virtual String GetInstructions() const = 0;
	virtual String GetDisplayName() const = 0;
	
	virtual EntityRef CreateToolSelector() const = 0;
	
	virtual void Register() = 0;
	virtual void Unregister() = 0;
	virtual void Activate(EntityRef entity) = 0;
	virtual void Deactivate(EntityRef entity) = 0;
};

class ToolSelectorKey :
	public Component<ToolSelectorKey> {
	
public:
	RTTI_COMP0(ToolSelectorKey)
	COPY_PANIC(ToolSelectorKey)
	COMP_DEF_VISIT
	
	
	TypeId type { AsVoidTypeId() };
	
	void Etherize(Ether& e) override;
	
};

struct ToolSelectorPrefab :
	EntityPrefab <
	Transform,
	ModelComponent,
	ToolSelectorKey,
	RigidBody,
	Easing
	> {
	
	static Components Make(Entity& e) {
		auto components = EntityPrefab::Make(e);
		RigidBodyRef rb = components.Get<RigidBodyRef>();
		EasingRef ea = components.Get<EasingRef>();
		rb->angular_velocity = { 0.0f, -3.0f, 0.0f }; // Spin in place
		rb->damping_factor = 1.0f;
		ea->position_easing_factor = 0.1f;
		return components;
	}
};

template<typename T, typename ToolComponent>
class ToolSystemBaseT :
	public ToolSystemBase,
	public InteractionListener
{
	
public:
	typedef ToolSystemBaseT<T, ToolComponent> CLASSNAME;
	RTTI_DECL2(ToolSystemBaseT, ToolSystemBase, InteractionListener)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ToolSystemBase>(this); /*vis && m_entities;*/}
	TypeCls GetType() const override {return AsTypeCls<T>();}
	
	
	
	
protected:
	// System
	void Start() override {
		Engine& m = GetEngine();
		m.Get<ToolboxSystemBase>()->AddToolSystem(AsRef<ToolSystemBase>());
	}
	
	void Stop() override {
		Engine& m = GetEngine();
		m.Get<ToolboxSystemBase>()->RemoveToolSystem(AsRef<ToolSystemBase>());
	}
	
};

NAMESPACE_ECS_END

#endif
