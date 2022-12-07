#include "CuboidTests.h"


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
	Pointf pos1(sin(phase), cos(phase));
	d.DrawSphere(pos1, 0.5, Color(170, 173, 255));
	
	// Bouncing
	Pointf pos2(0, fabs(phase), 0);
	d.DrawSphere(pos2, 0.5, Color(255, 181, 176));
	
	
}


GUBO_APP_MAIN {
	#if 0
	using namespace Ecs;
	Ecs::Engine& eng = GetActiveEngine();
	Workspace3DSystemRef wins = eng.Get<Workspace3DSystem>();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<CoreWindow> cw = e->Get<CoreWindow>();
	
	GuiSystemWorkspace3D* active_workspace = wins->GetActiveWorkspace();
	active_screen->AddWindow(*cw);
	
	DebugMainLoop();
	#else
	
	GuboTester().Run();
	
	#endif
}
