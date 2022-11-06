#include "Internal.h"


NAMESPACE_UPP

VirtualGui3D* VirtualGui3DPtr;

INITBLOCK_(VirtualGui) {
	using namespace Serial;
	using namespace Ecs;
	
	// System
	Engine::Register<Ecs::VirtualGuiSystem>("virtualgui");
	
	
}



END_UPP_NAMESPACE
