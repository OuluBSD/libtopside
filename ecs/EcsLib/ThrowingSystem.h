#pragma once


NAMESPACE_OULU_BEGIN

struct ThrowingComponent : Component<ThrowingComponent>
{
    void SetEnabled(bool enable) override;
    void Destroy() override;

    EntityRef ballObject;

    float distanceFromPointer = 0.05f;
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

