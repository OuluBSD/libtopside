#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2TimerBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	return true;
}

void SDL2TimerBase::Uninitialize() {
	obj.Clear();
}


NAMESPACE_SERIAL_END
