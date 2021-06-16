#include "EcsLib.h"

NAMESPACE_UPP


bool Open_NonGUI_ECS() {
	using namespace TS;
	Machine mach;
	
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& ents = *mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    
    #if HAVE_SDL2
    mach.Add<SDL2System>();
    #endif
    mach.Add<CenterSystem>();
    
    reg.SetAppName("ECS machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void Close_NonGUI_ECS() {
	using namespace TS;
	Machine mach;
	
	mach.Stop();
}


END_UPP_NAMESPACE

