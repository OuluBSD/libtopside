// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IPhysics_Vendors_h_
#define _IPhysics_Vendors_h

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



VENDORSSZZ
struct FysTos {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct FysOde {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

