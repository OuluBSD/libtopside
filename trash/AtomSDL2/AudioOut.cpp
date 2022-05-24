#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2AudioOutputBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	SetPrimarySinkQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	return true;
}

bool SDL2AudioOutputBase::PostInitialize() {
	DLOG("SDL2AudioOutputBase::PostInitialize");
	return true;
}

void SDL2AudioOutputBase::Uninitialize() {
	obj.Clear();
}

bool SDL2AudioOutputBase::PassConsumePacket(int sink_ch, const Packet& in) {
	Format fmt = in->GetFormat();
	return fmt.vd.val == ValCls::AUDIO;
}


NAMESPACE_SERIAL_END
