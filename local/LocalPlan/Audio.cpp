#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddAudio() {
	Package("Audio", "Aud");
	SetColor(226, 212, 0);
	Dependency("ParallelLib");
	HaveNegotiateFormat();
	
	Interface("SinkDevice");
	Interface("SourceDevice");
	
	Vendor("Portaudio", "BUILTIN_PORTAUDIO|WIN32&MSC");
	
}


NAMESPACE_TOPSIDE_END
