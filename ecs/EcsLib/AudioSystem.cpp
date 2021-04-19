#include "EcsLib.h"


NAMESPACE_OULU_BEGIN


bool AudioSystem::Initialize() {
	
	
	return true;
}

void AudioSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void AudioSystem::Update(float dt) {
	for(AudioSource* aud : audios) {
		aud->EmitAudioSource(dt);
	}
}

void AudioSystem::Stop() {
	
	
}

void AudioSystem::Uninitialize() {
	
	
}

void AudioSystem::AddAudioSource(AudioSource& src) {
	VectorFindAdd(audios, &src);
}

void AudioSystem::RemoveAudioSource(AudioSource& src) {
	VectorRemoveKey(audios, &src);
}


NAMESPACE_OULU_END
