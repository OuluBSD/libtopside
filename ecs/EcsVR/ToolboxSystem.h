#pragma once

#if 1

NAMESPACE_ECS_BEGIN


// ToolboxSystem
// This system manages the ToolSystems and manages the two Entities that represent the left and
// right Motion Controllers
class ToolboxSystemHolo :
	public ToolboxSystemBase
{
	
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	RTTI_DECL1(ToolboxSystemHolo, ToolboxSystemBase)
	ToolboxSystemHolo(Engine& e) : ToolboxSystemBase(e) {}
	
protected:
	// System
	void Start() override;
	void Stop() override;
	
	// InteractionListener
	void OnControllerPressed(const CtrlEvent& e) override;
	
private:
	
	//static PlayerHandedness ControllerHandToHandedness(ControllerHand hand);
	
	EntityRef FindController(const SpatialInteractionSource& source);
	
	
	
	
};

NAMESPACE_ECS_END

#endif
