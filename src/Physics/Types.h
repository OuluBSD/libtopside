#ifndef _Physics_Types_h_
#define _Physics_Types_h_

NAMESPACE_TOPSIDE_BEGIN

#define FYS_CLS_LIST(f) \
	FYS_CLS(Node, f) \
	FYS_CLS(Object, f) \
	FYS_CLS(Joint, f) \
	FYS_CLS(Space, f) \
	FYS_CLS(World, f) \


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
	using World		= TosWorld;
	using System	= Ecs::TosSystem;
	using NativeWorld		= SoftPhys::World*;
	using NativeSpace		= SoftPhys::Space*;
	using NativeGeom		= SoftPhys::Geometry*;
	using NativeBody		= SoftPhys::Body*;
	using NativeMass		= float;
	using NativeQuat		= quat;
	using NativeJointGroup	= SoftPhys::JointGroup*;
	using NativeThreading	= SoftPhys::Threading*;
	using NativeThreadPool	= SoftPhys::ThreadPool*;
	using NativeJoint		= SoftPhys::Joint*;
	using NativeFeedback	= SoftPhys::Feedback*;
	
	typedef void (*NearCallback)(void *data, NativeGeom o1, NativeGeom o2);
	
	#include "Functions.inl"
	
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
	
	#include "Functions.inl"
	
	static const char* Id() {return "Ode";}
	
};
#endif


#define FYSTYPE_LIST \
	FYSTYPE(TosFys) \
	FYSTYPE(OdeFys)

#ifdef flagODE
#define FYS_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <TosFys>; \
	template struct x <OdeFys>;
#else
#define FYS_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <TosFys>;
#endif

NAMESPACE_TOPSIDE_END

#endif
