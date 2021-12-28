#include "Physics.h"

#ifdef flagODE

NAMESPACE_TOPSIDE_BEGIN


void OdeFys::InitializeLibrary() {
	dInitODE2(0);
	dAllocateODEDataForThread(dAllocateMaskAll);
}

void OdeFys::UninitializeLibrary() {
	dCloseODE();
}

void OdeFys::CreateWorld(NativeWorld& world) {
	world = dWorldCreate();
}

void OdeFys::ClearWorld(NativeWorld& world) {
	dWorldDestroy(world);
}

void OdeFys::SetGravity(NativeWorld& world, const vec3& v) {
	dWorldSetGravity(world, v[0], v[1], v[2]);
}

void OdeFys::SetWorldCFM(NativeWorld& world, float f) {
	dWorldSetCFM(world, f);
}

void OdeFys::SetMaxCorrectingVelocity(NativeWorld& world, float f) {
	dWorldSetContactMaxCorrectingVel(world, f);
}

void OdeFys::SetContactSurfaceLayer(NativeWorld& world, float f) {
	dWorldSetContactSurfaceLayer(world, f);
}

void OdeFys::SetAutoDisable(NativeWorld& world, bool b) {
	dWorldSetAutoDisableFlag(world, b);
}

void OdeFys::SetStepIterations(NativeWorld& world, int i) {
	dWorldSetQuickStepNumIterations(world, i);
}

void OdeFys::SetAutoDisableSamples(NativeWorld& world, int i) {
	dWorldSetAutoDisableAverageSamplesCount(world, i);
}

void OdeFys::CreateSpace(NativeSpace& space, NativeSpace* owner, bool is_root) {
	if (is_root) {
		space = dHashSpaceCreate(0);
	} else {
		ASSERT(owner);
		space = dSimpleSpaceCreate(*owner);
		dSpaceSetCleanup(space, 0);
	}
}

void OdeFys::ClearSpace(NativeSpace& space) {
	dSpaceDestroy(space);
}

void OdeFys::Collide(NativeSpace& space, void* data, NearCallback cb) {
	dSpaceCollide(space, data, cb);
}

void OdeFys::Step(NativeWorld& world, float seconds) {
	dWorldStep(world, seconds);
}

void OdeFys::CreateJointGroup(NativeJointGroup& g) {
	g = dJointGroupCreate(0);
}

void OdeFys::ClearJointGroup(NativeJointGroup& g) {
	dJointGroupDestroy(g);
}

void OdeFys::DetachJointGroup(NativeJointGroup& g) {
	dJointGroupEmpty(g);
}

void OdeFys::CreateThreading(NativeThreading& t) {
	t = dThreadingAllocateMultiThreadedImplementation();
}

void OdeFys::CreateThreadPool(NativeThreadPool& p) {
	p = dThreadingAllocateThreadPool(4, 0, dAllocateFlagBasicData, NULL);
}

void OdeFys::AttachThreadPool(NativeThreading& t, NativeThreadPool& p) {
	dThreadingThreadPoolServeMultiThreadedImplementation(p, t);
}

void OdeFys::AttachThreading(NativeWorld& w, NativeThreading& t) {
	// dWorldSetStepIslandsProcessingMaxThreadCount(world, 1);
	dWorldSetStepThreadingImplementation(w, dThreadingImplementationGetFunctions(t), t);
	dAllocateODEDataForThread(dAllocateMaskAll);
}

void OdeFys::DetachThreading(NativeThreading& t) {
	dThreadingImplementationShutdownProcessing(t);
}

void OdeFys::DetachThreading(NativeWorld& w) {
	dWorldSetStepThreadingImplementation(w, NULL, NULL);
}

void OdeFys::ClearThreadPool(NativeThreadPool& p) {
	dThreadingFreeThreadPool(p);
}

void OdeFys::ClearThreading(NativeThreading& t) {
	dThreadingFreeImplementation(t);
}

void OdeFys::CreateBody(NativeWorld& w, NativeBody& b) {
	b = dBodyCreate(w);
}

vec3 OdeFys::GetBodyPosition(NativeBody& b) {
	const dReal* r = dBodyGetPosition(b);
	if (r)
		return vec3(r[0], r[1], r[2]);
	return vec3(0,0,0);
}

void OdeFys::SetBodyPosition(NativeBody& body, float x, float y, float z) {
	dBodySetPosition(body, x, y, z);
}

void OdeFys::SetBodyQuaternion(NativeBody& b, const quat& q) {
	dQuaternion Q {q[0], q[1], q[2], q[3]};
	dBodySetQuaternion(b, Q);
}

void OdeFys::SetBodyLinearVelocity(NativeBody& b, const vec3& v) {
	dBodySetLinearVel(b, v[0], v[1], v[2]);
}

void OdeFys::SetBodyAngularVelocity(NativeBody& b, const vec3& v) {
	dBodySetAngularVel(b, v[0], v[1], v[2]);
}

void OdeFys::SetGeomModelPlane(NativeGeom& g, NativeSpace& s, float a, float b, float c, float d) {
	g = dCreatePlane(s, a, b, c, d);
}

void OdeFys::SetGeomModelSphere(NativeGeom& g, float radius) {
	g = dCreateSphere(0, radius);
}

void OdeFys::SetGeomModelBox(NativeGeom& g, float w, float h, float l) {
	g = dCreateBox(0, w, h, l);
}

void OdeFys::SetGeomPosition(NativeGeom& geom, float x, float y, float z) {
	dGeomSetPosition(geom, x, y, z);
}

void OdeFys::ResetGeomRotation(NativeGeom& geom) {
	dMatrix3 R;
	dRSetIdentity(R);
	dGeomSetRotation(geom, R);
}

mat43 OdeFys::GetGeomRotationAxisAngle(NativeBody& body) {
	const dReal* r = dBodyGetRotation(body);
	mat43 m;
	for(int i = 0; i < 12; i++)
		m.data[i] = r[i];
	return m;
}

void OdeFys::SetGeomRotationAxisAngle(NativeBody& body, float ax, float ay, float az, float angle) {
	dMatrix3 R;
	dRFromAxisAndAngle(R, ax, ay, az, angle);
	dBodySetRotation(body, R);
}

void OdeFys::CreateJointHinge2(NativeWorld& w, NativeJoint& j) {
	j = dJointCreateHinge2(w, 0);
}

void OdeFys::SetJointFeedback(NativeJoint& j, NativeFeedback& fb) {
	dJointSetFeedback(j, &fb);
}

void OdeFys::AttachJoint(NativeJoint& j, NativeBody& b0, NativeBody& b1) {
	dJointAttach(j, b0, b1);
}

void OdeFys::SetJointHingeAnchor(NativeJoint& j, const vec3& pos) {
	dJointSetHinge2Anchor(j, pos[0], pos[1], pos[2]);
}

void OdeFys::SetJointHingeAxes(NativeJoint& j, const vec3& axis1, const vec3& axis2) {
	//dJointSetHinge2Axes(j, axis1, axis2);
	dJointSetHinge2Axis1(j, axis1[0], axis1[1], axis1[2]);
	dJointSetHinge2Axis2(j, axis2[0], axis2[1], axis2[2]);
}

void OdeFys::SetSuspensionERP(NativeJoint& j, float erp) {
	dJointSetHinge2Param(j, dParamSuspensionERP, erp);
}

void OdeFys::SetSuspensionCFM(NativeJoint& j, float cfm) {
	dJointSetHinge2Param(j, dParamSuspensionCFM, cfm);
}

void OdeFys::SetHingeRange(NativeJoint& j, float lo, float hi, int idx) {
	ASSERT(idx >= 0 && idx < 4);
	switch (idx) {
		case 0:
			dJointSetHinge2Param(j, dParamLoStop, lo);
			dJointSetHinge2Param(j, dParamHiStop, hi);
			break;
		case 1:
			dJointSetHinge2Param(j, dParamLoStop1, lo);
			dJointSetHinge2Param(j, dParamHiStop1, hi);
			break;
		case 2:
			dJointSetHinge2Param(j, dParamLoStop2, lo);
			dJointSetHinge2Param(j, dParamHiStop2, hi);
			break;
		case 3:
			dJointSetHinge2Param(j, dParamLoStop3, lo);
			dJointSetHinge2Param(j, dParamHiStop3, hi);
			break;
		default: break;
	}
}

void OdeFys::SetHingeVelocity(NativeJoint& j, float v, int idx) {
	ASSERT(idx >= 0 && idx < 4);
	switch (idx) {
		case 0:
			dJointSetHinge2Param(j, dParamVel, v);
			break;
		case 1:
			dJointSetHinge2Param(j, dParamVel1, v);
			break;
		case 2:
			dJointSetHinge2Param(j, dParamVel2, v);
			break;
		case 3:
			dJointSetHinge2Param(j, dParamVel3, v);
			break;
		default: break;
	}
}

void OdeFys::SetMaxForce(NativeJoint& j, float v, int idx) {
	ASSERT(idx >= 0 && idx < 4);
	switch (idx) {
		case 0:
			dJointSetHinge2Param(j, dParamFMax, v);
			break;
		case 1:
			dJointSetHinge2Param(j, dParamFMax1, v);
			break;
		case 2:
			dJointSetHinge2Param(j, dParamFMax2, v);
			break;
		case 3:
			dJointSetHinge2Param(j, dParamFMax3, v);
			break;
		default: break;
	}
}

void OdeFys::SetFudgeFactor(NativeJoint& j, float v) {
	dJointSetHinge2Param(j, dParamFudgeFactor, v);
}

void OdeFys::SetHingeAnchor(NativeJoint& j, const vec3& v) {
	dJointSetHingeAnchor(j, v[0], v[1], v[2]);
}

void OdeFys::SetAxis(NativeJoint& j, const vec3& v) {
	dJointSetHingeAxis(j, v[0], v[1], v[2]);
}

float OdeFys::GetAngle(NativeJoint& j) {
	return dJointGetHinge2Angle1(j);
}

void OdeFys::SetQuatFromAxisAngle(NativeQuat& q, const vec3& axis, float angle) {
	dQFromAxisAndAngle(q, axis[0], axis[1], axis[2], angle);
}

void OdeFys::SetMassFunctionSphere(NativeMass& mass, float density, float radius) {
	dMassSetSphere(&mass, density, radius);
}

void OdeFys::SetMassFunctionBox(NativeMass& mass, float w, float h, float l) {
	dMassSetBox(&mass, 1, w, h, l);
}

void OdeFys::SetMass(NativeMass& mass, float kg) {
	dMassAdjust(&mass, kg);
}


NAMESPACE_TOPSIDE_END

#endif
