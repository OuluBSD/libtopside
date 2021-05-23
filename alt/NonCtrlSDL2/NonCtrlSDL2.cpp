#include "NonCtrlSDL2.h"
#include <OOSDL2/OOSDL2.h>
#include <EcsLib/EcsLib.h>
#include <AccelCore/AccelCore.h>
#include <Physics/Physics.h>

NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(bool gui) {
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef ents = mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    mach.Add<ConnectorStore>();
    mach.Add<SDL2System>();
    mach.Add<HumanSystem>();
    mach.Add<DisplaySystem>();
    mach.Add<AudioSystem>();
    mach.Add<StaticSystem>();
    mach.Add<DeviceSystem>();
    mach.Add<FusionSystem>();
    
    //if (gui)
	//	mach.Add<WindowSystem>();
	
    /*mach.Add<HolographicScene>();
    mach.Add<EasingSystem>();
    mach.Add<MotionControllerSystem>();
    mach.Add<WorldLogicSystem>();*/
	   
    //if (flags.HaveOdePhysics())
	//	mach.Add<OdeSystem>();
	
    
    #ifdef flagOPENVR
    mach.Add<OpenVR>();
    #endif
    
    reg->SetAppName("SDL2 ECS machine");
    
    if (!mach.Start())
		return false;
    
    //PoolRef pool = ents->GetRoot()->GetAddPool("windows");
    //EntityRef app = pool->Create<SDL2StandaloneWindow>();
    //app->Find<Connector>()->ConnectAll();
    
	return true;
}

void SingleMachine::Close() {
	Machine& mach = GetActiveMachine();
	mach.Stop();
}



NAMESPACE_TOPSIDE_END
