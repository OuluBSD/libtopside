#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


#ifdef flagGUI


bool SDL2SwScreenBase::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
	GetSink()->GetValue(0).SetMaxQueueSize(1);
	return true;
}

void SDL2SwScreenBase::Uninitialize() {
	ev = 0;
	obj.Clear();
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
}

bool SDL2SwScreenBase::LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) {
	RTLOG("SDL2SwScreenBase::LoadPacket: sink #" << sink_ch << " " << in->ToString());
	return obj->Recv(sink_ch, in);
}

void SDL2SwScreenBase::StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) {
	RTLOG("SDL2SwScreenBase::StorePacket: " << sink_ch << ", " << src_ch << ": in=" << in->ToString());
	obj->Render();
}


#endif


NAMESPACE_SERIAL_END
