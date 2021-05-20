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
    mach.Add<HumanSystem>();
    mach.Add<DisplaySystem>();
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



NAMESPACE_TOPSIDE_BEGIN


CamerableRef HumanCustomSinkBase::GetCamerable() {
	return CamerableRef();
}

TransformRef HumanCustomSinkBase::GetTransform() {
	return TransformRef();
}


NAMESPACE_TOPSIDE_END
