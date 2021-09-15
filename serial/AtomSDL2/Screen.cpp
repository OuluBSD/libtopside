#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI

bool SDL2ScreenBase::AltInitialize(const Script::WorldState& ws) {
	dt = 0;
	SetFPS(60);
	OBJ_CREATE
	return true;
}

void SDL2ScreenBase::AltUninitialize() {
	ev = 0;
	obj.Clear();
}

#if 0

DisplayFormat SDL2ScreenBase::GetFormat(DisCtx) {
	TODO
}

Display& SDL2ScreenBase::GetValue(DisCtx) {
	TODO
}

void SDL2ScreenBase::SetTitle(String s) {
	if (obj)
		obj->SetTitle(s);
}
	
void SDL2ScreenBase::RecvDisplay(DisplaySource& src, double dt) {
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
