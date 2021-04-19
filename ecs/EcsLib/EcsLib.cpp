#include "EcsLib.h"
#include <FusionCore/FusionCore.h>

NAMESPACE_UPP


bool Open_NonGUI_ECS() {
	using namespace Oulu;
	Machine& mach = Oulu::GetMachine();
	
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& ents = *mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    
    #ifdef flagSDL2
    mach.Add<SDL2System>();
    #endif
    mach.Add<EventSystem>();
    mach.Add<RenderingSystem>();
    mach.Add<AudioSystem>();
    mach.Add<FusionSystem>();
    
    reg.SetAppName("ECS machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void Close_NonGUI_ECS() {
	using namespace Oulu;
	Machine& mach = Oulu::GetMachine();
	
	mach.Stop();
}


END_UPP_NAMESPACE
