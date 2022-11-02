#include "Physics.h"

NAMESPACE_TOPSIDE_BEGIN

void TosFys::InitializeLibrary() {
	
}

void TosFys::UninitializeLibrary() {
	
}

void TosFys::CreateWorld(NativeWorld& world) {
	world = new SoftPhys::World();
}

void TosFys::ClearWorld(NativeWorld& world) {
	delete world;
	world = 0;
}

void TosFys::SetGravity(NativeWorld& world, float f) {
	world->SetGravity(vec3(0,f,0));
}

void TosFys::SetWorldCFM(NativeWorld& world, float f) {
	
}

void TosFys::SetMaxCorrectingVelocity(NativeWorld& world, float f) {
	world->SetMaxCorrectingVelocity(f);
}

void TosFys::SetContactSurfaceLayer(NativeWorld& world, float f) {
	world->SetContactSurfaceLayer(f);
}

void TosFys::SetAutoDisable(NativeWorld& world, bool b) {
	world->SetAutoDisable(b);
}

void TosFys::SetStepIterations(NativeWorld& world, int i) {
	world->SetStepIterations(i);
}

void TosFys::SetAutoDisableSamples(NativeWorld& world, int i) {
	world->SetAutoDisableSamples(i);
}

void TosFys::CreateSpace(NativeSpace& space, bool is_root) {
	if (is_root) {
		space = new SoftPhys::Space();
	} else {
		space = new SoftPhys::Space();
		TODO
	}
}

void TosFys::ClearSpace(NativeSpace& space) {
	delete space;
	space = 0;
}

void TosFys::Collide(NativeSpace& space, void* data, NearCallback cb) {
	space->Collide(data, cb);
}

void TosFys::Step(NativeWorld& world, float seconds) {
	world->Step(seconds);
}

void TosFys::CreateJointGroup(NativeJointGroup& g) {
	g = new SoftPhys::JointGroup;
}

void TosFys::ClearJointGroup(NativeJointGroup& g) {
	delete g;
	g = 0;
}

void TosFys::DetachJointGroup(NativeJointGroup& g) {
	g->Detach();
}

void TosFys::CreateThreading(NativeThreading& t) {
	t = new SoftPhys::Threading();
}

void TosFys::CreateThreadPool(NativeThreadPool& p) {
	p = new SoftPhys::ThreadPool();
}

void TosFys::AttachThreadPool(NativeThreading& t, NativeThreadPool& p) {
	t->Add(*p);
}

void TosFys::AttachThreading(NativeWorld& w, NativeThreading& t) {
	w->AttachThreading(*t);
}

void TosFys::DetachThreading(NativeThreading& t) {
	t->Detach();
}

void TosFys::DetachThreading(NativeWorld& w) {
	w->DetachThreading();
}

void TosFys::ClearThreadPool(NativeThreadPool& p) {
	p->ClearThreading();
}

void TosFys::ClearThreading(NativeThreading& t) {
	t->Clear();
}

TosFys::NativeBody TosFys::CreateBody(NativeWorld w) {
	NativeBody b = new SoftPhys::Body();
	b->SetWorld(*w);
	return b;
}

vec3 TosFys::GetBodyPosition(NativeBody b) {
	return b->GetPosition();
}

void TosFys::SetBodyPosition(NativeBody body, float x, float y, float z) {
	body->SetPosition(vec3(x,y,z));
}

void TosFys::SetGeomPosition(NativeGeom geom, float x, float y, float z) {
	geom->SetPosition(vec3(x,y,z));
}

void TosFys::ResetGeomRotation(NativeGeom geom) {
	mat4 m;
	m.SetIdentity();
	geom->SetWorldMatrix(m);
}

void TosFys::SetGeomRotationAxisAngle(NativeGeom geom, float ax, float ay, float az, float angle) {
	geom->SetRotation(vec3(ax,ay,az), angle);
}

TosFys::NativeJoint TosFys::CreateJointHinge2(NativeWorld w) {
	NativeJoint joint = new SoftPhys::Joint();
	w->CreateJoint(*joint);
	return joint;
}

void TosFys::SetJointFeedback(NativeJoint j, NativeFeedback& fb) {
	j->SetFeedback(*fb);
}

void TosFys::AttachJoint(NativeJoint& j, NativeBody& b0, NativeBody& b1) {
	j->Attach(*b0, *b1);
}

void TosFys::SetJointHingeAnchor(NativeJoint& j, const vec3& pos) {
	j->SetHingeAnchor(pos);
}

void TosFys::SetJointHingeAxes(NativeJoint& j, const vec3& axis1, const vec3& axis2) {
	j->SetHingeAxes(axis1, axis2);
}

void TosFys::SetSuspensionERP(NativeJoint& j, float erp) {
	j->SetSuspensionERP(erp);
}

void TosFys::SetSuspensionCFM(NativeJoint& j, float cfm) {
	j->SetSuspensionCFM(cfm);
}

void TosFys::SetHingeRange(NativeJoint& j, float lo, float hi, int idx) {
	j->SetHingeRange(lo, hi, idx);
}

void TosFys::SetHingeVelocity(NativeJoint& j, float v, int idx) {
	j->SetHingeVelocity(v, idx);
}

void TosFys::SetMaxForce(NativeJoint& j, float v, int idx) {
	j->SetMaxForce(v, idx);
}

void TosFys::SetFudgeFactor(NativeJoint& j, float v) {
	j->SetFudgeFactor(v);
}

void TosFys::SetHingeAnchor(NativeJoint& j, const vec3& v) {
	j->SetHingeAnchor(v);
}

void TosFys::SetAxis(NativeJoint& j, const vec3& v) {
	j->SetAxis(v);
}

float TosFys::GetAngle(NativeJoint& j) {
	return j->GetAngle();
}

TosFys::NativeQuat TosFys::GetDefaultOrientation() {
	return quat(0, 1, 0, 0);
}


NAMESPACE_TOPSIDE_END
