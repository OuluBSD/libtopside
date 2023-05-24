#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


bool ThrowingInteractionSystemBase::Initialize() {
	ball_holding_distance = 0.5f;
	
	if (!InteractionListener::Initialize(GetEngine(), AsRefT<InteractionListener>()))
		return false;
	
	return true;
}

void ThrowingInteractionSystemBase::Uninitialize() {
	InteractionListener::Uninitialize(GetEngine(), AsRefT<InteractionListener>());
}

void ThrowingInteractionSystemBase::Attach(ThrowingComponentRef c) {
	ArrayFindAdd(comps, c);
}

void ThrowingInteractionSystemBase::Detach(ThrowingComponentRef c) {
	ArrayRemoveKey(comps, c);
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
	for (ThrowingComponentRef& throwing : comps) {
		EntityRef entity = throwing->GetEntity();
		TransformRef trans = entity->Find<Transform>();
		if (!trans)
			continue;
		
		if (throwing->ball_object) {
			if (!throwing->IsEnabled()) {
				throwing->ball_object->Destroy();
			}
			else {
				vec3 fwd_dir = trans->GetForwardDirection();
				TransformRef ball_transform = throwing->ball_object->Get<Transform>();
				ball_transform->data.position = trans->data.position + fwd_dir * ball_holding_distance;
				ball_transform->data.orientation = trans->data.orientation;
				
				if (ball_transform->size[0] < 1.0f) {
					ball_transform->size += vec3( 2.0f * (float)dt );
				}
			}
		}
	}
}

void ThrowingInteractionSystemBase::OnControllerUpdated(const CtrlEvent& e) {
	// pass
}

void ThrowingInteractionSystemBase::OnControllerPressed(const CtrlEvent& e) {
	if (e.type == EVENT_HOLO_PRESSED && e.value == ControllerMatrix::TRIGGER) {
		for (ThrowingComponentRef& throwing : comps) {
			if (!throwing->IsEnabled()) continue;
			
			throwing->ball_object = GetPool()->Create<Baseball>();
			throwing->ball_object->Get<Transform>()->size = vec3{ throwing->scale };
			throwing->ball_object->Get<RigidBody>()->SetEnabled(false);
			throwing->ball_object->Get<PhysicsBody>()->BindDefault();
		}
	}
}

void ThrowingInteractionSystemBase::OnControllerReleased(const CtrlEvent& e) {
	if (e.type == EVENT_HOLO_RELEASED && e.value == ControllerMatrix::TRIGGER) {
		ASSERT(e.ctrl);
		const ControllerState& source_state = e.GetState();
		const ControllerMatrix& source_props = source_state.props;
		const ControllerSource& source = source_state.GetSource();
		
		for (ThrowingComponentRef& throwing : comps) {
			if (!throwing->IsEnabled()) continue;
			
			EntityRef entity = throwing->GetEntity();
			TransformRef trans = entity->Find<Transform>();
			
			if (throwing->ball_object) {
				// We no longer need to keep a reference to the thrown ball.
				EntityRef ball = throwing->ball_object;
				throwing->ball_object.Clear();
				
				// If the controller has no motion, release the ball with no initial velocity.
				RigidBodyRef rb = ball->Get<RigidBody>();
				rb->SetEnabled(true);
				rb->velocity = {};
				rb->angular_velocity = {};
				
				TransformRef ball_trans = ball->Get<Transform>();
				
				vec3 position = trans->data.position;
				vec3 fwd_dir = trans->GetForwardDirection();
				
				
				vec3 velocity;
				vec3 grasp_angular_velocity;
				source.GetVelocity(velocity.data);
				source.GetAngularVelocity(grasp_angular_velocity.data);
				
				#if 1
				LOG("ThrowingInteractionSystemBase::OnControllerReleased: " <<
					"velocity: " << velocity.ToString() << ", "
					"grasp_angular_velocity: " << grasp_angular_velocity.ToString() << ")");
				#endif
				
				if (!grasp_angular_velocity.IsNull()) {
					const vec3 ball_position = position + (fwd_dir * ball_holding_distance);
					const vec3 ball_velocity = GetVelocityNearSourceLocation(position, velocity, grasp_angular_velocity, ball_position);
					
					if (!ball_velocity.IsNull()) {
						ball_trans->data.position = ball_position;
						ball_trans->data.orientation = trans->data.orientation;
						rb->velocity = ball_velocity;
						rb->angular_velocity = grasp_angular_velocity;
						
					}
				}
			}
		}
	}
}

void ThrowingInteractionSystemBase::Register() {
	// pass
}

void ThrowingInteractionSystemBase::Unregister() {
	// pass
}

void ThrowingInteractionSystemBase::Activate(EntityRef entity) {
	// pass
}

void ThrowingInteractionSystemBase::Deactivate(EntityRef entity) {
	// pass
}














void ThrowingComponent::Etherize(Ether& e) {
	CustomToolComponent::Etherize(e);
	
	e % distance_from_pointer
	  % scale;
	
	TODO // ref
}

void ThrowingComponent::Initialize() {
	ToolComponentRef tool = GetEntity()->Find<ToolComponent>();
	if (tool)
		tool->AddTool(AsRefT<ComponentBase>());
	
	Ref<ThrowingInteractionSystemBase> sys = GetEngine().TryGet<ThrowingInteractionSystemBase>();
	if (sys)
		sys-> Attach(AsRefT());
}

void ThrowingComponent::Uninitialize() {
	ToolComponentRef tool = GetEntity()->Find<ToolComponent>();
	if (tool)
		tool->RemoveTool(AsRefT<ComponentBase>());
	
	Ref<ThrowingInteractionSystemBase> sys = GetEngine().TryGet<ThrowingInteractionSystemBase>();
	if (sys)
		sys->Detach(AsRefT());
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

bool ThrowingComponent::LoadModel(ModelComponent& mdl) {
	mdl.Clear();
	return true;
}



NAMESPACE_ECS_END
