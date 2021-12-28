#include "Physics.h"

NAMESPACE_TOPSIDE_BEGIN


void TosFys::InitializeLibrary() {
	TODO
}

void TosFys::UninitializeLibrary() {
	TODO
}


void TosFys::CreateWorld(SoftPhys::World& world) {
	TODO
}

void TosFys::ClearWorld(SoftPhys::World& world) {
	TODO
}

void TosFys::SetGravity(SoftPhys::World& world, const vec3& v) {
	TODO
}

void TosFys::SetWorldCFM(SoftPhys::World& world, float f) {
	TODO
}

void TosFys::SetMaxCorrectingVelocity(SoftPhys::World& world, float f) {
	TODO
}

void TosFys::SetContactSurfaceLayer(SoftPhys::World& world, float f) {
	TODO
}

void TosFys::SetAutoDisable(SoftPhys::World& world, bool b) {
	TODO
}

void TosFys::SetStepIterations(SoftPhys::World& world, int i) {
	TODO
}

void TosFys::SetAutoDisableSamples(SoftPhys::World& world, int i) {
	TODO
}


void TosFys::CreateSpace(SoftPhys::Space& space, SoftPhys::Space* owner, bool is_root) {
	TODO
}

void TosFys::ClearSpace(SoftPhys::Space& space) {
	TODO
}

void TosFys::Collide(SoftPhys::Space& space, void* data, NearCallback cb) {
	TODO
}

int TosFys::Collide(SoftPhys::Geometry& o1, SoftPhys::Geometry& o2, int count, SoftPhys::Contact* c, int ptr_pitch) {
	TODO
}

void TosFys::Step(SoftPhys::World& world, float seconds) {
	TODO
}

void TosFys::AttachContact(SoftPhys::World& w, SoftPhys::JointGroup& cg, SoftPhys::Contact& c, float slip1, float slip2, float erp, float cfm) {
	TODO
}

void TosFys::AddGeomToSpace(SoftPhys::Space& space, SoftPhys::Geometry& geom) {
	TODO
}

void TosFys::RemoveGeomFromSpace(SoftPhys::Space& space, SoftPhys::Geometry& geom) {
	TODO
}


void TosFys::CreateJointGroup(SoftPhys::JointGroup& g) {
	TODO
}

void TosFys::ClearJointGroup(SoftPhys::JointGroup& g) {
	TODO
}

void TosFys::DetachJointGroup(SoftPhys::JointGroup& g) {
	TODO
}


void TosFys::CreateThreading(SoftPhys::Threading& t) {
	TODO
}

void TosFys::CreateThreadPool(SoftPhys::ThreadPool& p) {
	TODO
}

void TosFys::AttachThreadPool(SoftPhys::Threading& t, SoftPhys::ThreadPool& p) {
	TODO
}

void TosFys::AttachThreading(SoftPhys::World& w, SoftPhys::Threading& t) {
	TODO
}

void TosFys::DetachThreading(SoftPhys::World& w) {
	TODO
}

void TosFys::DetachThreading(SoftPhys::Threading& t) {
	TODO
}

void TosFys::ClearThreadPool(SoftPhys::ThreadPool& p) {
	TODO
}

void TosFys::ClearThreading(SoftPhys::Threading& t) {
	TODO
}


void TosFys::CreateBody(SoftPhys::World& w, SoftPhys::Body& b) {
	TODO
}

void TosFys::ClearBody(SoftPhys::Body& b) {
	TODO
}

vec3 TosFys::GetBodyPosition(SoftPhys::Body& b) {
	TODO
}

void TosFys::SetBodyMass(SoftPhys::Body& b, SoftPhys::Mass& m) {
	TODO
}

void TosFys::SetBodyPosition(SoftPhys::Body& b, float x, float y, float z) {
	TODO
}

void TosFys::SetBodyQuaternion(SoftPhys::Body& b, const quat& q) {
	TODO
}

void TosFys::SetBodyLinearVelocity(SoftPhys::Body& b, const vec3& v) {
	TODO
}

void TosFys::SetBodyAngularVelocity(SoftPhys::Body& b, const vec3& v) {
	TODO
}


void TosFys::ClearGeom(SoftPhys::Geometry& g) {
	TODO
}

void TosFys::SetGeomModelPlane(SoftPhys::Geometry& g, SoftPhys::Space& s, float a, float b, float c, float d) {
	TODO
}

void TosFys::SetGeomModelSphere(SoftPhys::Geometry& g, float radius) {
	TODO
}

void TosFys::SetGeomModelBox(SoftPhys::Geometry& g, float w, float h, float l) {
	TODO
}

void TosFys::SetGeomPosition(SoftPhys::Geometry& g, float x, float y, float z) {
	TODO
}

void TosFys::SetGeomRotationAxisAngle(SoftPhys::Body& body, float ax, float ay, float az, float angle) {
	TODO
}

void TosFys::SetGeomBody(SoftPhys::Geometry& g, SoftPhys::Body& b) {
	TODO
}

void TosFys::ResetGeomRotation(SoftPhys::Geometry& geom) {
	TODO
}

vec3 TosFys::GetGeomPosition(SoftPhys::Geometry& geom) {
	TODO
}

quat TosFys::GetGeomQuaternion(SoftPhys::Geometry& geom) {
	TODO
}

mat43 GetGeomRotationAxisAngle(SoftPhys::Body& body) {
	TODO
}

void TosFys::CreateJointHinge2(SoftPhys::World& w, SoftPhys::Joint& j) {
	TODO
}

void TosFys::AttachJoint(SoftPhys::Joint& j, SoftPhys::Body& b0, SoftPhys::Body& b1) {
	TODO
}


void TosFys::SetJointFeedback(SoftPhys::Joint& j, SoftPhys::Feedback& fb) {
	TODO
}

void TosFys::SetJointHingeAnchor(SoftPhys::Joint& j, const vec3& pos) {
	TODO
}

void TosFys::SetJointHingeAxes(SoftPhys::Joint& j, const vec3& axis1, const vec3& axis2) {
	TODO
}

void TosFys::SetSuspensionERP(SoftPhys::Joint& j, float erp) {
	TODO
}

void TosFys::SetSuspensionCFM(SoftPhys::Joint& j, float cfm) {
	TODO
}

void TosFys::SetHingeRange(SoftPhys::Joint& j, float lo, float hi, int idx) {
	TODO
}

void TosFys::SetHingeVelocity(SoftPhys::Joint& j, float v, int idx) {
	TODO
}

void TosFys::SetMaxForce(SoftPhys::Joint& j, float v, int idx) {
	TODO
}

void TosFys::SetFudgeFactor(SoftPhys::Joint& j, float v) {
	TODO
}

void TosFys::SetHingeAnchor(SoftPhys::Joint& j, const vec3& v) {
	TODO
}

void TosFys::SetAxis(SoftPhys::Joint& j, const vec3& v) {
	TODO
}

float TosFys::GetAngle(SoftPhys::Joint& j) {
	TODO
}



// utility functions
void TosFys::SetQuatFromAxisAngle(quat& q, const vec3& axis, float angle) {
	TODO
}

void TosFys::SetMassFunctionSphere(SoftPhys::Mass& mass, float density, float radius) {
	TODO
}

void TosFys::SetMassFunctionBox(SoftPhys::Mass& mass, float w, float h, float l) {
	TODO
}

void TosFys::SetMass(SoftPhys::Mass& mass, float kg) {
	TODO
}


NAMESPACE_TOPSIDE_END
