#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddAudioFileOut() {
	Package("AudioFileOut", "AFO");
	SetColor(80, 58, 119);
	Dependency("ParallelLib");
	HaveRecvFinalize();
	HaveIsReady();
	
	Interface("Sink");
	
	Vendor("CoreAudio");
	
}


NAMESPACE_TOPSIDE_END
