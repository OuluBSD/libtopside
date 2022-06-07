#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


bool ShootingInteractionSystemBase::Initialize() {
	if (!InteractionListener::Initialize(GetEngine(), AsRefT<InteractionListener>()))
		return false;
	
	return true;
}

void ShootingInteractionSystemBase::Uninitialize() {
	InteractionListener::Uninitialize(GetEngine(), AsRefT<InteractionListener>());
}

String ShootingInteractionSystemBase::GetInstructions() const {
	return "Pull the trigger to fire the gun.\n\n"
	       "You can feel controller vibrate for each bullet.\n\n";
}

String ShootingInteractionSystemBase::GetDisplayName() const {
	return "Shooting";
}

EntityRef ShootingInteractionSystemBase::CreateToolSelector() const {
	auto selector = GetPool()->Create<ToolSelectorPrefab>();
	selector->Get<ModelComponent>()->SetPrefabModel("Gun");
	selector->Get<ToolSelectorKey>()->type = GetType();
	return selector;
}

#if 0
void ShootingInteractionSystemBase::Register(const LinkedList<EntityRef>& entities) {
	ASSERT(!entities.IsEmpty());
	ToolSys::Register(entities);
	
	// The "barrel_to_ctrl" is to transform from the tip of the barrel to the location of the controller
	const mat4 barrel_to_ctrl = translate(vec3(0.0f, 0.0675f, -0.22f)) * make_mat4_rotation_x(ConvertToRadians(-70));
	
	TODO
	#if 0
	for (auto& entity : m_entities) {
		auto gun = GetPool()->Create<Gun>();
		gun->Get<PlayerHandComponent>()->req_hand = entity->Get<PlayerHandComponent>()->req_hand;
		
		// These values were created through trial and error and would be specific to the particular 3D model you choose to use for your gun.
		// In this scenario, we need to generate two transforms.
		// First transform is used to align the 3D model with the physical MotionController: model_to_controller
		// Second transform is used to align the 3D model's barrel with the physical MotionController: barrel_to_ctrl
		// When using the PlayerHandComponent, the MotionControllerSystem will update the Transform component of the same object to match the controller's location.
		Ref<ModelComponent> m = gun->Get<ModelComponent>();
		m->SetRotation(ConvertToRadians(180), ConvertToRadians(70), 0.0f);
		m->SetTranslation(vec3(0, 0.05f, 0.0f));
		
		entity->Get<ShootingComponent>()->barrel_to_ctrl = barrel_to_ctrl;
		entity->Get<ShootingComponent>()->gun = gun;
		entity->Get<ShootingComponent>()->SetEnabled(false);
	}
	#endif
}

void ShootingInteractionSystemBase::Activate(EntityRef entity) {
	ToolSystemBaseT::Activate(entity);
	entity->Get<ModelComponent>()->SetEnabled(false);
}

void ShootingInteractionSystemBase::Deactivate(EntityRef entity) {
	entity->Get<ModelComponent>()->SetEnabled(true);
	ToolSystemBaseT::Deactivate(entity);
}

void ShootingInteractionSystemBase::OnControllerPressed(const ControllerEventArgs& args) {
	if (auto enabled_entity = TryGetEntityFromSource(args.State().Source())) {
		auto shooting = enabled_entity->Get<ToolComponentRef>().AsRef<ShootingComponent>();
		
		if (args.PressKind() == SpatialInteractionPressKind::Select) {
			const mat4 barrel_to_world = shooting->barrel_to_ctrl * shooting->gun->Get<Transform>()->GetMatrix();
			const vec3 position = MatrixUtils::position(barrel_to_world);
			const quat orientation = make_quat_from_rotation_matrix(barrel_to_world);
			const vec3 forward = MatrixUtils::forward(barrel_to_world);
			const vec3 bullet_velocity = forward * shooting->bullet_speed;
			// Create bullet and send it on it's merry way
			auto bullet = GetPool()->Create<Bullet>();
			bullet->Get<Transform>()->position = position;
			bullet->Get<Transform>()->orientation = orientation;
			bullet->Get<RigidBody>()->velocity = bullet_velocity;
			SpatialInputUtilities::Haptics::SendContinuousBuzzForDuration(args.State().Source(), 125_ms);
		}
	}
}

void ShootingInteractionSystemBase::OnControllerUpdated(const ControllerEventArgs& args) {
	Optional<RTuple<EntityRef, ToolComponentRef>> enabled_entity = TryGetEntityFromSource(args.State().Source());
	if (enabled_entity) {
		EntityRef& entity = enabled_entity->a;
		ToolComponentRef& shooting = enabled_entity->b.a;
		
		// Show the controllers while we're holding grasp, to help show how the model relates to the real world object
		const bool should_render_controller = args.State().IsGrasped();
		entity->Get<ModelComponent>()->SetEnabled(should_render_controller);
		shooting->gun->Get<ModelComponent>()->alpha_multiplier = should_render_controller ? MakeOptional(0.25) : null_opt;
	}
}
#endif
void ShootingComponent::SetEnabled(bool enable) {
	Enableable::SetEnabled(enable);
	
	if (gun) {
		gun->SetEnabled(enable);
	}
}

void ShootingComponent::Destroy() {
	Destroyable::Destroy();
	
	if (gun) {
		gun->Destroy();
	}
}


NAMESPACE_ECS_END
