#include "System.h"
#include <FusionCore/FusionCore.h>
#include <Physics/Physics.h>

NAMESPACE_TOPSIDE_BEGIN




bool SDL2GUI3DSystem::Initialize() {
	return gui.Open();
}

void SDL2GUI3DSystem::Start() {
	
}

void SDL2GUI3DSystem::Update(double dt) {
	
}

void SDL2GUI3DSystem::Stop() {
	
}

void SDL2GUI3DSystem::Uninitialize() {
	gui.Close();
}




bool SingleMachine::Open(bool gui) {
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef ents = mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    mach.Add<SDL2System>();
    mach.Add<SDL2GUI3DSystem>();
    mach.Add<EventSystem>();
    mach.Add<RenderingSystem>();
    mach.Add<AudioSystem>();
    mach.Add<FusionSystem>();
    
    if (gui)
		mach.Add<WindowSystem>();
	
    mach.Add<HolographicScene>();
    mach.Add<EasingSystem>();
    mach.Add<MotionControllerSystem>();
    mach.Add<WorldLogicSystem>();
	   
    if (flags.HaveOdePhysics())
		mach.Add<OdeSystem>();
	
    
    #ifdef flagOPENVR
    mach.Add<OpenVR>();
    #endif
    
    reg->SetAppName("SDL2 ECS machine");
    
    if (!mach.Start())
		return false;
    
    PoolRef pool = ents->GetRoot()->GetAddPool("windows");
    EntityRef app = pool->Create<SDL2StandaloneWindow>();
    //app->Find<Connector>()->ConnectAll();
    
	return true;
}

void SingleMachine::Close() {
	Machine& mach = GetActiveMachine();
	mach.Stop();
}


NAMESPACE_TOPSIDE_END
