#ifndef _EcsVR_PaintingSystem_h_
#define _EcsVR_PaintingSystem_h_

NAMESPACE_ECS_BEGIN


class PaintingInteractionSystemHolo :
	public PaintingInteractionSystemBase
{
public:
	RTTI_DECL1(PaintingInteractionSystemHolo, PaintingInteractionSystemBase)
	PaintingInteractionSystemHolo(Engine& e) : PaintingInteractionSystemBase(e) {}
	
	
protected:
	void Update(double dt) override;
	void Register() override;
	
	void OnControllerPressed(const CtrlEvent& e) override;
	//void OnControllerUpdated(const CtrlEvent& e) override;
	//void OnControllerReleased(const CtrlEvent& e) override;
	
};


NAMESPACE_ECS_END

#endif
