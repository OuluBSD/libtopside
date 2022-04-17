#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Screen, Scr, S) {
	IfaceLib::Add(this);
	
	COLOR(112, 112, 112)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(IGraphics)
	LIBRARY("POSIX", X11)
	LIBRARY("POSIX & OGL", GLX)
	LIBRARY("POSIX & OGL", GL GLU GLEW glut)
	HAVE_RECV_FINALIZE
	HAVE_NEGOTIATE_FORMAT
	
	PKG_IFACE {
		//NATIVE_CLASS(SinkDevice)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(SinkDevice) {
			NATIVE_INHERIT(SinkDevice, dev)
			
		}
	}
	
	VENDOR(X11) {
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		VENDOR_INCLUDE("", X11/Xlib.h)
		VENDOR_INCLUDE("", X11/Xutil.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("win",			"::Window")
			.Add("display",		"::Display*")
			.Add("fb",			"::XImage*")
			.Add("visual",		"::Visual*")
			.Add("gc",			"::GC")
			;
		
	}
	
	VENDOR(X11Sw) {
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		VENDOR_INCLUDE("", X11/Xlib.h)
		VENDOR_INCLUDE("", X11/Xutil.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("win",					"::Window")
			.Add("display",				"::Display*")
			.Add("fb",					"::XImage*")
			.Add("visual",				"::Visual*")
			.Add("gc",					"::GC")
			.Add("accel",				"GfxAccelAtom<X11SwGfx>")
			.Add("accel_fb_data",		"Vector<byte>")
			.Add("accel_fb",			"ByteImage")
			.Add("accel_fb_ptr",		"ByteImage*")
			.Add("atomWmDeleteWindow",	"::Atom ")
			.Add("attr",				"::XSetWindowAttributes")
			;
		
	}
	
	VENDOR(X11Glx) {
		VENDOR_ENABLED_FLAG(OGL)
		VENDOR_INCLUDE("", X11/Xlib.h)
		VENDOR_INCLUDE("", X11/Xutil.h)
		VENDOR_INCLUDE("", GL/glx.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("win",					"::Window")
			.Add("display",				"::Display*")
			.Add("visual",				"::XVisualInfo*")
			.Add("gl_ctx",				"::GLXContext")
			.Add("ogl",					"GfxAccelAtom<X11OglGfx>")
			.Add("atomWmDeleteWindow",	"::Atom ")
			.Add("attr",				"::XSetWindowAttributes")
			;
		
	}
	
	
}


NAMESPACE_PLAN_END
