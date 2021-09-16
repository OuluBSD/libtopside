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

/*AudioFormat SDL2AudioOutputBase::GetFormat(AudCtx) {
	TODO
}

Audio& SDL2AudioOutputBase::GetValue(AudCtx) {
	return obj->GetAudio();
}*/

void SDL2AudioOutputBase::AltForward(FwdScope& fwd) {
	
}

/*void SDL2AudioOutputBase::AltForwardExchange(FwdScope& fwd) {
	TODO
}*/

void SDL2AudioOutputBase::AltStorePacket(Packet& p) {
	TODO
}


NAMESPACE_SERIAL_END
