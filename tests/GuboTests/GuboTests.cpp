#include "GuboTests.h"


GuboTester::GuboTester() {
	
}

void GuboTester::Paint(Draw3D& d) {
	Volf sz = GetCub();
	Volf ground = sz;
	ground.cy = 0.1;
	d.DrawCuboid(0, ground, Color(160, 221, 196));
	
	double time = ts.Seconds();
	float phase = fmod(time, phase_seconds) * M_PI*2;
	
	// Circling
	Point3f pos1(sin(phase), cos(phase), 0);
	d.DrawSphere(pos1, 0.5, Color(170, 173, 255));
	
	// Bouncing
	Point3f pos2(0, fabs(phase), 0);
	d.DrawSphere(pos2, 0.5, Color(255, 181, 176));
	
	
}



#if 1
void UserGuiMainFn() {
	GuboTester().Run();
}

CONSOLE_APP_MAIN {
	TS::Serial::Machine::WhenInitialize << callback(TS::DefaultSerialInitializer);
	TS::Serial::Machine::WhenPreFirstUpdate << callback(TS::DefaultStartup);
	TS::Serial::Machine::WhenUserProgram << callback(UserGuiMainFn);
	
	TS::SingleMachine mach;
	if (mach.Start()) {
		TS::DefaultRunner(0, "Gui App", GUBO_EON);
		
		mach.Stop();
	}
}
	

#else

//void DefaultSerialInitializer() {SetCoutLog(); DefaultInitializer(false);}

GUBO_APP_MAIN {
	#if 0
	using namespace Ecs;
	Ecs::Engine& eng = GetActiveEngine();
	Workspace3DSystemRef wins = eng.Get<Workspace3DSystem>();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<Geom2DComponent> cw = e->Get<Geom2DComponent>();
	
	GuiSystemWorkspace3D* active_workspace = wins->GetActiveWorkspace();
	active_screen->AddWindow(*cw);
	
	DebugMainLoop();
	#else
	
	GuboTester().Run();
	
	#endif
}

#endif
