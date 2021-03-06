#include "AtomSDL2.h"


NAMESPACE_SERIAL_BEGIN



SDL2ContextBase::SDL2ContextBase() {
	obj.Create();
	
	
}

void SDL2ContextBase::Add(AtomBaseRef sdlbase) {
	RefT_Loop<SDL2Base> base = sdlbase;
	ASSERT(base);
	atoms.Add(sdlbase);
}

bool SDL2ContextBase::Initialize(const Script::WorldState& ws) {
	DLOG("SDL2ContextBase::Initialize");
	return true;
}

bool SDL2ContextBase::PostInitialize() {
	DLOG("SDL2ContextBase::PostInitialize");
	LoopRef l = GetLoop();
	
	#if 0
	auto tim		= l->FindCast<SDL2TimerBase>();
	auto ain		= l->FindCast<SDL2AudioInputBase>();
	auto aout		= l->FindCast<SDL2AudioOutputBase>();
	#ifdef flagSCREEN
	auto scr		= l->FindCast<SDL2ScreenBase>();
	#endif
	auto ev			= l->FindCast<SDL2EventsBase>();
	auto joy		= l->FindCast<SDL2JoystickBase>();
	auto gc			= l->FindCast<SDL2GameControllerBase>();
	auto sens		= l->FindCast<SDL2SensorBase>();
	#endif
	
	if (atoms.IsEmpty()) {
		LOG("SDL2ContextBase::Initialize: error: no sdl2 components added to SDL2ContextBase");
		return false;
	}
	
	for (AtomBaseRef& ab : atoms) {
		RefT_Loop<SDL2Base> base = ab;
		if (base)
			obj->Add(base->GetObj());
	}
	
	
	if (!obj->Open()) {
		LOG("SDL2ContextBase::Initialize: error: " << obj->GetLastError());
		GetMachine().SetNotRunning();
	}
	
	
	return true;
}

void SDL2ContextBase::Uninitialize() {
	obj->CloseComponents();
	obj->Close();
}

void SDL2ContextBase::Forward(FwdScope& fwd) {
	RTLOG("SDL2ContextBase::Forward");
}





NAMESPACE_SERIAL_END

