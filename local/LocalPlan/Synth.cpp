#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddSynth() {
	Color(200, 179, 81);
	Dependency("ParallelLib");
	Dependency("SoftInstru");
	Dependency("SoftSynth");
	Dependency("AudioCore");
	Dependency("ports/fluidlite", "FLUIDSYNTH");
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("Instrument");
	
	Vendor("Soft");
	Vendor("Fluidsynth", "FLUIDSYNTH");
	Vendor("FmSynth");
	Vendor("CoreSynth");
	
}


NAMESPACE_TOPSIDE_END
