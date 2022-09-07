#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



void SDL2JoystickComponent::Initialize() {
	OBJ_CREATE
}

void SDL2JoystickComponent::Uninitialize() {
	obj.Clear();
}

/*void SDL2JoystickComponent::EmitController(double dt) {
	TODO
}*/



NAMESPACE_TOPSIDE_END
