#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



SDL2ContextComponent::SDL2ContextComponent() {
	obj.Create();
	
	
}

void SDL2ContextComponent::Initialize() {
	DLOG("SDL2ContextComponent::Initialize");
	EntityRef e = GetEntity();
	
	Ref<SDL2System> sdl2_sys = e->GetMachine().Get<SDL2System>();
	if (sdl2_sys)
		sdl2_sys->AddContext(*this);
	
	auto tim		= e->Find<SDL2TimerComponent>();
	auto ain		= e->Find<SDL2AudioInputComponent>();
	auto aout		= e->Find<SDL2AudioOutputComponent>();
#ifdef flagGUI
	auto scr		= e->Find<SDL2ScreenComponent>();
#endif
	
	auto ev			= e->Find<SDL2EventsComponent>();
	auto joy		= e->Find<SDL2JoystickComponent>();
	auto gc			= e->Find<SDL2GameControllerComponent>();
	auto sens		= e->Find<SDL2SensorComponent>();
	
	#define AddObj(x) if(x) {obj->Add(x->GetObj()); comps.Add(x);}
	
	AddObj(tim);
	AddObj(ain);
	AddObj(aout);
#ifdef flagGUI
	AddObj(scr);
#endif
	
	AddObj(ev);
	AddObj(joy);
	AddObj(gc);
	AddObj(sens);
	
	#undef AddObj
	
	if (!obj->Open()) {
		LOG("SDL2ContextComponent::Initialize: error: " << obj->GetLastError());
		GetMachine().SetNotRunning();
	}
}

void SDL2ContextComponent::Uninitialize() {
	Ref<SDL2System> sdl2_sys = GetEntity()->GetMachine().Get<SDL2System>();
	if (sdl2_sys)
		sdl2_sys	-> RemoveContext(*this);
	
	obj->Close();
}



NAMESPACE_TOPSIDE_END
