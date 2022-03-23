// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 23.3.23 18:44:22

#ifndef _IPhysics_Vendors_h_
#define _IPhysics_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

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



struct FysTos {
	using NativeGeom = uint32;
	using NativeBody = uint32;
	using NativeWorld = uint32;
	using NativeSpace = uint32;
	using NativeJoint = uint32;
	using NativeMass = uint32;
	using NativeQuat = uint32;
	using NativeFeedback = uint32;
	using NativeJointGroup = uint32;
	using NativeThreading = uint32;
	using NativeThreadPool = uint32;
	using NativeContact = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct FysOde {
	using NativeGeom = uint32;
	using NativeBody = uint32;
	using NativeWorld = uint32;
	using NativeSpace = uint32;
	using NativeJoint = uint32;
	using NativeMass = uint32;
	using NativeQuat = uint32;
	using NativeFeedback = uint32;
	using NativeJointGroup = uint32;
	using NativeThreading = uint32;
	using NativeThreadPool = uint32;
	using NativeContact = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

