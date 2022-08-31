#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddCamera() {
	Package("Camera", "Cam");
	SetColor(54, 157, 42);
	Dependency("ParallelLib");
	Dependency("IMedia");
	HaveIsReady();
	
	Interface("Camera");
	
	Vendor("V4L2OpenCV", "OPENCV&LINUX");
	
}


NAMESPACE_TOPSIDE_END
