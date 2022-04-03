// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 22:44:00

#ifndef _IScript_Vendors_h_
#define _IScript_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

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



#if 0
struct ScrEsc {
	using NativeRunner = void*;
	using NativeThread = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct ScrPython {
	using NativeRunner = void*;
	using NativeThread = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct ScrDuktape {
	using NativeRunner = void*;
	using NativeThread = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

