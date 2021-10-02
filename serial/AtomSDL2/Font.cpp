#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



bool SDL2FontBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void SDL2FontBase::Uninitialize() {
	fnt.Clear();
}





NAMESPACE_SERIAL_END
