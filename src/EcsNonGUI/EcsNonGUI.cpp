#include "EcsNonGUI.h"


NAMESPACE_ECS_BEGIN


bool SingleEngine::Open(bool gui) {
	const AppFlags& flags = GetAppFlags();
	Engine& mach = GetActiveEngine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef ents = mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    mach.Add<ExtSystem>();
    
    reg->SetAppName("SDL2 ECS machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void SingleEngine::Close() {
	Engine& mach = GetActiveEngine();
	mach.Stop();
}


NAMESPACE_ECS_END
