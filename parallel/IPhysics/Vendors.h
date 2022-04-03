// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 11:11:55

#ifndef _IPhysics_Vendors_h_
#define _IPhysics_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define FYS_CLS_LIST(x) \
	FYS_CLS(Node, x) \
	FYS_CLS(Object, x) \
	FYS_CLS(Joint, x) \
	FYS_CLS(Space, x) \
	FYS_CLS(System, x) \



#define FYS_VNDR_LIST \
	FYS_VNDR(FysTos) \
	FYS_VNDR(FysOde) \



#define FYS_CLS(x, v) struct v##x;
#define FYS_VNDR(x) FYS_CLS_LIST(x)
FYS_VNDR_LIST
#undef FYS_VNDR
#undef FYS_CLS



#if 0
struct FysTos {
	using NativeGeom = void*;
	using NativeBody = void*;
	using NativeWorld = void*;
	using NativeSpace = void*;
	using NativeJoint = void*;
	using NativeMass = void*;
	using NativeQuat = void*;
	using NativeFeedback = void*;
	using NativeJointGroup = void*;
	using NativeThreading = void*;
	using NativeThreadPool = void*;
	using NativeContact = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct FysOde {
	using NativeGeom = void*;
	using NativeBody = void*;
	using NativeWorld = void*;
	using NativeSpace = void*;
	using NativeJoint = void*;
	using NativeMass = void*;
	using NativeQuat = void*;
	using NativeFeedback = void*;
	using NativeJointGroup = void*;
	using NativeThreading = void*;
	using NativeThreadPool = void*;
	using NativeContact = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

