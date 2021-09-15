#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



bool SDL2SensorBase::AltInitialize(const Script::WorldState& ws) {
	OBJ_CREATE
	return true;
}

void SDL2SensorBase::AltUninitialize() {
	obj.Clear();
}





NAMESPACE_SERIAL_END
