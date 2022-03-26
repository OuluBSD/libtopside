// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 26.3.26 14:33:33

#ifndef _IEvents_Vendors_h_
#define _IEvents_Vendors_h_

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



struct EvSdl {
	using NativeContext = uint32;
	using NativeEvents = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct EvGlfw {
	using NativeContext = uint32;
	using NativeEvents = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct EvX11 {
	using NativeContext = uint32;
	using NativeEvents = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct EvWin32 {
	using NativeContext = uint32;
	using NativeEvents = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

