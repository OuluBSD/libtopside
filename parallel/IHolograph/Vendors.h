// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHolograph_Vendors_h_
#define _IHolograph_Vendors_h_

#if (defined flagOPENHMD && defined flagLINUX) || (defined flagOPENHMD && defined flagFREEBSD)
	#include <openhmd.h>
#endif

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
		ohmd_context* ctx;
		ohmd_device_settings* settings;
		const char* fragment;
		const char* vertex;
		ohmd_device* hmd;
		Size screen_sz;
		mat4 l_proj;
		mat4 l_view;
		mat4 r_proj;
		mat4 r_view;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

