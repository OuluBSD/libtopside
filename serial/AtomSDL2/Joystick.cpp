#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



bool SDL2JoystickBase::AltInitialize(const Script::WorldState& ws) {
	OBJ_CREATE
	return true;
}

void SDL2JoystickBase::AltUninitialize() {
	obj.Clear();
}





NAMESPACE_SERIAL_END
