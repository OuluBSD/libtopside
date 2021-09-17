#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI

bool SDL2ScreenBase::AltInitialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	return true;
}

void SDL2ScreenBase::AltUninitialize() {
	ev = 0;
	obj.Clear();
}

void SDL2ScreenBase::AltForward(FwdScope& fwd) {
	double time_delta = fwd.Cfg().time_delta;
	frame_age += time_delta;
	RTLOG("SDL2ScreenBase::AltForward: time_delta: " << time_delta << ", frame_age: " << frame_age);
	if (frame_age >= dt) {
		RTLOG("SDL2KopScreenBase::AltForward: render");
		if (frame_age >= 2 * dt)
			frame_age = 0;
		else
			frame_age -= dt;
		obj->Render();
	}
}



#endif



NAMESPACE_SERIAL_END
