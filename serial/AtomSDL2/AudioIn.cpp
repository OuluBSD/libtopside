#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



bool SDL2AudioInputBase::AltInitialize(const Script::WorldState& ws) {
	OBJ_CREATE
	return true;
}

void SDL2AudioInputBase::AltUninitialize() {
	obj.Clear();
}

/*AudioStream& SDL2AudioInputBase::GetStream(AudCtx) {
	TODO
}

void SDL2AudioInputBase::BeginStream(AudCtx) {
	TODO
}

void SDL2AudioInputBase::EndStream(AudCtx) {
	TODO
}
*/


NAMESPACE_SERIAL_END
