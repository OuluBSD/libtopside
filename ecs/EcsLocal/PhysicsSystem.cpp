#include "EcsLocal.h"
#include <SerialCore/SerialCore.h>


NAMESPACE_ECS_BEGIN


PhysicsSystem::PhysicsSystem(Engine& e) : SP(e) {
	prev_mouse = Point(0,0);
	gravity = vec3{ 0, -9.8f, 0 };
	
}

void PhysicsSystem::Update(double dt)
{
	time += dt;
	last_dt = dt;
	
	if (!env_name.IsEmpty()) {
		Serial::Machine& m = Serial::GetActiveMachine();
		Ref<LoopStore> ls = m.Find<LoopStore>();
		LoopRef l = ls->GetRoot();
		state = l->GetSpace()->FindStateDeep(env_name);
		if (!state) {
			LOG("PhysicsSystem::Arg: error: environment state with name '" << env_name << "' not found");
		}
		env_name.Clear();
	}

	if (debug_log) {
		//RTLOG("PhysicsSystem::Update: " << dt);
		
	}
	
	for (PhysicsBody* b : bodies) {
		
		if (b->test_fn) {
			RunTestFn(*b);
			continue;
		}
		
		TODO
	}
	
}

bool PhysicsSystem::Arg(String key, Object value) {
	
	if (key == "log") {
		debug_log = (String)value == "debug";
	}
	
	if (key == "env") {
		env_name = value;
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
			
			t.position = vec3(x, 2, z);
			if (debug_log) {
				LOG("PhysicsSystem::RunTestFn: " << time << ": " << HexStr(&b) << ": " << x << ":" << z);
			}
		}
		
	}
	else if (b.test_fn == PhysicsBody::TESTFN_FIXED) {
		// pass
	}
	else if (b.test_fn == PhysicsBody::TESTFN_PLAYER_BODY) {
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
			if (!b.trans->use_lookat)
				TestPlayerLookFn(b, Point(0,0));
			prev_mouse = Point(0,0);
		}
		
		
		bool fwd   = data['W'];
		bool left  = data['A'];
		bool down  = data['S'];
		bool right = data['D'];
		
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
		}
	}
	else TODO
	
}

void PhysicsSystem::TestPlayerLookFn(PhysicsBody& b, Point mouse_diff) {
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
}

void PhysicsSystem::TestPlayerMoveFn(PhysicsBody& b, vec3 rel_dir, float step) {
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
}






void PhysicsBody::Initialize() {
	Entity& e = GetParent();
	trans = e.Find<Transform>();
	if (!trans) {
		LOG("PhysicsBody:Initialize: error: transform component was not found");
	}
}

bool PhysicsBody::Arg(String key, Object value) {
	
	if (key == "bind") {
		Ref<PhysicsSystem> fys = GetEngine().Get<PhysicsSystem>();
		if (!fys) {
			LOG("PhysicsBody::Arg: error: no PhysicsSystem in engine");
			return false;
		}
		
		fys->Attach(*this);
	}
	else if (key == "test.fn") {
		String v = value;
		
		if      (v == "do.circle")			test_fn = TESTFN_CIRCLE;
		else if (v == "fixed")				test_fn = TESTFN_FIXED;
		else if (v == "player.body")		test_fn = TESTFN_PLAYER_BODY;
		
		else {
			LOG("PhysicsBody::Arg: error: invalid test function: " + v);
			return false;
		}
	}
	
	return true;
}


NAMESPACE_ECS_END
