#if 0
#include "EcsWin.h"


NAMESPACE_ECS_BEGIN



using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;

constexpr float BallHoldingDistance = 0.075f;

std::wstring_view ThrowingInteractionSystem::GetInstructions() const
{
    return L"Press and hold trigger to spawn a baseball.\n\n"
           L"Release trigger to throw the baseball.";
}

std::wstring_view ThrowingInteractionSystem::GetDisplayName() const
{
    return L"Throwing";
}

EntityRef ThrowingInteractionSystem::CreateToolSelector() const
{
    auto selector = m_engine.Get<EntityStore>()->Create<ToolSelectorPrefab>();

    selector->Get<PbrRenderable>()->ResetModel("Baseball");
    selector->Get<ToolSelectorKey>()->type = type();

    return selector;
}

void ThrowingInteractionSystem::Update(double dt)
{
    for (auto& enabledEntity : GetEnabledEntities())
    {
        auto[entity, throwing] = enabledEntity;

        if (throwing->ballObject)
        {
            if (const SpatialInteractionSourceLocation location = entity->Get<MotionControllerComponent>()->location)
            {
                if (const SpatialPointerInteractionSourcePose pointerPose = location.SourcePointerPose())
                {
                    auto transform = throwing->ballObject->Get<Transform>();

                    transform->position = pointerPose.Position() + pointerPose.ForwardDirection() * BallHoldingDistance;
                    transform->orientation = pointerPose.Orientation();

                    if (transform->scale.x < 1.0f)
                    {
                        transform->scale += float3{ 2.0f * dt };
                    }
                }
            }
        }
    }
}

void ThrowingInteractionSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args)
{
    if (args.PressKind() == SpatialInteractionPressKind::Select)
    {
        if (auto enabledEntity = TryGetEntityFromSource(args.State().Source()))
        {
            auto throwing = std::get<ThrowingComponent*>(*enabledEntity);

            auto ball = m_engine.Get<EntityStore>()->Create<Baseball>();
            ball->Get<Transform>()->size = float3{ throwing->scale };
            ball->Get<RigidBody>()->SetEnabled(false);
            throwing->ballObject = std::move(ball);
        }
    }
}

void ThrowingInteractionSystem::OnSourceReleased(const SpatialInteractionSourceEventArgs& args)
{
    if (args.PressKind() == SpatialInteractionPressKind::Select)
    {
        if (auto enabledEntity = TryGetEntityFromSource(args.State().Source()))
        {
            auto throwing = std::get<ThrowingComponent*>(*enabledEntity);
            fail_fast_if(!throwing);

            if (throwing->ballObject)
            {
                // We no longer need to keep a reference to the thrown ball.
                auto ball = throwing->ballObject;
                throwing->ballObject.reset();

                // If the controller has no motion, release the ball with no initial velocity.
                ball->Get<RigidBody>()->SetEnabled(true);
                ball->Get<RigidBody>()->velocity = {};
                ball->Get<RigidBody>()->angularVelocity = {};

                // If controller has motion, use velocity and angular velocity at ball's holding distances.
                const SpatialCoordinateSystem coordinateSystem = m_engine.Get<HolographicScene>()->WorldCoordinateSystem();
                if (const SpatialInteractionSourceLocation graspLocation = args.State().Properties().TryGetLocation(coordinateSystem))
                {
                    if (const SpatialPointerInteractionSourcePose pointerPose = graspLocation.SourcePointerPose())
                    {
                        if (const IReference<float3> graspAngularVelocity = graspLocation.AngularVelocity()) 
                        {
                            const float3 ballPosition = pointerPose.Position() + (pointerPose.ForwardDirection() * BallHoldingDistance);

                            if (const std::optional<float3> ballVelocity = SpatialInputUtilities::Physics::GetVelocityNearSourceLocation(graspLocation, ballPosition))
                            {
                                ball->Get<Transform>()->position = ballPosition;
                                ball->Get<Transform>()->orientation = pointerPose.Orientation();
                                ball->Get<RigidBody>()->velocity = ballVelocity.value();
                                ball->Get<RigidBody>()->angularVelocity = graspAngularVelocity.Value();
                            }
                        }
                    }
                }
            }
        }
    }
}

void ThrowingComponent::SetEnabled(bool enable) 
{
    Enableable::SetEnabled(enable);

    if (ballObject) {
        ballObject->SetEnabled(enable);
    }
}

void ThrowingComponent::Destroy() 
{
    Destroyable::Destroy();

    if (ballObject) {
        ballObject->Destroy();
    }
}


NAMESPACE_ECS_END
#endif
