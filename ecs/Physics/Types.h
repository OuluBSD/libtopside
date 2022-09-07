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
#else
	#define FYS_FYSSYS_LIST \
		FYS_SYS(Tos)
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
	
	
	static const char* Id() {return "Tos";}
	
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
	
	typedef void (*NearCallback)(void *data, NativeGeom& o1, NativeGeom& o2);
	
	static void InitializeLibrary();
	static void UninitializeLibrary();
	
	static void CreateWorld(NativeWorld& world);
	static void ClearWorld(NativeWorld& world);
	static void SetGravity(NativeWorld& world, float f);
	static void SetWorldCFM(NativeWorld& world, float f);
	static void SetMaxCorrectingVelocity(NativeWorld& world, float f);
	static void SetContactSurfaceLayer(NativeWorld& world, float f);
	static void SetAutoDisable(NativeWorld& world, bool b);
	static void SetStepIterations(NativeWorld& world, int i);
	static void SetAutoDisableSamples(NativeWorld& world, int i);
	
	static void CreateSpace(NativeSpace& space, bool is_root);
	static void ClearSpace(NativeSpace& space);
	static void Collide(NativeSpace& space, void* data, NearCallback cb);
	static void Step(NativeSpace& space, float seconds);
	
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
	
	static NativeBody CreateBody(NativeWorld w);
	static vec3 GetBodyPosition(NativeBody b);
	static void SetBodyPosition(NativeBody b, float x, float y, float z);
	
	static void SetGeomPosition(NativeGeom g, float x, float y, float z);
	static void SetGeomRotationAxisAngle(float ax, float ay, float az, float angle);
	static void ResetGeomRotation(NativeGeom geom);
	
	static NativeJoint CreateJointHinge2(NativeWorld w);
	static void AttachJoint(NativeJoint& j, NativeBody& b0, NativeBody& b1);
	static NativeQuat GetDefaultOrientation() {return dQuaternion {0,1,0,0};}
	static void SetJointFeedback(NativeJoint j, NativeFeedback& fb);
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
	
	static const char* Id() {return "Ode";}
	
};
#endif


#define FYSTYPE_LIST \
	FYSTYPE(TosFys) \
	FYSTYPE(OdeFys)

#define FYS_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <TosFys>; \
	template struct x <OdeFys>;


NAMESPACE_TOPSIDE_END

#endif
