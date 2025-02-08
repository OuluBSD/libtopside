#include "EcsLib.h"

NAMESPACE_UPP

MAKE_STATIC(Serial::ExtScriptEcsLoader, __ext_script_loader);

INITBLOCK_(EcsLib) {
	using namespace Serial;
	using namespace Ecs;
	
	__ecs_script_loader = &__ext_script_loader;
	
	// System
	Engine::Register<Ecs::RegistrySystem>("registry");
	Engine::Register<Ecs::EventSystem>("events");
	Engine::Register<Ecs::RenderingSystem>("rendering");
	
	
	// Component
	#define COMP(t, k, v) ComponentFactory::Register<t>(k);
	#include "Types.inl"
	#undef COMP
}

END_UPP_NAMESPACE
