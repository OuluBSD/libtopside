#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Screen, Scr, S) {
	IfaceLib::Add(this);
	
	COLOR(112, 112, 112)
	DEPENDENCY(ParallelLib)
	
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
		LIBRARY("POSIX", X11)
		VENDOR_INCLUDE("", X11/Xlib.h)
		VENDOR_INCLUDE("", X11/Xutil.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("win",			"::Window")
			.Add("display",		"::Display*")
			.Add("gc",			"::GC")
			;
		
		
	}
	
	
}


NAMESPACE_PLAN_END
