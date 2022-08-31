#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddMidiHw() {
	Package("MidiHw", "Mid");
	SetColor(198, 85, 150);
	Dependency("ParallelLib");
	HaveIsReady();
	
	Interface("Source");
	
	Vendor("Portmidi", "PORTMIDI");
	
}


NAMESPACE_TOPSIDE_END
