#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddEffect() {
	Package("Effect", "Fx");
	SetColor(28, 255, 150);
	Dependency("AudioCore");
	Dependency("ParallelLib");
	Dependency("ports/lilv", "LV2", false);
	Dependency("AudioHost", "LV2", false);
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("Effect");
	
	Vendor("AudioCore");
	Vendor("LV2", "LV2");
	
}


NAMESPACE_TOPSIDE_END
