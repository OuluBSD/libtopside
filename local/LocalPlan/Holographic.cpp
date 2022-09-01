#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddHolographic() {
	Package("Holographic", "Holo");
	SetColor(85, 42, 150);
	Dependency("ParallelLib");
	Dependency("IMedia");
	Dependency("ports/hcidump", "LINUX");
	Dependency("LocalHMD", "LOCALHMD");
	Library("openhmd hidapi-libusb", "LINUX & OPENHMD");
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("SinkDevice");
	
	Vendor("OpenHMD", "LINUX&OPENHMD|FREEBSD&OPENHMD");
	Vendor("LocalHMD", "LOCALHMD");
	Vendor("RemoteVRServer", "LINUX|FREEBSD");
	Vendor("DevUsb", "LINUX|FREEBSD");
	Vendor("DevBluetooth", "LINUX&HACK|FREEBSD&HACK");
	
}


NAMESPACE_TOPSIDE_END
