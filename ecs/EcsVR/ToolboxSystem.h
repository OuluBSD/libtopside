#pragma once

#if 1

NAMESPACE_ECS_BEGIN


// ToolboxSystem
// This system manages the ToolSystems and manages the two Entities that represent the left and
// right Motion Controllers
class ToolboxSystemHolo :
	public ToolboxSystemBase,
	public SpatialInteractionListener
{
	
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	RTTI_DECL2(ToolboxSystem, ToolboxSystemBase, SpatialInteractionListener)
	ToolboxSystem(Engine& e) : ToolboxSystemBase(e) {}
	
protected:
	// System
	void Start() override;
	void Stop() override;
	
	// ISpatialInteractionListener
	void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	
private:
	
	static SpatialInteractionSourceHandedness ControllerHandToHandedness(ControllerHand hand);
	
	EntityRef FindController(const SpatialInteractionSource& source);
	
	
	
	
};

NAMESPACE_ECS_END

#endif
