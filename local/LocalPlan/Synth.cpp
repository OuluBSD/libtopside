#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddSynth() {
	Package("Synth", "Syn");
	SetColor(200, 179, 81);
	Dependency("ParallelLib");
	Dependency("SoftInstru");
	Dependency("SoftSynth");
	Dependency("AudioCore");
	Dependency("ports/fluidlite", "FLUIDSYNTH");
	Dependency("ports/lilv");
	Dependency("LV2Host", "", false);
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("Instrument");
	
	Vendor("Soft");
	Vendor("Fluidsynth", "FLUIDSYNTH");
	Vendor("FmSynth");
	Vendor("CoreSynth");
	Vendor("LV2");
	
}


NAMESPACE_TOPSIDE_END
