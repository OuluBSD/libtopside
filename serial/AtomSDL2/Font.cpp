#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



bool SDL2FontBase::AltInitialize(const Script::WorldState& ws) {
	
	return true;
}

void SDL2FontBase::AltUninitialize() {
	fnt.Clear();
}





NAMESPACE_SERIAL_END
