#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN


PKG(Holograph, Holo, H) {
	IfaceLib::Add(this);
	
	COLOR(85, 42, 150)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(IGraphics)
	/*LIBRARY("POSIX", X11)
	LIBRARY("POSIX & OGL", GLX)
	LIBRARY("POSIX & OGL", GL GLU GLEW glut)*/
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
	
	VENDOR(OpenHMD) {
		VENDOR_ENABLED_FLAG2(OPENHMD, LINUX)
		VENDOR_ENABLED_FLAG2(OPENHMD, FREEBSD)
		//VENDOR_INCLUDE("", X11/Xlib.h)
		//VENDOR_INCLUDE("", X11/Xutil.h)
		//VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("data",		"void*")
			;
		
	}
	
}


NAMESPACE_PLAN_END
