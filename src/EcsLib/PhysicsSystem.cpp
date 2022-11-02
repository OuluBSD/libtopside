#include "EcsLib.h"


#if 0

NAMESPACE_TOPSIDE_BEGIN


const vec3 PhysicsSystem::EarthGravity = { 0, -9.8f, 0 };

void PhysicsSystem::Update(double dt)
{
	PoolRef p = GetMachine().Get<EntityStore>()->GetRoot();
	auto comps = p->GetComponents<Transform, RigidBody>();
    for (auto& tuple : comps) {
        Transform& transform = tuple.Get<Transform>();
        RigidBody& rigid_body = tuple.Get<RigidBody>();
        
        rigid_body.velocity += rigid_body.acceleration * dt;
        transform.position += rigid_body.velocity * dt;

        const vec3 adjusted_angular = TS::transform(rigid_body.angular_velocity, inverse(transform.orientation));

        const float angle = adjusted_angular.GetLength();
        if (angle > 0.0f)
        {
            const vec3 axis = adjusted_angular / angle;
            transform.orientation *= make_quat_from_axis_angle(axis, angle * dt);
        }

        rigid_body.velocity *= rigid_body.damping_factor;
        rigid_body.angular_velocity *= rigid_body.damping_factor;
    }
}


NAMESPACE_TOPSIDE_END

#endif
