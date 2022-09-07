#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



void SDL2GameControllerComponent::Initialize() {
	OBJ_CREATE
}

void SDL2GameControllerComponent::Uninitialize() {
	obj.Clear();
}

/*void SDL2GameControllerComponent::EmitController(double dt) {
	TODO
}*/



NAMESPACE_TOPSIDE_END
