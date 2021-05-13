#include "EcsLib.h"


NAMESPACE_OULU_BEGIN



String ThrowingInteractionSystem::GetInstructions() const {
	return "Press and hold trigger to spawn a baseball.\n\n"
	       "Release trigger to throw the baseball.";
}

String ThrowingInteractionSystem::GetDisplayName() const {
	return "Throwing";
}

EntityRef ThrowingInteractionSystem::CreateToolSelector() const {
	auto selector = GetPool()->Create<ToolSelectorPrefab>();
	selector->Get<PbrRenderable>()->ResetModel("Baseball");
	selector->Get<ToolSelectorKey>()->type = GetType();
	return selector;
}

void ThrowingInteractionSystem::Update(double dt) {
	for (auto& enabled_entity : GetEnabledEntities()) {
		auto[entity, throwing] = enabled_entity;
		
		if (throwing->ball_object) {
			if (const SpatialInteractionSourceLocation location = entity->Get<MotionControllerComponent>()->location) {
				if (const SpatialPointerInteractionSourcePose pointer_pose = location.SourcePointerPose()) {
					auto transform = throwing->ball_object->Get<Transform>();
					transform->position = pointer_pose.Position() + pointer_pose.ForwardDirection() * BallHoldingDistance;
					transform->orientation = pointer_pose.Orientation();
					
					if (transform->size[0] < 1.0f) {
						transform->size += vec3( 2.0 * dt );
					}
				}
			}
		}
	}
}

void ThrowingInteractionSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args) {
	if (args.PressKind() == SpatialInteractionPressKind::Select) {
		if (auto enabled_entity = TryGetEntityFromSource(args.State().Source())) {
			auto throwing = enabled_entity->Get<ToolComponentRef>()->AsRef<ThrowingComponent>();
			auto ball = GetPool()->Create<Baseball>();
			ball->Get<Transform>()->size = vec3{ throwing->scale };
			ball->Get<RigidBody>()->SetEnabled(false);
			throwing->ball_object = std::move(ball);
		}
	}
}

void ThrowingInteractionSystem::OnSourceReleased(const SpatialInteractionSourceEventArgs& args) {
	if (args.PressKind() == SpatialInteractionPressKind::Select) {
		if (auto enabled_entity = TryGetEntityFromSource(args.State().Source())) {
			auto throwing = enabled_entity->Get<ToolComponentRef>()->AsRef<ThrowingComponent>();
			ASSERT(throwing);
			
			if (throwing->ball_object) {
				// We no longer need to keep a reference to the thrown ball.
				auto ball = throwing->ball_object;
				throwing->ball_object.Clear();
				// If the controller has no motion, release the ball with no initial velocity.
				ball->Get<RigidBody>()->SetEnabled(true);
				ball->Get<RigidBody>()->velocity = {};
				ball->Get<RigidBody>()->angular_velocity = {};
				// If controller has motion, use velocity and angular velocity at ball's holding distances.
				const SpatialCoordinateSystem coordinate_system = GetMachine().Get<HolographicScene>()->WorldCoordinateSystem();
				
				if (const SpatialInteractionSourceLocation grasp_location = args.State().Properties().TryGetLocation(coordinate_system)) {
					if (const SpatialPointerInteractionSourcePose pointer_pose = grasp_location.SourcePointerPose()) {
						const vec3 grasp_angular_velocity = grasp_location.AngularVelocity();
						
						if (!grasp_angular_velocity.IsNull()) {
							const vec3 ball_position = pointer_pose.Position() + (pointer_pose.ForwardDirection() * BallHoldingDistance);
							const vec3 ball_velocity = SpatialInputUtilities::Physics::GetVelocityNearSourceLocation(grasp_location, ball_position);
							
							if (!ball_velocity.IsNull()) {
								ball->Get<Transform>()->position = ball_position;
								ball->Get<Transform>()->orientation = pointer_pose.Orientation();
								ball->Get<RigidBody>()->velocity = ball_velocity;
								ball->Get<RigidBody>()->angular_velocity = grasp_angular_velocity;
							}
						}
					}
				}
			}
		}
	}
}

void ThrowingComponent::SetEnabled(bool enable) {
	Enableable::SetEnabled(enable);
	
	if (ball_object) {
		ball_object->SetEnabled(enable);
	}
}

void ThrowingComponent::Destroy() {
	Destroyable::Destroy();
	
	if (ball_object) {
		ball_object->Destroy();
	}
}


NAMESPACE_OULU_END
