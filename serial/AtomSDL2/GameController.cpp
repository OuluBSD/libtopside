#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



bool SDL2GameControllerBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	return true;
}

void SDL2GameControllerBase::Uninitialize() {
	obj.Clear();
}





NAMESPACE_SERIAL_END
