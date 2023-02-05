#include "DesktopShell.h"


NAMESPACE_TOPSIDE_BEGIN


void DesktopMain() {
	using namespace Parallel;
	
	//GeomInteraction::do_debug_draw = true;
	GuiTesterApp().Run();
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
