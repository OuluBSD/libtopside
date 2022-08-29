#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddCamera() {
	Color(54, 157, 442);
	Dependency("ParallelLib");
	Dependency("IMedia");
	HaveIsReady();
	
	Interface("Camera");
	
	Vendor("V4L2OpenCV", "OPENCV&LINUX");
	
}


NAMESPACE_TOPSIDE_END
