#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



void SDL2AudioInputComponent::Initialize() {
	OBJ_CREATE
}

void SDL2AudioInputComponent::Uninitialize() {
	obj.Clear();
}

AudioStream& SDL2AudioInputComponent::GetStream(AudCtx) {
	TODO
}

void SDL2AudioInputComponent::BeginStream(AudCtx) {
	TODO
}

void SDL2AudioInputComponent::EndStream(AudCtx) {
	TODO
}



NAMESPACE_TOPSIDE_END
