#include "EcsCore.h"

NAMESPACE_UPP_BEGIN


INITBLOCK_(EcsCore) {
	using namespace Serial;
	using namespace Ecs;
	
	// Core
	Engine::Register<EntityStore>("entity.store");
	Engine::Register<ComponentStore>("component.store");
	
}


NAMESPACE_UPP_END
