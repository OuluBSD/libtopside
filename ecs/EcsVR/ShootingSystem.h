#pragma once

#if 1

NAMESPACE_ECS_BEGIN


// ShootingInteractionSystem
// This ToolSystem manages the Gun tool which allows you to shoot balls in the 3D scene

class ShootingInteractionSystemHolo :
	public ShootingInteractionSystemBase
{
	
public:
	RTTI_DECL1(ShootingInteractionSystemHolo, ShootingInteractionSystemBase)
	ShootingInteractionSystemHolo(Engine& e) : ShootingInteractionSystemBase(e) {}
	
protected:
	
	// ISpatialInteractionListener
	//void OnControllerPressed(const CtrlEvent& e) override;
	//void OnControllerUpdated(const CtrlEvent& e) override;
	
};

NAMESPACE_ECS_END

#endif
