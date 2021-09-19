#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI


bool SDL2SwScreenBase::AltInitialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	return true;
}

void SDL2SwScreenBase::AltUninitialize() {
	ev = 0;
	obj.Clear();
}

void SDL2SwScreenBase::AltForward(FwdScope& fwd) {
	PacketBuffer& sink_buf = this->GetSink()->GetValue().GetBuffer();
	ASSERT(!sink_buf.IsEmpty());
	if (sink_buf.IsEmpty()) return;
	
	double time_delta = fwd.Cfg().time_delta;
	frame_age += time_delta;
	
	RTLOG("SDL2SwScreenBase::AltForward: time_delta: " << time_delta << ", frame_age: " << frame_age);
	
	if (frame_age >= dt) {
		RTLOG("SDL2SwScreenBase::AltStorePacket: render");
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
		
		PostContinueForward();
	}
}

void SDL2SwScreenBase::AltStorePacket(Packet& p) {
	obj->Render();
}


#endif



NAMESPACE_SERIAL_END
