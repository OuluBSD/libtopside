#include <Complete/Complete.h>
#include <DesktopSuite/DesktopSuite.h>
#include <EcsVirtualGui/EcsVirtualGui.h>
using namespace UPP;

void CreateGeom2DComponent() {
	
	
	
}


GUI_APP_MAIN {
	using namespace Ecs;
	RTLOG("CreateGeom2DComponent");
	Ecs::Engine& eng = GetActiveEngine();
	WindowSystemRef wins = eng.Get<WindowSystem>();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<Geom2DComponent> cw = e->Get<Geom2DComponent>();
	
	WindowSystemScreen* active_screen = wins->GetActiveScreen();
	active_screen->AddWindow(*cw);
	
	
	DebugMainLoop();
}
