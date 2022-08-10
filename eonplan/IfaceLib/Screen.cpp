#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Screen, Scr, S) {
	IfaceLib::Add(this);
	
	COLOR(112, 112, 112)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(IGraphics)
	LIBRARY("POSIX", X11 Xrandr Xxf86vm)
	LIBRARY("POSIX & OGL", GLX)
	LIBRARY("POSIX & OGL", GL GLU GLEW glut)
	HAVE_RECV_FINALIZE
	HAVE_NEGOTIATE_FORMAT
	HAVE_IS_READY
	
	PKG_IFACE {
		//NATIVE_CLASS(SinkDevice)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(SinkDevice) {
			NATIVE_INHERIT(SinkDevice, dev)
			
		}
		CLASS(EventsBase) {
			NATIVE_INHERIT(EventsBase, ev)
			
		}
		CLASS(Context) {
			NATIVE_INHERIT(Context, ctx)
			
		}
	}
	
	VENDOR(X11) {
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		//VENDOR_INCLUDE("", X11/Xlib.h)
		//VENDOR_INCLUDE("", X11/Xutil.h)
		//VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeContext")
			.Add("win",					"::Window")
			.Add("display",				"::Display*")
			.Add("fb",					"::XImage*")
			.Add("visual",				"::Visual*")
			.Add("gc",					"::GC")
			.Add("visual_info",			"::XVisualInfo*")
			.Add("atomWmDeleteWindow",	"::Atom ")
			.Add("attr",				"::XSetWindowAttributes")
			;
		
		v->AddStruct("NativeSinkDevice")
			.Add("ctx",					"NativeContext*")
			;
		
		v->AddStruct("NativeEventsBase")
			.Add("ctx",				"NativeContext*")
			.Add("time",			"int")
			.Add("seq",				"dword")
			.Add("ev",				"UPP::CtrlEvent")
			.Add("sz",				"Size")
			.Add("ev_sendable",		"bool")
			.Add("is_lalt",			"bool")
			.Add("is_ralt",			"bool")
			.Add("is_lshift",		"bool")
			.Add("is_rshift",		"bool")
			.Add("is_lctrl",		"bool")
			.Add("is_rctrl",		"bool")
			.Add("prev_mouse_pt",	"Point")
			.Add("xev",				"::XEvent")
			;
		
	}
	
	VENDOR(X11Sw) {
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		//VENDOR_INCLUDE("", X11/Xlib.h)
		//VENDOR_INCLUDE("", X11/Xutil.h)
		//VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("ctx",					"ScrX11::NativeContext*")
			.Add("accel",				"GfxAccelAtom<X11SwGfx>")
			.Add("accel_buf",			"ByteImage")
			.Add("accel_buf_tmp",		"ByteImage")
			.Add("accel_zbuf",			"DepthImage")
			.Add("accel_fbo",			"SoftFramebuffer")
			;
		
		v->AddStruct("NativeContext");
		v->AddStruct("NativeEventsBase");
		
	}
	
	VENDOR(X11Ogl) {
		VENDOR_ENABLED_FLAG(OGL)
		//VENDOR_INCLUDE("", X11/Xlib.h)
		//VENDOR_INCLUDE("", X11/Xutil.h)
		//VENDOR_INCLUDE("", GL/glx.h)
		//VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("ctx",					"ScrX11::NativeContext*")
			.Add("gl_ctx",				"::GLXContext")
			.Add("ogl",					"GfxAccelAtom<X11OglGfx>")
			;
		
		v->AddStruct("NativeContext");
		v->AddStruct("NativeEventsBase");
		
	}
	
	
}


NAMESPACE_PLAN_END
