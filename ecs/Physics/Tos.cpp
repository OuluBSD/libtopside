#include "Physics.h"

NAMESPACE_TOPSIDE_BEGIN


void TosFys::InitializeLibrary() {
	// pass
}

void TosFys::UninitializeLibrary() {
	// pass
}


void TosFys::CreateWorld(SoftPhys::World& world) {
	world.Create();
}

void TosFys::ClearWorld(SoftPhys::World& world) {
	world.Clear();
}

void TosFys::SetGravity(SoftPhys::World& world, const vec3& v) {
	world.SetGravity(v);
}

void TosFys::SetWorldCFM(SoftPhys::World& world, float f) {
	world.SetMaxCorrectingVelocity(f);
}

void TosFys::SetMaxCorrectingVelocity(SoftPhys::World& world, float f) {
	world.SetMaxCorrectingVelocity(f);
}

void TosFys::SetContactSurfaceLayer(SoftPhys::World& world, float f) {
	world.SetContactSurfaceLayer(f);
}

void TosFys::SetAutoDisable(SoftPhys::World& world, bool b) {
	world.SetAutoDisable(b);
}

void TosFys::SetStepIterations(SoftPhys::World& world, int i) {
	world.SetStepIterations(i);
}

void TosFys::SetAutoDisableSamples(SoftPhys::World& world, int i) {
	world.SetAutoDisableSamples(i);
}


void TosFys::CreateSpace(SoftPhys::Space& space, SoftPhys::Space* owner, bool is_root) {
	space.Create();
	ASSERT((owner == NULL) == is_root);
	space.SetOwner(owner);
}

void TosFys::ClearSpace(SoftPhys::Space& space) {
	space.Clear();
}

void TosFys::Collide(SoftPhys::Space& space, void* data) {
	NearCallback cb = &System::StaticNearCallbackR;
	space.Collide(data, cb);
}

int TosFys::Collide(SoftPhys::Geometry& o1, SoftPhys::Geometry& o2, int count, SoftPhys::Contact* c, int ptr_pitch) {
	return SoftPhys::Collide(o1, o2, count, c, ptr_pitch);
}

void TosFys::Step(SoftPhys::World& world, float seconds) {
	world.Step(seconds);
}

void TosFys::AttachContact(SoftPhys::World& w, SoftPhys::JointGroup& cg, SoftPhys::Contact& c, float slip1, float slip2, float erp, float cfm) {
	TODO
}

void TosFys::AddGeomToSpace(SoftPhys::Space& space, SoftPhys::Geometry& geom) {
	space.Add(geom);
}

void TosFys::RemoveGeomFromSpace(SoftPhys::Space& space, SoftPhys::Geometry& geom) {
	space.Remove(geom);
}


void TosFys::CreateJointGroup(SoftPhys::JointGroup& g) {
	g.Create();
}

void TosFys::ClearJointGroup(SoftPhys::JointGroup& g) {
	g.Clear();
}

void TosFys::DetachJointGroup(SoftPhys::JointGroup& g) {
	g.Detach();
}


void TosFys::CreateThreading(SoftPhys::Threading& t) {
	t.Create();
}

void TosFys::CreateThreadPool(SoftPhys::ThreadPool& p) {
	p.Create();
}

void TosFys::AttachThreadPool(SoftPhys::Threading& t, SoftPhys::ThreadPool& p) {
	t.Add(p);
}

void TosFys::AttachThreading(SoftPhys::World& w, SoftPhys::Threading& t) {
	w.AttachThreading(t);
}

void TosFys::DetachThreading(SoftPhys::World& w) {
	w.DetachThreading();
}

void TosFys::DetachThreading(SoftPhys::Threading& t) {
	t.Detach();
}

void TosFys::ClearThreadPool(SoftPhys::ThreadPool& p) {
	p.Clear();
}

void TosFys::ClearThreading(SoftPhys::Threading& t) {
	t.Clear();
}


void TosFys::CreateBody(SoftPhys::World& w, SoftPhys::Body& b) {
	b.Create();
	w.CreateBody(b);
}

void TosFys::ClearBody(SoftPhys::Body& b) {
	b.Clear();
}

vec3 TosFys::GetBodyPosition(SoftPhys::Body& b) {
	b.GetPosition();
}

void TosFys::SetBodyRotationAxisAngle(NativeBody& b, float ax, float ay, float az, float angle) {
	b.SetRotation(vec3(ax, ay, az), angle);
}

void TosFys::SetBodyMass(SoftPhys::Body& b, SoftPhys::Mass& m) {
	b.SetMass(m);
}

void TosFys::SetBodyPosition(SoftPhys::Body& b, float x, float y, float z) {
	b.SetPosition(vec3(x,y,z));
}

void TosFys::SetBodyQuaternion(SoftPhys::Body& b, const quat& q) {
	b.SetQuaternion(q);
}

void TosFys::SetBodyLinearVelocity(SoftPhys::Body& b, const vec3& v) {
	b.SetLinearVelocity(v);
}

void TosFys::SetBodyAngularVelocity(SoftPhys::Body& b, const vec3& v) {
	b.SetAngularVelocity(v);
}


void TosFys::ClearGeom(SoftPhys::Geometry& g) {
	g.Clear();
}

void TosFys::SetGeomModelPlane(SoftPhys::Geometry& g, SoftPhys::Space& s, const vec4& plane) {
	g.SetModelPlane(s, plane);
}

void TosFys::SetGeomModelSphere(SoftPhys::Geometry& g, float radius) {
	g.SetModelSphere(radius);
}

void TosFys::SetGeomModelBox(SoftPhys::Geometry& g, float w, float h, float l) {
	g.SetModelBox(vec3(w,h,l));
}

void TosFys::SetGeomPosition(SoftPhys::Geometry& g, float x, float y, float z) {
	g.SetPosition(vec3(x,y,z));
}

void TosFys::SetGeomRotationAxisAngle(NativeGeom& g, float ax, float ay, float az, float angle) {
	g.SetRotation(vec3(ax, ay, az), angle);
}

void TosFys::SetGeomBody(SoftPhys::Geometry& g, SoftPhys::Body& b) {
	g.SetGeomBody(b);
}

void TosFys::ResetGeomRotation(SoftPhys::Geometry& g) {
	g.ResetRotation();
}

vec3 TosFys::GetGeomPosition(SoftPhys::Geometry& g) {
	return g.GetPosition();
}

quat TosFys::GetGeomQuaternion(SoftPhys::Geometry& g) {
	return g.GetQuaternion();
}

mat43 GetGeomRotationAxisAngle(SoftPhys::Body& b) {
	return b.GetRotationAxisAngle();
}

void TosFys::CreateJointHinge2(SoftPhys::World& w, SoftPhys::Joint& j) {
	ASSERT(j);
	w.CreateJoint(j);
}

void TosFys::AttachJoint(SoftPhys::Joint& j, SoftPhys::Body& b0, SoftPhys::Body& b1) {
	j.Attach(b0, b1);
}


void TosFys::SetJointFeedback(SoftPhys::Joint& j, SoftPhys::Feedback& fb) {
	j.SetFeedback(fb);
}

void TosFys::SetJointHingeAnchor(SoftPhys::Joint& j, const vec3& pos) {
	j.SetHingeAnchor(pos);
}

void TosFys::SetJointHingeAxes(SoftPhys::Joint& j, const vec3& axis1, const vec3& axis2) {
	j.SetHingeAxes(axis1, axis2);
}

void TosFys::SetSuspensionERP(SoftPhys::Joint& j, float erp) {
	j.SetSuspensionERP(erp);
}

void TosFys::SetSuspensionCFM(SoftPhys::Joint& j, float cfm) {
	j.SetSuspensionCFM(cfm);
}

void TosFys::SetHingeRange(SoftPhys::Joint& j, float lo, float hi, int idx) {
	j.SetHingeRange(lo, hi, idx);
}

void TosFys::SetHingeVelocity(SoftPhys::Joint& j, float v, int idx) {
	j.SetHingeVelocity(v, idx);
}

void TosFys::SetMaxForce(SoftPhys::Joint& j, float v, int idx) {
	j.SetMaxForce(v, idx);
}

void TosFys::SetFudgeFactor(SoftPhys::Joint& j, float v) {
	j.SetFudgeFactor(v);
}

void TosFys::SetHingeAnchor(SoftPhys::Joint& j, const vec3& v) {
	j.SetHingeAnchor(v);
}

void TosFys::SetAxis(SoftPhys::Joint& j, const vec3& v) {
	j.SetAxis(v);
}

float TosFys::GetAngle(SoftPhys::Joint& j) {
	return j.GetAngle();
}



// utility functions
void TosFys::SetQuatFromAxisAngle(quat& q, const vec3& axis, float angle) {
	float ax = axis[0];
	float ay = axis[1];
	float az = axis[2];
	float l = ax*ax + ay*ay + az*az;
	if (l > 0.0f) {
		angle *= 0.5f;
		l = FastSin(angle) * (1.0f / FastSqrt(l));
		q[0] = ax*l;
		q[1] = ay*l;
		q[2] = az*l;
		q[3] = FastCos(angle);
	}
	else {
		q[0] = 0;
		q[1] = 0;
		q[2] = 0;
		q[3] = 1;
	}
}

void TosFys::SetMassFunctionSphere(SoftPhys::Mass& mass, float density, float radius) {
	mass.SetFunctionSphere(density, radius);
}

void TosFys::SetMassFunctionBox(SoftPhys::Mass& mass, float w, float h, float l) {
	mass.SetFunctionBox(vec3(w,h,l));
}

void TosFys::SetMassFunctionBox(SoftPhys::Mass& mass, float density, float w, float h, float l) {
	mass.SetFunctionBox(vec3(w,h,l), density);
}

void TosFys::SetMass(SoftPhys::Mass& mass, float kg) {
	mass.SetMass(kg);
}


NAMESPACE_TOPSIDE_END
