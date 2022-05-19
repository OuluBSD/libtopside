#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


PhysicsSystem::PhysicsSystem(Engine& e) : SP(e) {
	
	gravity = vec3{ 0, -9.8f, 0 };
	
}

void PhysicsSystem::Update(double dt)
{
	if (debug_log) {
		RTLOG("PhysicsSystem::Update: " << dt );
		
	}
	
	
}

bool PhysicsSystem::Arg(String key, Object value) {
	
	if (key == "log") {
		debug_log = (String)value == "debug";
	}
	
	return true;
}






bool PhysicsBody::Arg(String key, Object value) {
	
	if (key == "bind") {
		//TODO
	}
	
	return true;
}


NAMESPACE_ECS_END
