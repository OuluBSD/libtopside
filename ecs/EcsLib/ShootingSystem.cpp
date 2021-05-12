#include "EcsLib.h"


String ShootingInteractionSystem::GetInstructions() const
{
    return "Pull the trigger to fire the gun.\n\n"
           "You can feel controller vibrate for each bullet.\n\n";
}

String ShootingInteractionSystem::GetDisplayName() const
{
    return "Shooting";
}

EntityRef ShootingInteractionSystem::CreateToolSelector() const
{
    auto selector = GetMachine().Get<EntityStore>()->Create<ToolSelectorPrefab>();

    selector->Get<PbrRenderable>()->ResetModel("Gun");
    selector->Get<ToolSelectorKey>()->type = type();

    return selector;
}

void ShootingInteractionSystem::Register(LinkedList<EntityRef>& entities)
{
    ToolSystem::Register(std::move(entities));

    // These values were created through trial and error and would be specific to the particular 3D model you choose to use for your gun.
    // In this scenario, we need to generate two transforms. 
    // First transform is used to align the 3D model with the physical MotionController: modelToController
    // Second transform is used to align the 3D model's barrel with the physical MotionController: barrel_to_ctrl

    // When using the MotionControllerComponent, the MotionControllerSystem will update the Transform component of the same object to match the controller's location.

    // The "modelToController" is to transform from the object's model space, to the location of the controller
    const mat4 modelToControllerRotation = make_mat4_from_yaw_pitch_roll(DirectX::XMConvertToRadians(180), DirectX::XMConvertToRadians(70), 0.0f);
    const mat4 modelToControllerTranslation = make_mat4_translation(0, 0.05f, 0.0f);
    const mat4 modelToController = modelToControllerRotation * modelToControllerTranslation;

    // The "barrel_to_ctrl" is to transform from the tip of the barrel to the location of the controller
    const mat4 barrel_to_ctrl = make_mat4_translation(0.0f, 0.0675f, -0.22f) * make_mat4_rotation_x(DirectX::XMConvertToRadians(-70));
    
    for (auto& entity : m_entities)
    {
        auto gun = GetMachine().Get<EntityStore>()->Create<Gun>();
        gun->Get<MotionControllerComponent>()->req_hand = entity->Get<MotionControllerComponent>()->req_hand;
        gun->Get<PbrRenderable>()->Offset = modelToController;

        entity->Get<ShootingComponent>()->barrel_to_ctrl = barrel_to_ctrl;
        entity->Get<ShootingComponent>()->gun = std::move(gun);
        entity->Get<ShootingComponent>()->SetEnabled(false);
    }
}

void ShootingInteractionSystem::Activate(Entity& entity)
{
    ToolSystem::Activate(entity);
    entity.Get<PbrRenderable>()->SetEnabled(false);
}

void ShootingInteractionSystem::Deactivate(Entity& entity)
{
    entity.Get<PbrRenderable>()->SetEnabled(true);
    ToolSystem::Deactivate(entity);
}

void ShootingInteractionSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args)
{
    if (auto enabledEntity = TryGetEntityFromSource(args.State().Source()))
    {
        auto shooting = std::get<ShootingComponent*>(*enabledEntity);

        if (args.PressKind() == SpatialInteractionPressKind::Select)
        {
            const mat4 barrelToWorld = shooting->barrel_to_ctrl * shooting->gun->Get<Transform>()->GetMatrix();

            const vec3 position = mat4_util::position(barrelToWorld);
            const quaternion orientation = make_quaternion_from_rotation_matrix(barrelToWorld);

            const vec3 forward = mat4_util::forward(barrelToWorld);
            const vec3 bulletVelocity = forward * shooting->bulletSpeed;

            // Create bullet and send it on it's merry way
            auto bullet = GetMachine().Get<EntityStore>()->Create<Bullet>();

            bullet->Get<Transform>()->position = position;
            bullet->Get<Transform>()->orientation = orientation;
            bullet->Get<RigidBody>()->velocity = bulletVelocity;

            SpatialInputUtilities::Haptics::SendContinuousBuzzForDuration(args.State().Source(), 125ms);
        }
    }
}

void ShootingInteractionSystem::OnSourceUpdated(const SpatialInteractionSourceEventArgs& args)
{
    if (auto enabledEntity = TryGetEntityFromSource(args.State().Source()))
    {
        auto[entity, shooting] = *enabledEntity;
        
        // Show the controllers while we're holding grasp, to help show how the model relates to the real world object
        const bool shouldRenderController = args.State().IsGrasped();

        entity->Get<PbrRenderable>()->SetEnabled(shouldRenderController);
        shooting->gun->Get<PbrRenderable>()->AlphaMultiplier = (shouldRenderController) ? std::make_optional(0.25f) : std::nullopt;
    }
}

void ShootingComponent::SetEnabled(bool enable) 
{
    Enableable::SetEnabled(enable);

    if (gun) {
        gun->SetEnabled(enable);
    }
}

void ShootingComponent::Destroy() 
{
    Destroyable::Destroy();

    if (gun) {
        gun->Destroy();
    }
}

