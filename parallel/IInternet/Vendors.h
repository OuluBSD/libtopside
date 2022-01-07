// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IInternet_Vendors_h_
#define _IInternet_Vendors_h

NAMESPACE_TOPSIDE_BEGIN

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



VENDORSSZZ
struct NetPosix {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct NetWin32 {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct NetEnet {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct NetNullSerial {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

