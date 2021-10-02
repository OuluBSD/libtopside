#include "AtomSDL2.h"

#if 0

NAMESPACE_SERIAL_BEGIN



bool SDL2System::Initialize(const Script::WorldState& ws) {
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

void SDL2System::AddContext(AtomBaseRef comp) {
	atoms.FindAdd(comp);
}

void SDL2System::RemoveContext(AtomBaseRef comp) {
	atoms.RemoveKey(comp);
}


NAMESPACE_SERIAL_END

#endif
