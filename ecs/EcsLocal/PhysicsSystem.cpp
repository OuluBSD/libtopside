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
		//RTLOG("PhysicsSystem::Update: " << dt);
		
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
			rigid_body->velocity += rigid_body->acceleration * dt;
			transform->data.position += rigid_body->velocity * dt;
			
			vec3 adjusted_angular = TS::transform(rigid_body->angular_velocity, inverse(ToMat4(transform->data.orientation)));
			
			float angle = adjusted_angular.GetLength();
			if (angle > 0.0f) {
				vec3 axis = adjusted_angular / angle;
				transform->data.orientation *= AxisAngleQuat(axis, angle * dt);
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
		debug_log = (String)value == "debug";
	}
	if (key == "rm.outsiders") {
		remove_outside_area = (String)value == "true";
	}
	if (key == "rm.area.size") {
		area_length = StrDbl(value);
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
			
			t.data.position = vec3(x, 2, z);
			if (debug_log) {
				LOG("PhysicsSystem::RunTestFn: " << time << ": " << HexStr(&b) << ": " << x << ":" << z);
			}
		}
		
	}
	else if (b.test_fn == PhysicsBody::TESTFN_FIXED) {
		// pass
	}
	/*else if (b.test_fn == PhysicsBody::TESTFN_PLAYER_BODY) {
		FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
		
		if (!b.player)
			b.player = b.GetEntity()->Find<PlayerBodyComponent>();
		
		if (state->GetBool(MOUSE_LEFTDOWN)) {
			Point& drag = state->Set<Point>(MOUSE_TOYCOMPAT_DRAG);
			
			Point diff = drag - prev_mouse;
			
			if (prev_mouse.x != 0 && prev_mouse.y != 0 && (diff.x || diff.y))
				TestPlayerLookFn(b, diff);
			
			prev_mouse = drag;
		}
		else {
		!!!!!!
			if (!b.trans->use_lookat)
				TestPlayerLookFn(b, Point(0,0));
		!!!!
		
			prev_mouse = Point(0,0);
		}
		
		
		bool fwd   = data['w'];
		bool left  = data['a'];
		bool down  = data['s'];
		bool right = data['d'];
		
		float step = last_dt * 1.5;
		
		if (fwd) {
			TestPlayerMoveFn(b, vec3(0,0,1), step);
		}
		if (left) {
			TestPlayerMoveFn(b, vec3(-1,0,0), step);
		}
		if (down) {
			TestPlayerMoveFn(b, vec3(0,0,-1), step);
		}
		if (right) {
			TestPlayerMoveFn(b, vec3(+1,0,0), step);
		}/
	}*/
	else TODO
	
}

void PhysicsSystem::TestPlayerLookFn(PhysicsBody& b, Point mouse_diff) {
	TODO
	/*
	double rot_speed = 0.05 / (2*M_PI);
	yaw += mouse_diff.x * rot_speed;
	pitch += mouse_diff.y * rot_speed;
	
	//b.trans->use_lookat = true;
	auto head = b.player->GetHead();
	if (!head)
		return;
	
	head->up = vec3(0,1,0);
	head->direction =  vec3(
		 sin(pitch) * sin(yaw),
		 cos(pitch),
		-sin(pitch) * cos(yaw));
	
	#if 0
	const vec3& v = b.player->direction;
	LOG("dx: " << mouse_diff.x << ", dy: " << mouse_diff.y <<
		", rot: " << v[0] << ", " << v[1] << ", " << v[2] <<
		", angle: " << yaw << ss", angle1: " << pitch);
	#endif
	*/
}

void PhysicsSystem::TestPlayerMoveFn(PhysicsBody& b, vec3 rel_dir, float step) {
	TODO
	/*
	auto head = b.player->GetHead();
	if (!head)
		return;
	
	vec3& pos = b.trans->position;
	vec3 dir = head->direction;
	
	// remove y component
	dir[1] = 0;
	
	float straight = rel_dir[2];
	float sideways = rel_dir[0];
	
	if (straight) {
		pos += dir * step * straight;
	}
	if (sideways) {
		vec3 s = dir * step * sideways;
		pos[0] -= s[2];
		pos[2] += s[0];
	}
	*/
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
		if ((String)value == "true")
			return BindDefault();
	}
	else if (key == "test.fn") {
		String v = value;
		
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
