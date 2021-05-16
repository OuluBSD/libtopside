#pragma once

#ifdef flagVR

NAMESPACE_TOPSIDE_BEGIN

class ShootingComponent :
	public Component<ShootingComponent> {
	VIS_COMP_0_0
	
public:
	COPY_PANIC(ShootingComponent)
	void Visit(RuntimeVisitor& vis) override {}
	
	
	void SetEnabled(bool enable) override;
	void Destroy() override;
	
	EntityRef gun;
	
	float bullet_speed = 20.0f;
	mat4 barrel_to_ctrl;
};

////////////////////////////////////////////////////////////////////////////////
// ShootingInteractionSystem
// This ToolSystem manages the Gun tool which allows you to shoot balls in the 3D scene

class ShootingInteractionSystem :
	public ToolSystem<ShootingInteractionSystem, ShootingComponent>
{
	
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	SYS_CTOR(ShootingInteractionSystem);
	
	using Parent = Machine;
	
	static constexpr const char* POOL_NAME = "shooting";
	
	PoolRef GetPool() const {return GetMachine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
protected:
	// ToolSystemBase
	String GetInstructions() const override;
	String GetDisplayName() const override;
	EntityRef CreateToolSelector() const override;
	
	void Register(const LinkedList<EntityRef>& entities) override;
	void Activate(EntityRef entity) override;
	void Deactivate(EntityRef entity) override;
	
	// ISpatialInteractionListener
	void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) override;
	
};

NAMESPACE_TOPSIDE_END

#endif
