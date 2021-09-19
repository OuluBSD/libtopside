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
	double time_delta = fwd.Cfg().time_delta;
	frame_age += time_delta;
	
	RTLOG("SDL2SwScreenBase::AltForward: time_delta: " << time_delta << ", frame_age: " << frame_age);
}

void SDL2SwScreenBase::AltStorePacket(Packet& p) {
	if (frame_age >= dt) {
		RTLOG("SDL2SwScreenBase::AltStorePacket: render");
		if (frame_age >= 2 * dt)
			frame_age = 0;
		else
			frame_age -= dt;
		obj->Render();
	}
}


#endif



NAMESPACE_SERIAL_END
