#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddScreen() {
	Package("Screen", "Scr");
	SetColor(112, 112, 112);
	Dependency("ParallelLib");
	Dependency("IGraphics");
	Library("X11 Xrandr Xxf86vm", "POSIX");
	Library("GLX GL GLU GLEW glut", "POSIX & OGL");
	HaveRecvFinalize();
	HaveNegotiateFormat();
	HaveIsReady();
	
	Interface("SinkDevice");
	Interface("Context");
	Interface("EventsBase");
	
	Vendor("X11", "LINUX|FREEBSD");
	Vendor("X11Sw", "LINUX|FREEBSD");
	Vendor("X11Ogl", "LINUX&OGL|FREEBSD&OGL");
	
	
}


NAMESPACE_TOPSIDE_END
