#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2AudioOutputBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	GetSink()->GetValue(0).SetMinQueueSize(10);
	return true;
}

bool SDL2AudioOutputBase::PostInitialize() {
	DLOG("SDL2AudioOutputBase::PostInitialize");
	return true;
}

void SDL2AudioOutputBase::Uninitialize() {
	obj.Clear();
}

bool SDL2AudioOutputBase::PassLoadPacket(int ch_i, const Packet& p) {
	Format fmt = p->GetFormat();
	return fmt.vd.val == ValCls::AUDIO;
}


NAMESPACE_SERIAL_END
