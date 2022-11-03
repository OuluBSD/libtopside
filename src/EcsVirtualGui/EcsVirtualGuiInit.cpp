#include "EcsVirtualGui.h"
#include <Local/Local.h>

NAMESPACE_UPP

INITBLOCK_(EcsVirtualGui) {
	#if HAVE_WINDOWSYSTEM
	Ecs::Engine::Register<Ecs::WindowSystem>("windows");
	#endif
}

END_UPP_NAMESPACE

