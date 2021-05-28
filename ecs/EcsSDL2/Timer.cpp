#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



void SDL2TimerComponent::Initialize() {
	OBJ_CREATE
}

void SDL2TimerComponent::Uninitialize() {
	obj.Clear();
}



NAMESPACE_TOPSIDE_END
