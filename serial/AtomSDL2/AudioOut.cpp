#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2AudioOutputBase::AltInitialize(const Script::WorldState& ws) {
	aconfig.frames_after_sync = 0;
	SetAudioSyncInterval(15);
	OBJ_CREATE
	return true;
}

void SDL2AudioOutputBase::AltUninitialize() {
	obj.Clear();
}

void SDL2AudioOutputBase::AltForward(FwdScope& fwd) {
	// pass
}

void SDL2AudioOutputBase::AltStorePacket(Packet& p) {
	// pass
}


NAMESPACE_SERIAL_END
