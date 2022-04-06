// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.7 0:44:33

#ifndef _IEvent_Vendors_h_
#define _IEvent_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define EV_CLS_LIST(x) \
	EV_CLS(SourceDevice, x) \



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



#if 0
struct EvSdl {
	using NativeContext = void*;
	using NativeSourceDevice = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct EvGlfw {
	using NativeContext = void*;
	using NativeSourceDevice = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct EvX11 {
	using NativeContext = void*;
	using NativeSourceDevice = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct EvWin32 {
	using NativeContext = void*;
	using NativeSourceDevice = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

