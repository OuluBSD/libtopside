#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN



	
	
void RigidBody::Initialize() {
	velocity = zero<vec3>();
	acceleration = zero<vec3>();
	angular_velocity = zero<vec3>();
	angular_acceleration = zero<vec3>();
	
	damping_factor = 0.999f;
	
}


NAMESPACE_ECS_END