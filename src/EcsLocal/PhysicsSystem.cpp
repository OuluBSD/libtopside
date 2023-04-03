#include "EcsLocal.h"
#include <SerialCore/SerialCore.h>


NAMESPACE_ECS_BEGIN


PhysicsSystem::PhysicsSystem(Engine& e) : SP(e) {
	gravity = vec3{ 0, -9.8f, 0 };
	
}

void PhysicsSystem::Update(double dt)
{
	time += dt;
	last_dt = dt;
	
	if (debug_log) {
		
	}
	
	for (PhysicsBody* b : bodies) {
		
		if (b->test_fn) {
			RunTestFn(*b);
			continue;
		}
		
		
		EntityRef ent = b->GetEntity();
		Ref<RigidBody> rigid_body = ent->Find<RigidBody>();
		Ref<Transform> transform = ent->Find<Transform>();
		
		if (rigid_body && transform && rigid_body->IsEnabled()) {
			rigid_body->velocity += rigid_body->acceleration * (float)dt;
			transform->data.position += rigid_body->velocity * (float)dt;
			
			vec3 adjusted_angular = TS::VectorTransform(rigid_body->angular_velocity, Inverse(QuatMat(transform->data.orientation)));
			
			float angle = adjusted_angular.GetLength();
			if (angle > 0.0f) {
				vec3 axis = adjusted_angular / angle;
				transform->data.orientation *= AxisAngleQuat(axis, angle * (float)dt);
			}
			
			rigid_body->velocity *= rigid_body->damping_factor;
			rigid_body->angular_velocity *= rigid_body->damping_factor;
		}
		
		if (transform) {
			vec3 a = transform->data.position.GetAbsolute();
			if (a[0] >= area_length ||
				a[1] >= area_length ||
				a[2] >= area_length)
				ent->Destroy();
		}
	}
	
}

bool PhysicsSystem::Arg(String key, Object value) {
	
	if (key == "log") {
		debug_log = value.ToString() == "debug";
	}
	if (key == "rm.outsiders") {
		remove_outside_area = value.ToString() == "true";
	}
	if (key == "rm.area.size") {
		area_length = value.ToFloat();
	}
	
	return true;
}

void PhysicsSystem::Attach(PhysicsBody& b) {
	VectorFindAdd(bodies, &b);
}

void PhysicsSystem::Detach(PhysicsBody& b) {
	VectorRemoveKey(bodies, &b);
}

void PhysicsSystem::RunTestFn(PhysicsBody& b) {
	ASSERT(b.test_fn);
	
	if (b.test_fn == PhysicsBody::TESTFN_CIRCLE) {
		
		if (b.trans) {
			Transform& t = *b.trans;
			double phase = time * 0.5;
			double radius = 3;
			double x = sin(phase) * radius;
			double z = cos(phase) * radius;
			
			t.data.position = vec3((float)x, 2, (float)z);
			if (debug_log) {
				LOG("PhysicsSystem::RunTestFn: " << time << ": " << HexStr(&b) << ": " << x << ":" << z);
			}
		}
		
	}
	else if (b.test_fn == PhysicsBody::TESTFN_FIXED) {
		// pass
	}
	else TODO
	
}

void PhysicsSystem::TestPlayerLookFn(PhysicsBody& b, Point mouse_diff) {
	TODO
	
}

void PhysicsSystem::TestPlayerMoveFn(PhysicsBody& b, vec3 rel_dir, float step) {
	TODO
	
}






void PhysicsBody::Initialize() {
	test_fn = 0;
	is_bound = 0;
	
	Entity& e = GetParent();
	trans = e.Find<Transform>();
	if (!trans) {
		LOG("PhysicsBody:Initialize: error: transform component was not found");
	}
}

void PhysicsBody::Uninitialize() {
	if (is_bound)
		UnbindDefault();
	
}

bool PhysicsBody::Arg(String key, Object value) {
	
	if (key == "bind") {
		if (value.ToString() == "true")
			return BindDefault();
	}
	else if (key == "test.fn") {
		String v = value.ToString();
		
		if      (v == "do.circle")			test_fn = TESTFN_CIRCLE;
		else if (v == "fixed")				test_fn = TESTFN_FIXED;
		else {
			LOG("PhysicsBody::Arg: error: invalid test function: " + v);
			return false;
		}
	}
	
	return true;
}

bool PhysicsBody::BindDefault() {
	if (is_bound) {
		LOG("PhysicsBody::BindDefault: already bound");
		return false;
	}
	
	Ref<PhysicsSystem> fys = GetEngine().TryGet<PhysicsSystem>();
	if (!fys) {
		LOG("PhysicsBody::BindDefault: error: no PhysicsSystem in engine");
		return false;
	}
	
	fys->Attach(*this);
	is_bound = true;
	
	return true;
}

void PhysicsBody::UnbindDefault() {
	ASSERT(is_bound);
	
	Ref<PhysicsSystem> fys = GetEngine().TryGet<PhysicsSystem>();
	if (!fys) {
		LOG("PhysicsBody::UnbindDefault: error: no PhysicsSystem in engine");
		return;
	}
	
	fys->Detach(*this);
	
	is_bound = false;
}

NAMESPACE_ECS_END
