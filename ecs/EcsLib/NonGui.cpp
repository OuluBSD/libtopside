#include "EcsLib.h"

NAMESPACE_UPP


bool Open_NonGUI_ECS() {
	using namespace TS;
	using namespace TS::ECS;
	Engine mach;
	
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& ents = *mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    
    reg.SetAppName("ECS machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void Close_NonGUI_ECS() {
	using namespace TS;
	using namespace TS::ECS;
	Engine mach;
	
	mach.Stop();
}


END_UPP_NAMESPACE

