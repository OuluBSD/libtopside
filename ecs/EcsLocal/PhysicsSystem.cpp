#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


PhysicsSystem::PhysicsSystem(Engine& e) : SP(e) {
	
	gravity = vec3{ 0, -9.8f, 0 };
	
}

void PhysicsSystem::Update(double dt)
{
	time += dt;
	
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
			
			t.position = vec3(x, 0, z);
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
		else {
			LOG("PhysicsBody::Arg: error: invalid test function: " + v);
			return false;
		}
	}
	
	return true;
}


NAMESPACE_ECS_END
