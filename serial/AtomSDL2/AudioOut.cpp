#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2AudioOutputBase::AltInitialize(const Script::WorldState& ws) {
	aconfig.frames_after_sync = 0;
	SetAudioSyncInterval(15);
	OBJ_CREATE
	GetSink()->GetValue(0).SetMinQueueSize(10);
	return true;
}

bool SDL2AudioOutputBase::AltPostInitialize() {
	DLOG("SDL2AudioOutputBase::AltPostInitialize");
	return true;
}

void SDL2AudioOutputBase::AltUninitialize() {
	obj.Clear();
}

void SDL2AudioOutputBase::AltForward(FwdScope& fwd) {
	// pass
}

bool SDL2AudioOutputBase::PassLoadPacket(int ch_i, const Packet& p) {
	Format fmt = p->GetFormat();
	return fmt.vd.val == ValCls::AUDIO;
}


NAMESPACE_SERIAL_END
