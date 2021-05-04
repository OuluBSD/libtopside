#include "EcsCore.h"


NAMESPACE_OULU_BEGIN

Callback AudioSystem::WhenUninit;

bool AudioSystem::Initialize() {
	
	
	return true;
}

void AudioSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void AudioSystem::Update(double dt) {
	
	for (AudioSourceRef src : srcs) {
		AudioStream& stream = src->GetAudioSource();
		bool buffer_full = stream.GetAudioBufferSize() >= 2;
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_AUDIO_PIPE
			LOG("AUDIO DEBUG: begin source " << HexStr(&*src) << src->GetConfigString() << "> render");
			#endif
			
			src->BeginAudioSource();
		}
	}
	
	for (AudioExchangePointRef expt : expts) {
		AudioSourceRef src = expt->Source();
		
		expt->Update(dt);
		if (expt->AnySinkConsumed()) {
			#if DEBUG_AUDIO_PIPE
			auto sink = expt->Sink();
			LOG("AUDIO DEBUG: sink consumed " << HexStr(&*sink) << sink->GetConfigString() << ">");
			#endif
			
			src->SetConsumed();
		}
	}
	
	for (AudioSourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.any_consumed) {
			#if DEBUG_AUDIO_PIPE
			LOG("AUDIO DEBUG: end source " << HexStr(&*src) << src->GetConfigString() << "> render");
			#endif
			
			src->EndAudioSource(cfg.any_consumed);
		}
	}
	
}

void AudioSystem::Stop() {
	
	
}

void AudioSystem::Uninitialize() {
	
	WhenUninit();
}

void AudioSystem::Add(AudioSourceRef src) {
	VectorFindAdd(srcs, src);
}

void AudioSystem::Remove(AudioSourceRef src) {
	VectorRemoveKey(srcs, src);
}

void AudioSystem::Add(AudioSinkRef sink) {
	VectorFindAdd(sinks, sink);
}

void AudioSystem::Remove(AudioSinkRef sink) {
	VectorRemoveKey(sinks, sink);
}

void AudioSystem::Add(AudioExchangePointRef expt) {
	VectorFindAdd(expts, expt);
}

void AudioSystem::Remove(AudioExchangePointRef expt) {
	VectorRemoveKey(expts, expt);
}








NAMESPACE_OULU_END
