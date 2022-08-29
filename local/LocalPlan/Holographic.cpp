#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddHolographic() {
	Color(85, 42, 150);
	Dependency("ParallelLib");
	Dependency("IMedia");
	Dependency("ports/hcidump", "LINUX");
	Dependency("LocalHMD", "LOCALHMD");
	Library("openhmd hidapi-libusb", "LINUX & OPENHMD");
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("SinkDevice");
	
	Vendor("OpenHMD", "LINUX|FREEBSD");
	
}


NAMESPACE_TOPSIDE_END
