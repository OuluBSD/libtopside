#include "EcsLib.h"




NAMESPACE_TOPSIDE_BEGIN



bool EventSystem::Initialize() {
	return true;
}

void EventSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void EventSystem::Update(double dt) {
	for (ControllerSourceRef& out : outputs)
		out->EmitController(dt);
	for (MidiSourceRef& out : midis)
		out->EmitMidi(dt);
}

void EventSystem::Stop() {
	
}

void EventSystem::Uninitialize() {
	
	//Close();
	
}

void EventSystem::Add(ControllerSourceRef out) {
	ASSERT(out);
	outputs.FindAdd(out);
}

void EventSystem::Remove(ControllerSourceRef out) {
	ASSERT(out);
	outputs.RemoveKey(out);
}

void EventSystem::Add(MidiSourceRef out) {
	ASSERT(out);
	midis.FindAdd(out);
}

void EventSystem::Remove(MidiSourceRef out) {
	ASSERT(out);
	midis.RemoveKey(out);
}


NAMESPACE_TOPSIDE_END
