#ifndef _Physics_Types_h_
#define _Physics_Types_h_

NAMESPACE_TOPSIDE_BEGIN

#define FYS_CLS_LIST(f) \
	FYS_CLS(Node, f) \
	FYS_CLS(Object, f) \
	FYS_CLS(Joint, f) \
	FYS_CLS(Space, f)

#define FYS_ECS_CLS_LIST(f) \
	FYS_CLS(System, f)


#ifdef flagODE
	#define FYS_FYSSYS_LIST \
		FYS_SYS(Tos) \
		FYS_SYS(Ode)
		
	#define FYSTYPE_LIST \
		FYSTYPE(TosFys) \
		FYSTYPE(OdeFys)
	
	#define FYS_EXCPLICIT_INITIALIZE_CLASS(x) \
		template struct x <TosFys>; \
		template struct x <OdeFys>;
#else
	#define FYS_FYSSYS_LIST \
		FYS_SYS(Tos)
		
	#define FYSTYPE_LIST \
		FYSTYPE(TosFys)
	
	#define FYS_EXCPLICIT_INITIALIZE_CLASS(x) \
		template struct x <TosFys>;
#endif

#define FYS_CLS(x, f) struct f##x;
#define FYS_SYS(x) FYS_CLS_LIST(x)
FYS_FYSSYS_LIST
#undef FYS_SYS
namespace Ecs {
#define FYS_SYS(x) FYS_ECS_CLS_LIST(x)
FYS_FYSSYS_LIST
#undef FYS_SYS
}
#undef FYS_CLS


namespace FVar {
	
	
}


struct TosFys {
	using Node		= TosNode;
	using Object	= TosObject;
	using Joint		= TosJoint;
	using Space		= TosSpace;
	using System	= Ecs::TosSystem;
	
	using NativeGeom		= SoftPhys::Geometry;
	using NativeBody		= SoftPhys::Body;
	using NativeWorld		= SoftPhys::World;
	using NativeSpace		= SoftPhys::Space;
	using NativeJoint		= SoftPhys::Joint;
	using NativeMass		= SoftPhys::Mass;
	using NativeQuat		= quat;
	using NativeFeedback	= SoftPhys::Feedback;
	using NativeJointGroup	= SoftPhys::JointGroup;
	using NativeThreading	= SoftPhys::Threading;
	using NativeThreadPool	= SoftPhys::ThreadPool;
	using NativeContact		= SoftPhys::Contact;
	
	
	typedef void (*NearCallback)(void *data, NativeGeom& o1, NativeGeom& o2);
	
	static void InitializeLibrary();
	static void UninitializeLibrary();
	
	static void CreateWorld(NativeWorld& world);
	static void ClearWorld(NativeWorld& world);
	static void SetGravity(NativeWorld& world, const vec3& v);
	static void SetWorldCFM(NativeWorld& world, float f);
	static void SetMaxCorrectingVelocity(NativeWorld& world, float f);
	static void SetContactSurfaceLayer(NativeWorld& world, float f);
	static void SetAutoDisable(NativeWorld& world, bool b);
	static void SetStepIterations(NativeWorld& world, int i);
	static void SetAutoDisableSamples(NativeWorld& world, int i);
	
	static void CreateSpace(NativeSpace& space, NativeSpace* owner, bool is_root);
	static void ClearSpace(NativeSpace& space);
	static void Collide(NativeSpace& space, void* data);
	static int  Collide(NativeGeom& o1, NativeGeom& o2, int count, NativeContact* c, int ptr_pitch);
	static void Step(NativeWorld& world, float seconds);
	static void AttachContact(NativeWorld& w, NativeJointGroup& cg, NativeContact& c, float slip1, float slip2, float erp, float cfm);
	static void AddGeomToSpace(NativeSpace& space, NativeGeom& geom);
	static void RemoveGeomFromSpace(NativeSpace& space, NativeGeom& geom);
	
	static void CreateJointGroup(NativeJointGroup& g);
	static void ClearJointGroup(NativeJointGroup& g);
	static void DetachJointGroup(NativeJointGroup& g);
	
	static void CreateThreading(NativeThreading& t);
	static void CreateThreadPool(NativeThreadPool& p);
	static void AttachThreadPool(NativeThreading& t, NativeThreadPool& p);
	static void AttachThreading(NativeWorld& w, NativeThreading& t);
	static void DetachThreading(NativeWorld& w);
	static void DetachThreading(NativeThreading& t);
	static void ClearThreadPool(NativeThreadPool& p);
	static void ClearThreading(NativeThreading& t);
	
	static void CreateBody(NativeWorld& w, NativeBody& b);
	static void ClearBody(NativeBody& b);
	static vec3 GetBodyPosition(NativeBody& b);
	static void SetBodyRotationAxisAngle(NativeBody& b, float ax, float ay, float az, float angle);
	static void SetBodyMass(NativeBody& b, NativeMass& m);
	static void SetBodyPosition(NativeBody& b, float x, float y, float z);
	static void SetBodyQuaternion(NativeBody& b, const quat& q);
	static void SetBodyLinearVelocity(NativeBody& b, const vec3& v);
	static void SetBodyAngularVelocity(NativeBody& b, const vec3& v);
	
	static void ClearGeom(NativeGeom& g);
	static void SetGeomModelPlane(NativeGeom& g, NativeSpace& s, const vec4& plane=vec4(0,1,0,0));
	static void SetGeomModelSphere(NativeGeom& g, float radius);
	static void SetGeomModelBox(NativeGeom& g, float w, float h, float l);
	static void SetGeomPosition(NativeGeom& g, float x, float y, float z);
	static void SetGeomRotationAxisAngle(NativeGeom& g, float ax, float ay, float az, float angle);
	static void SetGeomBody(NativeGeom& g, NativeBody& b);
	static void ResetGeomRotation(NativeGeom& geom);
	static vec3 GetGeomPosition(NativeGeom& geom);
	static quat GetGeomQuaternion(NativeGeom& geom);
	static mat43 GetGeomRotationAxisAngle(NativeBody& body);
	
	static void CreateJointHinge2(NativeWorld& w, NativeJoint& j);
	static void AttachJoint(NativeJoint& j, NativeBody& b0, NativeBody& b1);
	static void GetDefaultOrientation(NativeQuat& q) {q[0] = 0; q[1] = 1; q[2] = 0; q[3] = 0;}
	static void SetJointFeedback(NativeJoint& j, NativeFeedback& fb);
	static void SetJointHingeAnchor(NativeJoint& j, const vec3& pos);
	static void SetJointHingeAxes(NativeJoint& j, const vec3& axis1, const vec3& axis2);
	static void SetSuspensionERP(NativeJoint& j, float erp);
	static void SetSuspensionCFM(NativeJoint& j, float cfm);
	static void SetHingeRange(NativeJoint& j, float lo, float hi, int idx=0);
	static void SetHingeVelocity(NativeJoint& j, float v, int idx=0);
	static void SetMaxForce(NativeJoint& j, float v, int idx=0);
	static void SetFudgeFactor(NativeJoint& j, float v);
	static void SetHingeAnchor(NativeJoint& j, const vec3& v);
	static void SetAxis(NativeJoint& j, const vec3& v);
	static float GetAngle(NativeJoint& j);
	
	
	// utility functions
	static void SetQuatFromAxisAngle(NativeQuat& q, const vec3& axis, float angle);
	static void SetMassFunctionSphere(NativeMass& mass, float density, float radius);
	static void SetMassFunctionBox(NativeMass& mass, float w, float h, float l);
	static void SetMassFunctionBox(NativeMass& mass, float density, float w, float h, float l);
	static void SetMass(NativeMass& mass, float kg);
	
	static String Id() {return "Tos";}
	
};

#ifdef flagODE
struct OdeFys {
	using Node		= OdeNode;
	using Object	= OdeObject;
	using Joint		= OdeJoint;
	using Space		= OdeSpace;
	using System	= Ecs::OdeSystem;
	
	using NativeGeom		= dGeomID;
	using NativeBody		= dBodyID;
	using NativeWorld		= dWorldID;
	using NativeSpace		= dSpaceID;
	using NativeJoint		= dJointID;
	using NativeMass		= dMass;
	using NativeQuat		= dQuaternion;
	using NativeFeedback	= dJointFeedback;
	using NativeJointGroup	= dJointGroupID;
	using NativeThreading	= dThreadingImplementationID;
	using NativeThreadPool	= dThreadingThreadPoolID;
	using NativeContact		= dContact;
	
	
	typedef void (*NearCallback)(void *data, NativeGeom o1, NativeGeom o2);
	
	static void InitializeLibrary();
	static void UninitializeLibrary();
	
	static void CreateWorld(NativeWorld& world);
	static void ClearWorld(NativeWorld& world);
	static void SetGravity(NativeWorld& world, const vec3& v);
	static void SetWorldCFM(NativeWorld& world, float f);
	static void SetMaxCorrectingVelocity(NativeWorld& world, float f);
	static void SetContactSurfaceLayer(NativeWorld& world, float f);
	static void SetAutoDisable(NativeWorld& world, bool b);
	static void SetStepIterations(NativeWorld& world, int i);
	static void SetAutoDisableSamples(NativeWorld& world, int i);
	
	static void CreateSpace(NativeSpace& space, NativeSpace* owner, bool is_root);
	static void ClearSpace(NativeSpace& space);
	static void Collide(NativeSpace& space, void* data);
	static int  Collide(NativeGeom& o1, NativeGeom& o2, int count, NativeContact* c, int ptr_pitch);
	static void Step(NativeWorld& world, float seconds);
	static void AttachContact(NativeWorld& w, NativeJointGroup& cg, NativeContact& c, float slip1, float slip2, float erp, float cfm);
	static void AddGeomToSpace(NativeSpace& space, NativeGeom& geom);
	static void RemoveGeomFromSpace(NativeSpace& space, NativeGeom& geom);
	
	static void CreateJointGroup(NativeJointGroup& g);
	static void ClearJointGroup(NativeJointGroup& g);
	static void DetachJointGroup(NativeJointGroup& g);
	
	static void CreateThreading(NativeThreading& t);
	static void CreateThreadPool(NativeThreadPool& p);
	static void AttachThreadPool(NativeThreading& t, NativeThreadPool& p);
	static void AttachThreading(NativeWorld& w, NativeThreading& t);
	static void DetachThreading(NativeWorld& w);
	static void DetachThreading(NativeThreading& t);
	static void ClearThreadPool(NativeThreadPool& p);
	static void ClearThreading(NativeThreading& t);
	
	static void CreateBody(NativeWorld& w, NativeBody& b);
	static void ClearBody(NativeBody& b);
	static vec3 GetBodyPosition(NativeBody& b);
	static void SetBodyRotationAxisAngle(NativeBody& b, float ax, float ay, float az, float angle);
	static void SetBodyMass(NativeBody& b, NativeMass& m);
	static void SetBodyPosition(NativeBody& b, float x, float y, float z);
	static void SetBodyQuaternion(NativeBody& b, const quat& q);
	static void SetBodyQuaternion(NativeBody& b, const NativeQuat& q);
	static void SetBodyLinearVelocity(NativeBody& b, const vec3& v);
	static void SetBodyAngularVelocity(NativeBody& b, const vec3& v);
	
	static void ClearGeom(NativeGeom& g);
	static void SetGeomModelPlane(NativeGeom& g, NativeSpace& s, const vec4& plane=vec4(0,1,0,0));
	static void SetGeomModelSphere(NativeGeom& g, float radius);
	static void SetGeomModelBox(NativeGeom& g, float w, float h, float l);
	static void SetGeomPosition(NativeGeom& g, float x, float y, float z);
	static void SetGeomRotationAxisAngle(NativeGeom& g, float ax, float ay, float az, float angle);
	static void SetGeomBody(NativeGeom& g, NativeBody& b);
	static void ResetGeomRotation(NativeGeom& geom);
	static vec3 GetGeomPosition(NativeGeom& geom);
	static quat GetGeomQuaternion(NativeGeom& geom);
	static mat43 GetGeomRotationAxisAngle(NativeBody& body);
	
	static void CreateJointHinge2(NativeWorld& w, NativeJoint& j);
	static void AttachJoint(NativeJoint& j, NativeBody& b0, NativeBody& b1);
	static void GetDefaultOrientation(NativeQuat& q) {q[0] = 0; q[1] = 1; q[2] = 0; q[3] = 0;}
	static void SetJointFeedback(NativeJoint& j, NativeFeedback& fb);
	static void SetJointHingeAnchor(NativeJoint& j, const vec3& pos);
	static void SetJointHingeAxes(NativeJoint& j, const vec3& axis1, const vec3& axis2);
	static void SetSuspensionERP(NativeJoint& j, float erp);
	static void SetSuspensionCFM(NativeJoint& j, float cfm);
	static void SetHingeRange(NativeJoint& j, float lo, float hi, int idx=0);
	static void SetHingeVelocity(NativeJoint& j, float v, int idx=0);
	static void SetMaxForce(NativeJoint& j, float v, int idx=0);
	static void SetFudgeFactor(NativeJoint& j, float v);
	static void SetHingeAnchor(NativeJoint& j, const vec3& v);
	static void SetAxis(NativeJoint& j, const vec3& v);
	static float GetAngle(NativeJoint& j);
	
	
	// utility functions
	static void SetQuatFromAxisAngle(NativeQuat& q, const vec3& axis, float angle);
	static void SetMassFunctionSphere(NativeMass& mass, float density, float radius);
	static void SetMassFunctionBox(NativeMass& mass, float w, float h, float l);
	static void SetMass(NativeMass& mass, float kg);
	static quat GetQuat(const NativeQuat& q);
	static void GetNativeQuat(const quat& q, NativeQuat& r);
	
	static String Id() {return "Ode";}
	
};
#endif



NAMESPACE_TOPSIDE_END

#endif
