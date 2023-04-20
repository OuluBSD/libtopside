#if 0
#pragma once


NAMESPACE_ECS_BEGIN


struct ThrowingComponent : Component<ThrowingComponent>
{
    void SetEnabled(bool enable) override;
    void Destroy() override;

    EntityRef ballObject;

    float distanceFromPointer = 0.05f;
    float scale = 0.25f;
    
    COPY_PANIC(ThrowingComponent)
    
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
    std::wstring_view GetInstructions() const override;
    std::wstring_view GetDisplayName() const override;
    EntityRef CreateToolSelector() const override;

    // ISpatialInteractionListener
    void OnSourcePressed(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;

    void OnSourceReleased(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;
};


NAMESPACE_ECS_END
#endif
