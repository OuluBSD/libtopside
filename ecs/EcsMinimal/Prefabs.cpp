#include "EcsMinimal.h"

NAMESPACE_ECS_BEGIN


void DefaultEcsSerialInitializer() {
	Machine& mach = GetActiveMachine();
	
	#ifdef flagODE
	mach.FindAdd<SystemT<OdeFys>>();
	#else
	mach.FindAdd<SystemT<TosFys>>();
	#endif
}

void DefaultEcsInitializer() {
	Engine& eng = GetActiveEngine();
	
	eng.GetAdd<RenderingSystem>();
	eng.GetAdd<EntityStore>();
	eng.GetAdd<ComponentStore>();
	eng.GetAdd<EventSystem>();
	
	#if HAVE_WINDOWSYSTEM
	eng.GetAdd<VirtualGuiSystem>();
	eng.GetAdd<WindowSystem>();
	#endif
	
	DefaultSerialInitializerInternalEon();
}


void DefaultEcsStartup() {
	
}


NAMESPACE_ECS_END
