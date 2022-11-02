#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddAudio() {
	Package("Audio", "Aud");
	SetColor(226, 212, 0);
	Dependency("ParallelLib");
	Dependency("ports/portaudio", "BUILTIN_PORTAUDIO");
	Library("portaudio", "PORTAUDIO");
	HaveNegotiateFormat();
	
	Interface("SinkDevice");
	Interface("SourceDevice");
	
	Vendor("Portaudio", "BUILTIN_PORTAUDIO|PORTAUDIO");
	
}


NAMESPACE_TOPSIDE_END
