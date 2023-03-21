#include "GuboShell.h"


NAMESPACE_TOPSIDE_BEGIN


void VguiMain() {
	#if IS_UPP_CORE
	SetLanguage(LNG_ENGLISH);
	SetDefaultCharset(CHARSET_UTF8);
	
	ChClassicSkin();
	#endif
	
	
	Gu::GuboTester app;
	app.OpenMain();
	Surface::EventLoop();
}

void DesktopMain() {
	using namespace Parallel;
	
	Surface::SetDebugDraw(0);
	Gubo::SetDebugDraw(1);
	
	#if 0
	AtomVirtualGui3D gui;
	gui.Create(RectC(100, 100, 1024, 768), "GuboShell");
	RunVirtualGui3D(gui, callback(VguiMain));
	#endif
	
	VguiMain();
}


NAMESPACE_TOPSIDE_END



CONSOLE_APP_MAIN {
	using namespace TS;
	Serial::Machine::WhenInitialize << callback(DefaultSerialInitializer);
	Serial::Machine::WhenPreFirstUpdate << callback(DefaultStartup);
	Serial::Machine::WhenUserProgram << callback(DesktopMain);
	
	SingleMachine mach;
	if (mach.Start()) {
		DefaultRunner(0, "Gubo App", GUBO_EON);
		
		mach.Stop();
	}
}
