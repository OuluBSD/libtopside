#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



bool SDL2GameControllerBase::AltInitialize(const Script::WorldState& ws) {
	OBJ_CREATE
	return true;
}

void SDL2GameControllerBase::AltUninitialize() {
	obj.Clear();
}





NAMESPACE_SERIAL_END
