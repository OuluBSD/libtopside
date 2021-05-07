#include "EcsLib.h"

#ifdef flagVIRTUALGUI3DALT
#include <VirtualGui3DAlt/VirtualGuiAlt.h>
#endif


NAMESPACE_OULU_BEGIN



bool EventSystem::Initialize() {
	return true;
}

void EventSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void EventSystem::Update(double dt) {
	for (ControllerSource* out : outputs)
		out->EmitController(dt);
	for (MidiSource* out : midis)
		out->EmitMidi(dt);
}

void EventSystem::Stop() {
	
}

void EventSystem::Uninitialize() {
	
	//Close();
	
}

void EventSystem::Add(ControllerSource* out) {
	VectorFindAdd(outputs, out);
}

void EventSystem::Remove(ControllerSource* out) {
	VectorRemoveKey(outputs, out);
}

void EventSystem::Add(MidiSource* out) {
	VectorFindAdd(midis, out);
}

void EventSystem::Remove(MidiSource* out) {
	VectorRemoveKey(midis, out);
}


NAMESPACE_OULU_END
