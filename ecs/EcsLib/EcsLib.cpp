#include "EcsLib.h"
#include <FusionCore/FusionCore.h>

NAMESPACE_UPP


bool Open_NonGUI_ECS() {
	using namespace Topside;
	Machine mach;
	
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& ents = *mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    
    #if HAVE_SDL2
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
	using namespace Topside;
	Machine mach;
	
	mach.Stop();
}


END_UPP_NAMESPACE
