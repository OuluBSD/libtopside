#pragma once


NAMESPACE_OULU_BEGIN


class ThrowingComponent :
	public Component<ThrowingComponent>
{
	VIS_COMP_0_0
	
public:
	COPY_PANIC(ThrowingComponent)
	void Visit(RuntimeVisitor& vis) override {}
	
    void SetEnabled(bool enable) override;
    void Destroy() override;

    EntityRef ball_object;

    float distance_from_pointer = 0.05f;
    float scale = 0.25f;
};

////////////////////////////////////////////////////////////////////////////////
// ThrowingInteractionSystem
// This ToolSystem manages the Throwing tool which allows you to throw baseballs in 3D scene
class ThrowingInteractionSystem : public ToolSystem<ThrowingInteractionSystem, ThrowingComponent>
{
public:
    using ToolSystem::ToolSystem;

protected:
    // System
    void Update(double dt) override;

    // IInteractionModeSystem
    String GetInstructions() const override;
    String GetDisplayName() const override;
    EntityRef CreateToolSelector() const override;

    // ISpatialInteractionListener
    void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
    void OnSourceReleased(const SpatialInteractionSourceEventArgs& args) override;
    
};


NAMESPACE_OULU_END

