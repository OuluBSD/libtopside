#pragma once

#if 1

NAMESPACE_ECS_BEGIN

class ShootingComponent :
	public Component<ShootingComponent> {
	
public:
	RTTI_COMP0(ShootingComponent)
	COPY_PANIC(ShootingComponent)
	COMP_DEF_VISIT
	
	
	
	void SetEnabled(bool enable) override;
	void Destroy() override;
	
	EntityRef gun;
	
	float bullet_speed = 20.0f;
	mat4 barrel_to_ctrl;
};


// ShootingInteractionSystem
// This ToolSystem manages the Gun tool which allows you to shoot balls in the 3D scene

class ShootingInteractionSystem :
	public ToolSystem<ShootingInteractionSystem, ShootingComponent>
{
	
public:
	ECS_SYS_CTOR(ShootingInteractionSystem);
	using ToolSys = ToolSystem<ShootingInteractionSystem, ShootingComponent>;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ToolSys>(this);}
	
	using Parent = Engine;
	
	static constexpr const char* POOL_NAME = "shooting";
	
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
protected:
	// ToolSystemBase
	String GetInstructions() const override;
	String GetDisplayName() const override;
	EntityRef CreateToolSelector() const override;
	
	void Register(const LinkedList<EntityRef>& entities) override;
	void Activate(EntityRef entity) override;
	void Deactivate(EntityRef entity) override;
	
	// ISpatialInteractionListener
	//void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	//void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) override;
	
};

NAMESPACE_ECS_END

#endif
