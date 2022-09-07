#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



void SDL2SensorComponent::Initialize() {
	OBJ_CREATE
}

void SDL2SensorComponent::Uninitialize() {
	obj.Clear();
}

/*void SDL2SensorComponent::EmitController(double dt) {
	TODO
}*/



NAMESPACE_TOPSIDE_END
