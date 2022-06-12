// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHolograph_Vendors_h_
#define _IHolograph_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define HOLO_CLS_LIST(x) \
	HOLO_CLS(SinkDevice, x) \



#define HOLO_VNDR_LIST \
	HOLO_VNDR(HoloOpenHMD) \



#define HOLO_CLS(x, v) struct v##x;
#define HOLO_VNDR(x) HOLO_CLS_LIST(x)
HOLO_VNDR_LIST
#undef HOLO_VNDR
#undef HOLO_CLS



#if (defined flagOPENHMD && defined flagLINUX) || (defined flagOPENHMD && defined flagFREEBSD)
struct HoloOpenHMD {
	
	struct NativeSinkDevice {
		void* data;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

