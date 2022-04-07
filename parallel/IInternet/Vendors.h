// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.7 20:44:33

#ifndef _IInternet_Vendors_h_
#define _IInternet_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define NET_CLS_LIST(x) \
	NET_CLS(Socket, x) \



#define NET_VNDR_LIST \
	NET_VNDR(NetPosix) \
	NET_VNDR(NetWin32) \
	NET_VNDR(NetEnet) \
	NET_VNDR(NetNullSerial) \



#define NET_CLS(x, v) struct v##x;
#define NET_VNDR(x) NET_CLS_LIST(x)
NET_VNDR_LIST
#undef NET_VNDR
#undef NET_CLS



#if 0
struct NetPosix {
	using NativeSocket = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct NetWin32 {
	using NativeSocket = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct NetEnet {
	using NativeSocket = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if 0
struct NetNullSerial {
	using NativeSocket = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

