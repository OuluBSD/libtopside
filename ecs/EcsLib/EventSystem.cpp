#include "EcsLib.h"

#ifdef flagVIRTUALGUI3DALT
#include <VirtualGui3DAlt/VirtualGuiAlt.h>
#endif


NAMESPACE_OULU_BEGIN


EventSystem::EventSystem(Machine& m) : System<EventSystem>(m) {
	
}

bool EventSystem::Initialize() {
	return true;
}

void EventSystem::Start() {
	ents = machine.Get<EntityStore>();
}

void EventSystem::Update(float dt) {
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

void EventSystem::AddControllable(ControllerSource& out) {
	VectorFindAdd(outputs, &out);
}

void EventSystem::RemoveControllable(ControllerSource& out) {
	VectorRemoveKey(outputs, &out);
}

void EventSystem::AddMidi(MidiSource& out) {
	VectorFindAdd(midis, &out);
}

void EventSystem::RemoveMidi(MidiSource& out) {
	VectorRemoveKey(midis, &out);
}


NAMESPACE_OULU_END
