// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IScreen_Vendors_h_
#define _IScreen_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define SCR_CLS_LIST(x) \
	SCR_CLS(SinkDevice, x) \
	SCR_CLS(EventsBase, x) \
	SCR_CLS(Context, x) \



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
	
	struct NativeContext {
		::Window win;
		::Display* display;
		::XImage* fb;
		::Visual* visual;
		::GC gc;
		::XVisualInfo* visual_info;
		::Atom  atomWmDeleteWindow;
		::XSetWindowAttributes attr;
	};
	
	struct NativeSinkDevice {
		NativeContext* ctx;
	};
	
	struct NativeEventsBase {
		NativeContext* ctx;
		int time;
		dword seq;
		UPP::CtrlEvent ev;
		Size sz;
		bool ev_sendable;
		bool is_lalt;
		bool is_ralt;
		bool is_lshift;
		bool is_rshift;
		bool is_lctrl;
		bool is_rctrl;
		Point prev_mouse_pt;
		::XEvent xev;
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
		ScrX11::NativeContext* ctx;
		GfxAccelAtom<X11SwGfx> accel;
		ByteImage accel_buf;
		ByteImage accel_buf_tmp;
		DepthImage accel_zbuf;
		SoftFramebufferT<X11SwGfx> accel_fbo;
	};
	
	struct NativeContext {
	};
	
	struct NativeEventsBase {
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
		ScrX11::NativeContext* ctx;
		::GLXContext gl_ctx;
		GfxAccelAtom<X11OglGfx> ogl;
	};
	
	struct NativeContext {
	};
	
	struct NativeEventsBase {
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

