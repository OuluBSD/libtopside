// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 25.3.25 19:11:33

#ifndef _IVirtualMachine_Vendors_h_
#define _IVirtualMachine_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define VM_CLS_LIST(x) \
	VM_CLS(VirtualMachine, x) \
	VM_CLS(Thread, x) \



#define VM_VNDR_LIST \
	VM_VNDR(VmTos) \



#define VM_CLS(x, v) struct v##x;
#define VM_VNDR(x) VM_CLS_LIST(x)
VM_VNDR_LIST
#undef VM_VNDR
#undef VM_CLS



struct VmTos {
	using NativeVirtualMachine = uint32;
	using NativeThread = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

