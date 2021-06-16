#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



void SDL2AudioOutputComponent::Initialize() {
	aconfig.frames_after_sync = 0;
	SetAudioSyncInterval(15);
	OBJ_CREATE
}

void SDL2AudioOutputComponent::Uninitialize() {
	obj.Clear();
}

AudioFormat SDL2AudioOutputComponent::GetFormat(AudCtx) {
	TODO
}

Audio& SDL2AudioOutputComponent::GetValue(AudCtx) {
	return obj->GetAudio();
}

void SDL2AudioOutputComponent::Forward(FwdScope& fwd) {
	TODO
}

void SDL2AudioOutputComponent::ForwardExchange(FwdScope& fwd) {
	TODO
}


NAMESPACE_TOPSIDE_END
