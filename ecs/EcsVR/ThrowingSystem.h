#pragma once

#if 1

NAMESPACE_ECS_BEGIN


// ThrowingInteractionSystem
// This ToolSystem manages the Throwing tool which allows you to throw baseballs in 3D scene
class ThrowingInteractionSystemHolo : public ThrowingInteractionSystemBase {
	
public:
	ThrowingInteractionSystemHolo(Engine& e) : ThrowingInteractionSystemBase(e) {}
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ThrowingInteractionSystemBase>(this);}
	
	
protected:
	// System
	void Update(double dt) override;
	
	// ISpatialInteractionListener
	void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	void OnSourceReleased(const SpatialInteractionSourceEventArgs& args) override;
	
};


NAMESPACE_ECS_END

#endif
