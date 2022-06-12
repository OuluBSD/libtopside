#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN


PKG(Holograph, Holo, H) {
	IfaceLib::Add(this);
	
	COLOR(85, 42, 150)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(IGraphics)
	LIBRARY("LINUX & OPENHMD", openhmd hidapi-libusb)
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
		VENDOR_INCLUDE("", openhmd.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("ctx",			"ohmd_context*")
			.Add("settings",	"ohmd_device_settings*")
			.Add("fragment",	"const char*")
			.Add("vertex",		"const char*")
			.Add("hmd",			"ohmd_device*")
			.Add("screen_sz",	"Size")
			.Add("l_proj",		"mat4")
			.Add("l_view",		"mat4")
			.Add("r_proj",		"mat4")
			.Add("r_view",		"mat4")
			;
		
	}
	
}


NAMESPACE_PLAN_END
