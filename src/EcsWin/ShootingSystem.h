#pragma once


NAMESPACE_WIN_BEGIN


struct ShootingComponent : Component<ShootingComponent>
{
    void SetEnabled(bool enable) override;
    void Destroy() override;

    EntityRef gun;

    float bulletSpeed = 20.0f;
    winrt::Windows::Foundation::Numerics::float4x4 barrelToController;
    
    COPY_PANIC(ShootingComponent)
    
};

////////////////////////////////////////////////////////////////////////////////
// ShootingInteractionSystem
// This ToolSystem manages the Gun tool which allows you to shoot balls in the 3D scene

class ShootingInteractionSystem : public ToolSystem<ShootingInteractionSystem, ShootingComponent>
{
public:
    using ToolSystem::ToolSystem;

protected:
    // ToolSystemBase
    std::wstring_view GetInstructions() const override;
    std::wstring_view GetDisplayName() const override;
    EntityRef CreateToolSelector() const override;

    void Register(Array<EntityRef>& entities) override;
    void Activate(Entity& entity) override;
    void Deactivate(Entity& entity) override;

    // ISpatialInteractionListener
    void OnSourcePressed(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;

    void OnSourceUpdated(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;
};


NAMESPACE_WIN_END
