#pragma once


NAMESPACE_OULU_BEGIN

struct ShootingComponent : Component<ShootingComponent>
{
    void SetEnabled(bool enable) override;
    void Destroy() override;

    EntityRef gun;

    float bulletSpeed = 20.0f;
    mat4 barrel_to_ctrl;
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
    String GetInstructions() const override;
    String GetDisplayName() const override;
    EntityRef CreateToolSelector() const override;

    void Register(LinkedList<EntityRef>& entities) override;
    void Activate(EntityRef entity) override;
    void Deactivate(EntityRef entity) override;

    // ISpatialInteractionListener
    void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) override;
	
};

NAMESPACE_OULU_END
