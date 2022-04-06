// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 12:22:22

#ifndef _IScreen_Vendors_h_
#define _IScreen_Vendors_h_

#if (defined flagLINUX) || (defined flagFREEBSD)
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
#endif

NAMESPACE_PARALLEL_BEGIN

#define SCR_CLS_LIST(x) \
	SCR_CLS(SinkDevice, x) \



#define SCR_VNDR_LIST \
	SCR_VNDR(ScrX11) \



#define SCR_CLS(x, v) struct v##x;
#define SCR_VNDR(x) SCR_CLS_LIST(x)
SCR_VNDR_LIST
#undef SCR_VNDR
#undef SCR_CLS



#if (defined flagLINUX) || (defined flagFREEBSD)
struct ScrX11 {
	
	struct NativeSinkDevice {
		::Window win;
		::Display* display;
		::XImage* fb;
		::Visual* visual;
		::GC gc;
	};

	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

