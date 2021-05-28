#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



#ifdef flagGUI

void SDL2ScreenComponent::Initialize() {
	dt = 0;
	SetFPS(60);
	OBJ_CREATE
	auto ev_comp = GetEntity()->Find<SDL2EventsComponent>();
	if (ev_comp)
		ev = ev_comp->GetOOSDL2();
}

void SDL2ScreenComponent::Uninitialize() {
	ev = 0;
	obj.Clear();
}

DisplayFormat SDL2ScreenComponent::GetFormat(DisCtx) {
	TODO
}

Display& SDL2ScreenComponent::GetValue(DisCtx) {
	TODO
}

#if 0

void SDL2ScreenComponent::SetTitle(String s) {
	if (obj)
		obj->SetTitle(s);
}
	
void SDL2ScreenComponent::RecvDisplay(DisplaySource& src, double dt) {
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



NAMESPACE_TOPSIDE_END
