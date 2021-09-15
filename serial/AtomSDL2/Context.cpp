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

bool SDL2ContextBase::AltInitialize(const Script::WorldState& ws) {
	DLOG("SDL2ContextBase::AltInitialize");
	return true;
}

bool SDL2ContextBase::AltPostInitialize() {
	DLOG("SDL2ContextBase::AltPostInitialize");
	LoopRef l = GetLoop();
	
	#if 0
	auto tim		= l->FindCast<SDL2TimerBase>();
	auto ain		= l->FindCast<SDL2AudioInputBase>();
	auto aout		= l->FindCast<SDL2AudioOutputBase>();
	#ifdef flagGUI
	auto scr		= l->FindCast<SDL2ScreenBase>();
	#endif
	auto ev			= l->FindCast<SDL2EventsBase>();
	auto joy		= l->FindCast<SDL2JoystickBase>();
	auto gc			= l->FindCast<SDL2GameControllerBase>();
	auto sens		= l->FindCast<SDL2SensorBase>();
	#endif
	
	if (atoms.IsEmpty()) {
		LOG("SDL2ContextBase::AltInitialize: error: no sdl2 components added to SDL2ContextBase");
		return false;
	}
	
	for (AtomBaseRef& ab : atoms) {
		RefT_Loop<SDL2Base> base = ab;
		if (base)
			obj->Add(base->GetObj());
	}
	
	
	if (!obj->Open()) {
		LOG("SDL2ContextBase::AltInitialize: error: " << obj->GetLastError());
		GetMachine().SetNotRunning();
	}
	
	
	return true;
}

void SDL2ContextBase::AltUninitialize() {
	obj->Close();
}

void SDL2ContextBase::AltForward(FwdScope& fwd) {
	RTLOG("SDL2ContextBase::AltForward");
}



NAMESPACE_SERIAL_END

