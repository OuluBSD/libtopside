#include "EcsLib.h"


NAMESPACE_OULU_BEGIN

Callback AudioSystem::WhenUninit;

bool AudioSystem::Initialize() {
	
	
	return true;
}

void AudioSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void AudioSystem::Update(double dt) {
	for(AudioSource* aud : srcs) {
		aud->EmitAudioSource(dt);
	}
}

void AudioSystem::Stop() {
	
	
}

void AudioSystem::Uninitialize() {
	
	WhenUninit();
}

void AudioSystem::Add(AudioSource* src) {
	VectorFindAdd(srcs, src);
}

void AudioSystem::Remove(AudioSource* src) {
	VectorRemoveKey(srcs, src);
}

void AudioSystem::Add(AudioSink* sink) {
	VectorFindAdd(sinks, sink);
}

void AudioSystem::Remove(AudioSink* sink) {
	VectorRemoveKey(sinks, sink);
}


NAMESPACE_OULU_END
