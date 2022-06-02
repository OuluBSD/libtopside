#include "EcsVR.h"


NAMESPACE_ECS_BEGIN



#if 0
void ShootingInteractionSystemHolo::OnSourcePressed(const SpatialInteractionSourceEventArgs& args) {
	if (auto enabled_entity = TryGetEntityFromSource(args.State().Source())) {
		auto shooting = enabled_entity->Get<ToolComponentRef>().AsRef<ShootingComponent>();
		TODO
		/*if (args.PressKind() == SpatialInteractionPressKind::Select) {
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
		}*/
	}
}

void ShootingInteractionSystemHolo::OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) {
	Optional<RTuple<EntityRef, ToolComponentRef>> enabled_entity = TryGetEntityFromSource(args.State().Source());
	if (enabled_entity) {
		TODO
		/*EntityRef& entity = enabled_entity->a;
		ToolComponentRef& shooting = enabled_entity->b.a;
		
		// Show the controllers while we're holding grasp, to help show how the model relates to the real world object
		const bool should_render_controller = args.State().IsGrasped();
		entity->Get<PbrRenderable>()->SetEnabled(should_render_controller);
		shooting->gun->Get<PbrRenderable>()->alpha_multiplier = should_render_controller ? MakeOptional(0.25) : null_opt;*/
	}
}
#endif



NAMESPACE_ECS_END

