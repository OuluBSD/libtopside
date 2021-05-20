#include <Local/Local.h>
#include <EcsCore/EcsCore.h>
#include <EcsLib/EcsLib.h>
#include "System.h"


NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(bool gui) {
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef ents = mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    mach.Add<HumanSystem>();
    mach.Add<AudioSystem>();
    mach.Add<DeviceSystem>();
    
    reg->SetAppName("SDL2 ECS machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void SingleMachine::Close() {
	Machine& mach = GetActiveMachine();
	mach.Stop();
}


NAMESPACE_TOPSIDE_END
