// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IEvents_Vendors_h_
#define _IEvents_Vendors_h

NAMESPACE_TOPSIDE_BEGIN

#define EV_CLS_LIST(x) \
	EV_CLS(Events, x) \



#define EV_VNDR_LIST \
	EV_VNDR(EvSdl) \
	EV_VNDR(EvGlfw) \
	EV_VNDR(EvX11) \
	EV_VNDR(EvWin32) \



#define EV_CLS(x, v) struct v##x;
#define EV_VNDR(x) EV_CLS_LIST(x)
EV_VNDR_LIST
#undef EV_VNDR
#undef EV_CLS



VENDORSSZZ
struct EvSdl {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct EvGlfw {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct EvX11 {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct EvWin32 {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

