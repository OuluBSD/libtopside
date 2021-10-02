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

void SDL2SwScreenBase::Forward(FwdScope& fwd) {
	
}


/*bool SDL2SwScreenBase::PassLoadPacket(int ch_i, const Packet& p) {
	Format fmt = p->GetFormat();
	return fmt.vd.val == ValCls::VIDEO;
}*/

bool SDL2SwScreenBase::LoadPacket(int sink_ch_i, const Packet& p) {
	RTLOG("SDL2SwScreenBase::LoadPacket: sink #" << sink_ch_i << " " << p->ToString());
	return obj->Recv(sink_ch_i, p);
}

void SDL2SwScreenBase::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("SDL2SwScreenBase::StorePacket: " << sink_ch << ", " << src_ch << ": " << p->ToString());
	obj->Render();
}


#endif



NAMESPACE_SERIAL_END
