#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddHal() {
	Package("Hal", "Hal");
	SetColor(198, 127, 200);
	Dependency("ParallelLib");
	Dependency("IGraphics");
	Library("SDL2", "SDL2");
	Library("SDL2_ttf", "SDL2");
	Library("SDL2_image", "SDL2");
	HaveRecvFinalize();
	HaveUpdate();
	HaveIsReady();
	HaveContextFunctions();
	
	Interface("AudioSinkDevice");
	Interface("CenterVideoSinkDevice");
	Interface("CenterFboSinkDevice");
	Interface("OglVideoSinkDevice", "OGL");
	Interface("ContextBase");
	Interface("EventsBase");
	Interface("UppEventsBase");
	Interface("UppOglDevice", "OGL");
	
	Vendor("Sdl", "SDL2");
	
}


NAMESPACE_TOPSIDE_END
