#include "DesktopShell.h"


NAMESPACE_TOPSIDE_BEGIN


void DesktopMain() {
	using namespace Parallel;
	
	//GeomInteraction::do_debug_draw = true;
	#if 0
	SDL2GUI gui;
	gui.Create(RectC(100, 100, 1024, 768), "SDL2GL Virtual Gui Test");

	RunVirtualGui(gui, [] {
		SetLanguage(LNG_ENGLISH);
		SetDefaultCharset(CHARSET_UTF8);
		
		ChClassicSkin();
		
		GuiTesterApp app;
		app.OpenMain();
		//app.SetRect(RectC(10,10,640,480));
		Ctrl::EventLoop();
	});
	#else
	//GuiTesterApp().RunInMachine();
	//CtrlTesterApp().RunInMachine();
	EventsTester().RunInMachine();
	#endif
	
	Machine& mach = GetActiveMachine();
	
	WindowSystemRef wins = mach.Get<WindowSystem>();
	
	if (wins) {
		
		
	}
}


NAMESPACE_TOPSIDE_END



CONSOLE_APP_MAIN {
	using namespace TS;
	Serial::Machine::WhenInitialize << callback(DefaultSerialInitializer);
	Serial::Machine::WhenPreFirstUpdate << callback(DefaultStartup);
	Serial::Machine::WhenUserProgram << callback(DesktopMain);
	
	SingleMachine mach;
	if (mach.Start()) {
		DefaultRunner(0, "Gui App", GUI_EON);
		
		mach.Stop();
	}
}
