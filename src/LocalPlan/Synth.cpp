#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddSynth() {
	Package("Synth", "Syn");
	SetColor(200, 179, 81);
	Dependency("ParallelLib");
	Dependency("SoftInstru");
	Dependency("SoftSynth");
	Dependency("AudioCore");
	Dependency("ports/fluidlite", "FLUIDLITE", false);
	Library("fluidsynth", "FLUIDSYNTH");
	Dependency("ports/lilv", "LV2", false);
	Dependency("AudioHost", "LV2", false);
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("Instrument");
	
	Vendor("Soft");
	Vendor("Fluidsynth", "FLUIDSYNTH|FLUIDLITE");
	Vendor("FmSynth");
	Vendor("CoreSynth");
	Vendor("CoreDrummer");
	Vendor("LV2", "LV2");
	
}


NAMESPACE_TOPSIDE_END
