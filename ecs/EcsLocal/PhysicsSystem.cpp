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
	else if (b.test_fn == PhysicsBody::TESTFN_PLAYER) {
		FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
		
		if (state->GetBool(MOUSE_LEFTDOWN)) {
			Point& drag = state->Set<Point>(MOUSE_TOYCOMPAT_DRAG);
			
			Point diff = drag - prev_mouse;
			
			if (prev_mouse.x != 0 && prev_mouse.y != 0 && (diff.x || diff.y)) {
				double sensitivity = 0.05 / (2*M_PI);
				double pitch = diff.y * sensitivity;
				double yaw = diff.x * sensitivity;
				
				pitch += prev_pitch;
				yaw += prev_yaw;
				
				#if 1
				quat q_pitch = make_quat_from_axis_angle(vec3(1, 0, 0), pitch);
				quat q_yaw = make_quat_from_axis_angle(vec3(0, 1, 0), yaw);
				quat orientation = q_pitch * q_yaw;
				#else
				quat orientation = make_quat_from_yaw_pitch_roll(yaw, pitch, 0);
				#endif
				
				orientation.Normalize();
				b.trans->orientation = orientation;
				//DUMP(b.trans->orientation);
				//DUMP(orientation);
				
				prev_pitch = pitch;
				prev_yaw = yaw;
			}
			
			prev_mouse = drag;
		}
		
		bool fwd   = data['W'];
		bool left  = data['A'];
		bool down  = data['S'];
		bool right = data['D'];
		
		if (fwd) {
			b.trans->position[2] += last_dt * 0.5;
		}
		if (left) {
			b.trans->position[0] -= last_dt * 0.5;
		}
		if (down) {
			b.trans->position[2] -= last_dt * 0.5;
		}
		if (right) {
			b.trans->position[0] += last_dt * 0.5;
		}
	}
	else TODO
	
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
		if (v == "do.circle")
			test_fn = TESTFN_CIRCLE;
		else if (v == "fixed")
			test_fn = TESTFN_FIXED;
		else if (v == "player")
			test_fn = TESTFN_PLAYER;
		else {
			LOG("PhysicsBody::Arg: error: invalid test function: " + v);
			return false;
		}
	}
	
	return true;
}


NAMESPACE_ECS_END
