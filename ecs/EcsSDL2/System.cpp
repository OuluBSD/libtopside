#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



bool SDL2System::Initialize() {
	return img.Open() && fnt.Open();
}

void SDL2System::Start() {
	
}

void SDL2System::Update(double dt) {
	
}

void SDL2System::Stop() {
	
}

void SDL2System::Uninitialize() {
	img.Close();
	fnt.Close();
}

void SDL2System::AddContext(SDL2ContextConnectorRef comp) {
	comps.FindAdd(comp);
}

void SDL2System::RemoveContext(SDL2ContextConnectorRef comp) {
	comps.RemoveKey(comp);
}


NAMESPACE_TOPSIDE_END
