#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI


bool SDL2ScreenBase::AltInitialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	
	obj->SetShaderFile(ws.Get(".filepath"));
	obj->SetTestImage(ws.Get(".testimage") == "true");
	
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
	return true;
}

void SDL2ScreenBase::AltUninitialize() {
	ev = 0;
	obj.Clear();
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
}

void SDL2ScreenBase::AltUpdate(double dt) {
	frame_age += dt;
	RTLOG("SDL2ScreenBase::AltUpdate: dt: " << dt << ", frame_age: " << frame_age);
}

void SDL2ScreenBase::AltForward(FwdScope& fwd) {
	const int sink_ch_i = 0;
	
	PacketBuffer& sink_buf = this->GetSink()->GetValue(sink_ch_i).GetBuffer();
	if (sink_buf.IsEmpty()) return;
	
	RTLOG("SDL2ScreenBase::AltForward: frame_age: " << frame_age);
	
	if (frame_age >= dt) {
		RTLOG("SDL2ScreenBase::AltForward: render");
		if (frame_age >= 2 * dt)
			frame_age = 0;
		else
			frame_age -= dt;
		
		while (sink_buf.GetCount()) {
			Packet p = sink_buf.First();
			sink_buf.RemoveFirst();
			PacketConsumed(p);
			if (obj->Recv(p))
				break;
		}
		
		//PostContinueForward();
	}
	else {
		RTLOG("SDL2ScreenBase::AltForward: wait");
	}
}

void SDL2ScreenBase::AltStorePacket(Packet& p) {
	RTLOG("SDL2ScreenBase::AltStorePacket");
	obj->Render(*last_cfg);
}


#endif



NAMESPACE_SERIAL_END
