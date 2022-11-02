#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddVolumetric() {
	Package("Volumetric", "Vol");
	SetColor(28, 85, 0);
	Dependency("ParallelLib");
	HaveIsReady();
	
	Interface("StaticSource");
	
	Vendor("RawByte");
	
}


NAMESPACE_TOPSIDE_END
