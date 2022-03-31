#include "IHal.h"

#if defined flagSDL2

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

NAMESPACE_PARALLEL_BEGIN

bool HalSdl2::AudioSinkDevice_Initialize(NativeAudioSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
	/*OBJ_CREATE
	SetPrimarySinkQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	return true;*/
}

bool HalSdl2::AudioSinkDevice_PostInitialize(NativeAudioSinkDevice& dev) {
	TODO
	/*DLOG("SDL2AudioOutputBase::PostInitialize");
	return true;*/
}

bool HalSdl2::AudioSinkDevice_Start(NativeAudioSinkDevice& dev) {
	TODO
}

void HalSdl2::AudioSinkDevice_Stop(NativeAudioSinkDevice& dev) {
	TODO
}

void HalSdl2::AudioSinkDevice_Uninitialize(NativeAudioSinkDevice& dev) {
	TODO
	//obj.Clear();
}

bool HalSdl2::AudioSinkDevice_ProcessPacket(NativeAudioSinkDevice& dev, PacketValue& v) {
	TODO
}





bool HalSdl2::ContextBase_Initialize(NativeContextBase& ctx, AtomBase& a, const Script::WorldState& ws) {
	DLOG("HalSdl2::ContextBase_Initialize");
	return true;
}

bool HalSdl2::ContextBase_PostInitialize(NativeContextBase& ctx) {
	DLOG("HalSdl2::ContextBase_PostInitialize");
	
	TODO
	
	#if 0
	
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
	
	#endif
	
	return true;
}

bool HalSdl2::ContextBase_Start(NativeContextBase& ctx) {
	TODO
}

void HalSdl2::ContextBase_Stop(NativeContextBase& ctx) {
	TODO
}

void HalSdl2::ContextBase_Uninitialize(NativeContextBase& ctx) {
	/*obj->CloseComponents();
	obj->Close();*/
	TODO
}

bool HalSdl2::ContextBase_ProcessPacket(NativeContextBase& ctx, PacketValue& v) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

