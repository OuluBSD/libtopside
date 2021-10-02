#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2AudioInputBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	return true;
}

void SDL2AudioInputBase::Uninitialize() {
	obj.Clear();
}



NAMESPACE_SERIAL_END
