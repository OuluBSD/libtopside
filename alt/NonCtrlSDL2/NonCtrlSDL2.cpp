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
    
    #define IFACE_CTX_CLS(dev, value, prefix) mach.Add<prefix##System>();
    #define IFACE(x) DEV_IFACE(x)
    IFACE_LIST
    #undef IFACE
    #undef IFACE_CTX_CLS
    mach.Add<AccelSystem>();
    
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
    
    PoolRef pool = ents->GetRoot()->GetAddPool("system");
    pool->AddConnectEverything();
    EntityRef app = pool->Create<SDL2StandaloneWindow>();
    pool->ConnectEverything();
    
	return true;
}

void SingleMachine::Close() {
	Machine& mach = GetActiveMachine();
	mach.Stop();
}



NAMESPACE_TOPSIDE_END
