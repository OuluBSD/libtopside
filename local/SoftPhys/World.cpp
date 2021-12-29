#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


World::World() {
	gravity.Clear();
	
}


void World::Step(float seconds) {
	TODO
}

void World::AttachThreading(Threading& t) {
	t.DetachWorld();
	DetachThreading();
	ASSERT(!t.world && !threading);
	threading = &t;
	t.world = this;
}

void World::DetachThreading() {
	if (threading) {
		threading->world = 0;
		threading = 0;
	}
}

void World::CreateBody(Body& b) {
	TODO
}

void World::CreateJoint(Joint& j) {
	TODO
}


World& World::SetGravity(const vec3& v) {
	gravity = v;
	return *this;
}

World& World::SetMaxCorrectingVelocity(float f) {
	correcting_velocity = f;
	return *this;
}

World& World::SetContactSurfaceLayer(float f) {
	surface_layer = f;
	return *this;
}

World& World::SetAutoDisable(bool b) {
	auto_disable = b;
	return *this;
}

World& World::SetStepIterations(int i) {
	iters = i;
	return *this;
}

World& World::SetAutoDisableSamples(int i) {
	auto_disable_samples = i;
	return *this;
}


}
NAMESPACE_TOPSIDE_END
