#include "EcsComplete.h"



NAMESPACE_SERIAL_BEGIN


void EngineEcsInit();


void MachineEcsInit() {
	Machine& mach = GetActiveMachine();
	mach.Add<EntitySystem>();
	
	#ifdef flagPHYSICS
	#ifdef flagODE
	mach.FindAdd<SystemT<OdeFys>>();
	#else
	mach.FindAdd<SystemT<TosFys>>();
	#endif
	#endif
	
	Ecs::Engine::WhenInitialize << callback(EngineEcsInit);
}

void EngineEcsInit() {
    Ecs::Engine& eng = Ecs::GetActiveEngine();
    
	eng.GetAdd<Ecs::RegistrySystem>();
	eng.GetAdd<Ecs::InteractionSystem>();
	
	eng.GetAdd<Ecs::RenderingSystem>();
	eng.GetAdd<Ecs::EntityStore>();
	eng.GetAdd<Ecs::ComponentStore>();
	eng.GetAdd<Ecs::EventSystem>();
	
	#ifdef flagDEBUG
	LOG("warning: TODO ecs window system");
	#endif
	
	#if 0
	#if HAVE_WINDOWSYSTEM
	eng.GetAdd<Ecs::VirtualGuiSystem>();
	eng.GetAdd<Ecs::WindowSystem>();
	#endif
	#endif
	
	//DefaultSerialInitializerInternalEon();
}


NAMESPACE_SERIAL_END
