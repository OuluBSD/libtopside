#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::AddScreen() {
	Package("Screen", "Scr");
	SetColor(112, 112, 112);
	Dependency("ParallelLib");
	Dependency("IGraphics");
	Library("X11 Xrandr Xxf86vm", "POSIX & !EMSCRIPTEN");
	Library("GLX GL GLU GLEW glut", "POSIX & OGL & !EMSCRIPTEN");
	Library("D3D11", "WIN32 & DX11");
	HaveRecvFinalize();
	HaveNegotiateFormat();
	HaveIsReady();
	
	Interface("SinkDevice");
	Interface("Context");
	Interface("EventsBase");
	
	Vendor("UppCtrl",	"GUI&UPPCORE");
	Vendor("X11",		"POSIXDESKTOP&SCREEN");
	Vendor("X11Sw",		"POSIXDESKTOP&SCREEN");
	Vendor("X11Ogl",	"POSIXDESKTOP&SCREEN&OGL");
	Vendor("Win",		"WIN32&SCREEN&!UWP");
	//Vendor("WinSw",	"WIN32&SCREEN");
	Vendor("WinD11",	"WIN32&SCREEN&DX11");
	
	
}


NAMESPACE_TOPSIDE_END
