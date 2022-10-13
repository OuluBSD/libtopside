#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddEffect() {
	Package("Effect", "Fx");
	SetColor(28, 255, 150);
	Dependency("AudioCore");
	Dependency("ParallelLib");
	Dependency("ports/lilv");
	Dependency("LV2Host", "", false);
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("Effect");
	
	Vendor("AudioCore");
	Vendor("LV2");
	
}


NAMESPACE_TOPSIDE_END
