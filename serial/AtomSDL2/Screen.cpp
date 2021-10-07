#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI


bool SDL2ScreenBase::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	
	OglBuffer& buf = GetBuffer();
	obj->SetShaderFile(ws.Get(".filepath"));
	obj->SetTestImage(ws.Get(".testimage") == "true");
	obj->SetBuffer(buf);
	
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
	GetSink()->GetValue(0).SetMaxQueueSize(1);
	return true;
}

void SDL2ScreenBase::Uninitialize() {
	ev = 0;
	obj.Clear();
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
}

bool SDL2ScreenBase::LoadPacket(int sink_ch, const Packet& p) {
	RTLOG("SDL2ScreenBase::LoadPacket: sink #" << sink_ch << " " << p->ToString());
	return obj->Recv(sink_ch, p);
}

void SDL2ScreenBase::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("SDL2ScreenBase::StorePacket: " << sink_ch << ", " << src_ch << ": " << p->ToString());
	if (sink_ch == 0 && src_ch == 0) {
		obj->Render(*last_cfg);
	}
	
	#if 0
	Format fmt = p->GetFormat();
	if (fmt.vd == VD(OGL,FBO)) {
		PacketValue& val = *p;
		InternalPacketData& data = val.GetData<InternalPacketData>();
		GetBuffer().StoreOutputLink(data);
	}
	#endif
}


#endif



NAMESPACE_SERIAL_END
