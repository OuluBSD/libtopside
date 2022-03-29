// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

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



struct NetPosix {
	using NativeSocket = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct NetWin32 {
	using NativeSocket = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct NetEnet {
	using NativeSocket = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct NetNullSerial {
	using NativeSocket = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_PARALLEL_END


#endif

