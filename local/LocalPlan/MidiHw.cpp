#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddMidiHw() {
	Package("MidiHw", "Mid");
	SetColor(198, 85, 150);
	Dependency("ParallelLib");
	Dependency("MidiFile");
	Dependency("ports/portmidi", "BUILTIN_PORTMIDI", false);
	HaveIsReady();
	Library("portmidi", "PORTMIDI");
	
	Interface("Source");
	
	Vendor("Portmidi", "PORTMIDI|BUILTIN_PORTMIDI");
	
}


NAMESPACE_TOPSIDE_END
