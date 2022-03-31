// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

#ifndef _IVirtualMachine_Vendors_h_
#define _IVirtualMachine_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

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



#if 0
struct VmTos {
	using NativeVirtualMachine = void*;
	using NativeThread = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

