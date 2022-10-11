#include "NonCtrlSDL2.h"
#include <OOSDL2/OOSDL2.h>
#include <EcsLib/EcsLib.h>
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
    
    #define DEV(x) mach.Add<x##System>();
    DEV_LIST
    #undef DEV
    
    #define IFACE(x) mach.Add<ScopeValLibT<x##Spec>::PacketTracker>();
    IFACE_LIST
    #undef IFACE
    
    
    
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
