#include "GuiTests.h"

GuiTester::GuiTester() {
	
	
	
}

void GuiTester::Paint(Draw& d) {
	Size sz = GetSize();
	
	if (do_debug_draw) {
		if (has_mouse) {
			RGBA c{255, 0, 0, 125};
			d.DrawRect(sz, c);
		}
		else {
			RGBA c(RandomColor(64, 128));
			c.a = 127;
			d.DrawRect(sz, c);
		}
	}
	else
		d.DrawRect(sz, White());
	
	d.DrawRect(30, 30, 30,30, Yellow());
	d.DrawText(30,30, "GuiTester", SansSerif(), Black());
	d.DrawLine(0,0, 200, 400, 3, LtGreen());
	
}



#if 1
void UserGuiMainFn() {
	//GeomInteraction::do_debug_draw = true;
	GuiTester().Run();
	//GuiTesterApp().Run();
}

CONSOLE_APP_MAIN {
	TS::Serial::Machine::WhenInitialize << callback(TS::DefaultSerialInitializer);
	TS::Serial::Machine::WhenPreFirstUpdate << callback(TS::DefaultStartup);
	TS::Serial::Machine::WhenUserProgram << callback(UserGuiMainFn);
	
	TS::SingleMachine mach;
	if (mach.Start()) {
		TS::DefaultRunner(0, "Gui App", GUI_EON);
		
		mach.Stop();
	}
}
	

#else
GUI_APP_MAIN {
	using namespace Ecs;
	RTLOG("GUI_APP_MAIN");
	Ecs::Engine& eng = GetActiveEngine();
	WindowSystemRef wins = eng.Get<WindowSystem>();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<Geom2DComponent> cw = e->Get<Geom2DComponent>();
	
	WindowSystemScreen* active_screen = wins->GetActiveScreen();
	active_screen->AddWindow(*cw);
	
	
	DebugMainLoop();
}

#endif
