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
	ComponentFactory::Register<Transform>("transform3");
	ComponentFactory::Register<Transform2D>("transform2");
	ComponentFactory::Register<Viewable>("viewable");
	ComponentFactory::Register<Viewport>("viewport");
	ComponentFactory::Register<ChaseCam>("camera.chase");
	ComponentFactory::Register<Renderable>("renderable");
	ComponentFactory::Register<ModelComponent>("model");
	
	
}

END_UPP_NAMESPACE
