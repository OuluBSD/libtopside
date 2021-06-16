#include "EcsLocal.h"

#ifdef flagVR

NAMESPACE_TOPSIDE_BEGIN


String ShootingInteractionSystem::GetInstructions() const {
	return "Pull the trigger to fire the gun.\n\n"
	       "You can feel controller vibrate for each bullet.\n\n";
}

String ShootingInteractionSystem::GetDisplayName() const {
	return "Shooting";
}

EntityRef ShootingInteractionSystem::CreateToolSelector() const {
	auto selector = GetPool()->Create<ToolSelectorPrefab>();
	selector->Get<PbrRenderable>()->ResetModel("Gun");
	selector->Get<ToolSelectorKey>()->type = GetType();
	return selector;
}

void ShootingInteractionSystem::Register(const LinkedList<EntityRef>& entities) {
	ToolSystem::Register(std::move(entities));
	// These values were created through trial and error and would be specific to the particular 3D model you choose to use for your gun.
	// In this scenario, we need to generate two transforms.
	// First transform is used to align the 3D model with the physical MotionController: model_to_controller
	// Second transform is used to align the 3D model's barrel with the physical MotionController: barrel_to_ctrl
	// When using the MotionControllerComponent, the MotionControllerSystem will update the Transform component of the same object to match the controller's location.
	// The "model_to_controller" is to transform from the object's model space, to the location of the controller
	const mat4 model_to_controller_rotation = make_mat4_from_yaw_pitch_roll(ConvertToRadians(180), ConvertToRadians(70), 0.0f);
	const mat4 model_to_controller_translation = make_mat4_translation(vec3(0, 0.05f, 0.0f));
	const mat4 model_to_controller = model_to_controller_rotation * model_to_controller_translation;
	// The "barrel_to_ctrl" is to transform from the tip of the barrel to the location of the controller
	const mat4 barrel_to_ctrl = translate(vec3(0.0f, 0.0675f, -0.22f)) * make_mat4_rotation_x(ConvertToRadians(-70));
	
	for (auto& entity : m_entities) {
		auto gun = GetPool()->Create<Gun>();
		gun->Get<MotionControllerComponent>()->req_hand = entity->Get<MotionControllerComponent>()->req_hand;
		gun->Get<PbrRenderable>()->offset = model_to_controller;
		entity->Get<ShootingComponent>()->barrel_to_ctrl = barrel_to_ctrl;
		entity->Get<ShootingComponent>()->gun = std::move(gun);
		entity->Get<ShootingComponent>()->SetEnabled(false);
	}
}

void ShootingInteractionSystem::Activate(EntityRef entity) {
	ToolSystem::Activate(entity);
	entity->Get<PbrRenderable>()->SetEnabled(false);
}

void ShootingInteractionSystem::Deactivate(EntityRef entity) {
	entity->Get<PbrRenderable>()->SetEnabled(true);
	ToolSystem::Deactivate(entity);
}

void ShootingInteractionSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args) {
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

void ShootingInteractionSystem::OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) {
	if (auto enabled_entity = TryGetEntityFromSource(args.State().Source())) {
		auto[entity, shooting] = *enabled_entity;
		// Show the controllers while we're holding grasp, to help show how the model relates to the real world object
		const bool should_render_controller = args.State().IsGrasped();
		entity->Get<PbrRenderable>()->SetEnabled(should_render_controller);
		shooting->gun->Get<PbrRenderable>()->alpha_multiplier = should_render_controller ? MakeOptional(0.25) : null_opt;
	}
}

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


NAMESPACE_TOPSIDE_END

#endif
