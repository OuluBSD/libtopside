#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddScreen() {
	Package("Screen", "Scr");
	SetColor(112, 112, 112);
	Dependency("ParallelLib");
	Dependency("IGraphics");
	Library("X11 Xrandr Xxf86vm", "POSIX & !EMSCRIPTEN");
	Library("GLX GL GLU GLEW glut", "POSIX & OGL & !EMSCRIPTEN");
	HaveRecvFinalize();
	HaveNegotiateFormat();
	HaveIsReady();
	
	Interface("SinkDevice");
	Interface("Context");
	Interface("EventsBase");
	
	Vendor("X11", "POSIXDESKTOP&SCREEN");
	Vendor("X11Sw", "POSIXDESKTOP&SCREEN");
	Vendor("X11Ogl", "POSIXDESKTOP&SCREEN&OGL");
	
	
}


NAMESPACE_TOPSIDE_END
