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

class ShootingInteractionSystemHolo :
	public ShootingInteractionSystemBase
{
	
public:
	RTTI_DECL1(ShootingInteractionSystemHolo, ShootingInteractionSystemBase)
	ShootingInteractionSystemHolo(Engine& e) : PaintingInteractionSystemBase(e) {}
	
protected:
	
	// ISpatialInteractionListener
	void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) override;
	
};

NAMESPACE_ECS_END

#endif
