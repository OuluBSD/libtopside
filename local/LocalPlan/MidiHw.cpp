#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddMidiHw() {
	Color(198, 85, 150);
	Dependency("ParallelLib");
	HaveIsReady();
	
	Interface("Source");
	
	Vendor("Portmidi");
	
}


NAMESPACE_TOPSIDE_END
