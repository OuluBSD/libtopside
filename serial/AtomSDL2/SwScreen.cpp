#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI

bool SDL2SwScreenBase::AltInitialize(const Script::WorldState& ws) {
	fps = 60;
	dt = 1.0 / (double)fps;
	SetFPS(fps);
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
	if (frame_age >= dt) {
		RTLOG("SDL2SwScreenBase::AltForward: render");
		if (frame_age >= 2 * dt)
			frame_age = 0;
		else
			frame_age -= dt;
		obj->Render();
	}
}



#if 0

DisplayFormat SDL2SwScreenBase::GetFormat(DisCtx) {
	TODO
}

Display& SDL2SwScreenBase::GetValue(DisCtx) {
	TODO
}

void SDL2SwScreenBase::SetTitle(String s) {
	if (obj)
		obj->SetTitle(s);
}
	
void SDL2SwScreenBase::RecvDisplay(DisplaySource& src, double dt) {
	frame_age += dt;
	this->dt += dt;
	
	if (frame_age >= config.fps_dt) {
		if (frame_age > 2 * config.fps_dt)
			frame_age = config.fps_dt;
		else
			frame_age = Modulus(frame_age, config.fps_dt);
		
		
		SystemDraw& draw = obj->BeginDraw();
		
		if (!src.Render(config, draw))
			frame_age = config.fps_dt; // force redraw
		
		obj->CommitDraw();
	}
}
#endif

#endif



NAMESPACE_SERIAL_END
