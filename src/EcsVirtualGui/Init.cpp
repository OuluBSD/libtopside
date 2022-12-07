#include "EcsVirtualGui.h"

NAMESPACE_UPP


INITBLOCK_(EcsVirtualGui) {
	#if 0
	Ecs::Engine::Register<Ecs::WindowSystem>("windows");
	#endif
	
	Ecs::Engine::Register<Ecs::VirtualGuiSystem>("virtualgui");
	
}


END_UPP_NAMESPACE

