#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


World::World() {
	
}


void World::Step(float seconds) {
	TODO
}

void World::AttachThreading(Threading& t) {
	TODO
}

void World::DetachThreading() {
	TODO
}

void World::CreateBody(Body& b) {
	TODO
}

void World::CreateJoint(Joint& j) {
	TODO
}


World& World::SetGravity(const vec3& v) {
	TODO
}

World& World::SetMaxCorrectingVelocity(float f) {
	TODO
}

World& World::SetContactSurfaceLayer(float f) {
	TODO
}

World& World::SetAutoDisable(bool b) {
	TODO
}

World& World::SetStepIterations(int i) {
	TODO
}

World& World::SetAutoDisableSamples(int i) {
	TODO
}


}
NAMESPACE_TOPSIDE_END
