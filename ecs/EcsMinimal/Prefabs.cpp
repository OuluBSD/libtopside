#include "EcsMinimal.h"

NAMESPACE_ECS_BEGIN


void DefaultEcsInitializer() {
	Engine& eng = GetActiveEngine();
	eng.GetAdd<RenderingSystem>();
	eng.GetAdd<EntityStore>();
	eng.GetAdd<ComponentStore>();
	#ifdef flagODE
	eng.GetAdd<OdeSystem>();
	#else
	//eng.GetAdd<TosSystem>();
	#endif
	eng.GetAdd<EventSystem>();
	
	#if HAVE_WINDOWSYSTEM
	eng.GetAdd<VirtualGuiSystem>();
	eng.GetAdd<WindowSystem>();
	#endif
	
	//Serial::Machine& mach = Serial::GetActiveMachine();
	//eng.GetAdd<PhysicsSystem>();
	
	/*
	mach.Add<RegistrySystem>();
    mach.Add<HumanSystem>();
    mach.Add<DisplaySystem>();
    mach.Add<WindowSystem>();
    #ifdef flagOPENVR
    mach.Add<OpenVR>();
    #endif
    
    EntityStore& ents = *mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    mach.Add<HolographicScene>();
    mach.Add<EasingSystem>();
    mach.Add<AudioSystem>();
    mach.Add<ControllerSystem>();
    mach.Add<MotionControllerSystem>();
    mach.Add<WorldLogicSystem>();
    
    bool physics = false;
    if (physics)
		mach.Add<PhysicsSystem>();

    mach.Start();
    
	ents.Create<CameraPrefab>();
	*/
	
	DefaultSerialInitializerInternalEon();
}


void DefaultEcsStartup() {
	/*Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	RenderingSystemRef rend = eng.Get<RenderingSystem>();
	PoolRef models = ents->GetRoot()->GetAddPool("models");
	PoolRef cameras = ents->GetRoot()->GetAddPool("cameras");
	EntityRef gnd = models->Create<StaticGroundPlanePrefab>();
	EntityRef car = models->Create<BuggyCarPrefab>();
	EntityRef cam = cameras->Create<CameraPrefab>();
	
	Ref<ChaseCam> chaser = cam->Add<ChaseCam>();
	chaser->SetTarget(car->Get<Transform>());
	rend->AddViewable(cam->Get<Viewable>());*/
}


NAMESPACE_ECS_END
