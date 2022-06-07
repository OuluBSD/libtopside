#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


bool ThrowingInteractionSystemBase::Initialize() {
	if (!InteractionListener::Initialize(GetEngine(), AsRefT<InteractionListener>()))
		return false;
	
	return true;
}

void ThrowingInteractionSystemBase::Uninitialize() {
	InteractionListener::Uninitialize(GetEngine(), AsRefT<InteractionListener>());
}

String ThrowingInteractionSystemBase::GetInstructions() const {
	return "Press and hold trigger to spawn a baseball.\n\n"
	       "Release trigger to throw the baseball.";
}

String ThrowingInteractionSystemBase::GetDisplayName() const {
	return "Throwing";
}

EntityRef ThrowingInteractionSystemBase::CreateToolSelector() const {
	auto selector = GetPool()->Create<ToolSelectorPrefab>();
	selector->Get<ModelComponent>()->SetPrefabModel("Baseball");
	selector->Get<ToolSelectorKey>()->type = GetType();
	return selector;
}

void ThrowingInteractionSystemBase::Update(double dt) {
	TODO
	#if 0
	Vector<RTuple<EntityRef, ToolComponentRef>> enabled_ents = GetEnabledEntities();
	
	for (RTuple<EntityRef, ToolComponentRef>& enabled_entity : enabled_ents) {
		EntityRef& entity = enabled_entity.a;
		ToolComponentRef& throwing = enabled_entity.b.a;
		
		if (throwing->ball_object) {
			if (const HandActionSourceLocation* location = entity->Get<PlayerHandComponent>()->location) {
				if (const HandActionSourcePose* pointer_pose = location->GetHandPose()) {
					auto transform = throwing->ball_object->Get<Transform>();
					transform->position = pointer_pose->GetPosition() + pointer_pose->GetForwardDirection() * ball_holding_distance;
					transform->orientation = pointer_pose->GetOrientation();
					
					if (transform->size[0] < 1.0f) {
						transform->size += vec3( 2.0 * dt );
					}
				}
			}
		}
	}
	#endif
}
#if 0
void ThrowingInteractionSystemBase::OnControllerPressed(const ControllerEventArgs& args) {
	if (args.PressKind() == SpatialInteractionPressKind::Select) {
		if (auto enabled_entity = TryGetEntityFromSource(args.State().Source())) {
			auto throwing = enabled_entity->Get<ToolComponentRef>()->AsRef<ThrowingComponent>();
			throwing->ball_object = GetPool()->Create<Baseball>();
			throwing->ball_object->Get<Transform>()->size = vec3{ throwing->scale };
			throwing->ball_object->Get<RigidBody>()->SetEnabled(false);
		}
	}
}

void ThrowingInteractionSystemBase::OnControllerReleased(const ControllerEventArgs& args) {
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
				const SpatialCoordinateSystem coordinate_system = GetEngine().Get<HolographicScene>()->WorldCoordinateSystem();
				
				if (const HandActionSourceLocation grasp_location = args.State().Properties().TryGetLocation(coordinate_system)) {
					if (const HandActionSourcePose pointer_pose = grasp_location.SourcePointerPose()) {
						const vec3 grasp_angular_velocity = grasp_location.AngularVelocity();
						
						if (!grasp_angular_velocity.IsNull()) {
							const vec3 ball_position = pointer_pose.Position() + (pointer_pose.ForwardDirection() * ball_holding_distance);
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
#endif
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


NAMESPACE_ECS_END
