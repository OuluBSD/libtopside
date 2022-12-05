#include <Complete/Complete.h>
#include <DesktopSuite/DesktopSuite.h>
#include <EcsVirtualGui/EcsVirtualGui.h>
using namespace UPP;

void CreateCoreWindow() {
	
	
	
}


GUI_APP_MAIN {
	using namespace Ecs;
	RTLOG("CreateCoreWindow");
	Ecs::Engine& eng = GetActiveEngine();
	WindowSystemRef wins = eng.Get<WindowSystem>();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<CoreWindow> cw = e->Get<CoreWindow>();
	
	WindowSystemScreen* active_screen = wins->GetActiveScreen();
	active_screen->AddWindow(*cw);
	
	
	DebugMainLoop();
}
