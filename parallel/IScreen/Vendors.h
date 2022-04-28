// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IScreen_Vendors_h_
#define _IScreen_Vendors_h_

#if (defined flagLINUX) || (defined flagFREEBSD)
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
#endif

#if (defined flagLINUX) || (defined flagFREEBSD)
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
#endif

#if defined flagOGL
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <GL/glx.h>
#endif

NAMESPACE_PARALLEL_BEGIN

#define SCR_CLS_LIST(x) \
	SCR_CLS(SinkDevice, x) \



#define SCR_VNDR_LIST \
	SCR_VNDR(ScrX11) \
	SCR_VNDR(ScrX11Sw) \
	SCR_VNDR(ScrX11Ogl) \



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

#if (defined flagLINUX) || (defined flagFREEBSD)
struct ScrX11Sw {
	
	struct NativeSinkDevice {
		::Window win;
		::Display* display;
		::XImage* fb;
		::Visual* visual;
		::GC gc;
		GfxAccelAtom<X11SwGfx> accel;
		ByteImage accel_buf;
		ByteImage accel_buf_tmp;
		DepthImage accel_zbuf;
		SoftFramebufferT<X11SwGfx> accel_fbo;
		::Atom atomWmDeleteWindow;
		::XSetWindowAttributes attr;
	};

	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if defined flagOGL
struct ScrX11Ogl {
	
	struct NativeSinkDevice {
		::Window win;
		::Display* display;
		::XVisualInfo* visual;
		::GLXContext gl_ctx;
		GfxAccelAtom<X11OglGfx> ogl;
		::Atom  atomWmDeleteWindow;
		::XSetWindowAttributes attr;
	};

	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

