// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IScript_Vendors_h_
#define _IScript_Vendors_h

NAMESPACE_TOPSIDE_BEGIN

#define SCR_CLS_LIST(x) \
	SCR_CLS(Runner, x) \
	SCR_CLS(Thread, x) \



#define SCR_VNDR_LIST \
	SCR_VNDR(ScrEsc) \
	SCR_VNDR(ScrPython) \
	SCR_VNDR(ScrDuktape) \



#define SCR_CLS(x, v) struct v##x;
#define SCR_VNDR(x) SCR_CLS_LIST(x)
SCR_VNDR_LIST
#undef SCR_VNDR
#undef SCR_CLS



struct ScrEsc {
	using NativeRunner = uint32;
	using NativeThread = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct ScrPython {
	using NativeRunner = uint32;
	using NativeThread = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct ScrDuktape {
	using NativeRunner = uint32;
	using NativeThread = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

