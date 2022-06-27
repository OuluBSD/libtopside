#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN


PKG(Holograph, Holo, H) {
	IfaceLib::Add(this);
	
	COLOR(85, 42, 150)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(IGraphics)
	DEPENDENCY_("LINUX", ports/hcidump)
	DEPENDENCY_("LOCALHMD", LocalHMD)
	LIBRARY("LINUX & OPENHMD", openhmd hidapi-libusb)
	/*LIBRARY("POSIX", X11)
	LIBRARY("POSIX & OGL", GLX)
	LIBRARY("POSIX & OGL", GL GLU GLEW glut)*/
	HAVE_RECV_FINALIZE
	//HAVE_NEGOTIATE_FORMAT
	HAVE_IS_READY
	
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
			.Add("ctx",						"ohmd_context*")
			.Add("settings",				"ohmd_device_settings*")
			.Add("fragment",				"const char*")
			.Add("vertex",					"const char*")
			.Add("hmd",						"ohmd_device*")
			.Add("ctrl[2]",					"ohmd_device*")
			.Add("screen_sz",				"Size")
			.Add("ev",						"CtrlEvent")
			.Add("ev3d",					"ControllerMatrix")
			.Add("ev_sendable",				"bool")
			.Add("seq",						"int")
			.Add("ts",						"TimeStop")
			.Add("control_count[2]",		"int")
			.Add("controls_fn[2][64]",		"int")
			.Add("controls_types[2][64]",	"int")
		;
		
	}
	
	VENDOR(LocalHMD) {
		VENDOR_ENABLED_FLAG(LOCALHMD)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		VENDOR_INCLUDE("", LocalHMD/LocalHMD.h)
		
		v->AddStruct("NativeSinkDevice")
			.Add("ctx",						"TS::HMD::Context*")
			.Add("settings",				"TS::HMD::DeviceSettings*")
			.Add("fragment",				"const char*")
			.Add("vertex",					"const char*")
			.Add("hmd",						"TS::HMD::Device*")
			.Add("ctrl[2]",					"TS::HMD::Device*")
			.Add("screen_sz",				"Size")
			.Add("ev",						"CtrlEvent")
			.Add("ev3d",					"ControllerMatrix")
			.Add("trans",					"TransformMatrix")
			.Add("has_initial_orient",		"bool")
			.Add("initial_orient",			"quat")
			.Add("ev_sendable",				"bool")
			.Add("seq",						"int")
			.Add("ts",						"TimeStop")
			.Add("control_count[2]",		"int")
			.Add("controls_fn[2][64]",		"int")
			.Add("controls_types[2][64]",	"int")
		;
		
	}
	
	VENDOR(DevUsb) {
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		//VENDOR_INCLUDE("", openhmd.h)
		//VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
		;
		
	}
	
	VENDOR(DevBluetooth) {
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		VENDOR_INCLUDE("", ports/hcidump/hcidump.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, void*)
		
		v->AddStruct("NativeSinkDevice")
			.Add("bt[2]",		"SimpleBluetoothConnection")
			.Add("data[2]",		"Vector<byte>")
			.Add("sock",		"TcpSocket")
			.Add("mode",		"int")
			.Add("ctrl_idx[2]",	"int")
		;
		
	}
	
}


NAMESPACE_PLAN_END
