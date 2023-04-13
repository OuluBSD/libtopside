#pragma once


NAMESPACE_ECS_BEGIN


struct ShootingComponent : Neso::Component<ShootingComponent>
{
    void SetEnabled(bool enable) override;
    void Destroy() override;

    Neso::SharedEntity gun;

    float bulletSpeed = 20.0f;
    winrt::Windows::Foundation::Numerics::float4x4 barrelToController;
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
    Neso::SharedEntity CreateToolSelector() const override;

    void Register(std::vector<Neso::SharedEntity> entities) override;
    void Activate(Neso::Entity& entity) override;
    void Deactivate(Neso::Entity& entity) override;

    // ISpatialInteractionListener
    void OnSourcePressed(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;

    void OnSourceUpdated(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;
};


NAMESPACE_ECS_END
