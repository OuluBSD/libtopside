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
		int buf_sz = stream.GetAudio().GetQueueSize();
		bool buffer_full = buf_sz >= 2;
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_AUDIO_PIPE
			LOG("AUDIO DEBUG: begin source " << HexStr((size_t)&*src) << src->GetConfigString() << ">");
			#endif
			
			src->BeginAudioSource();
		}
	}
	
	for (AudioExchangePointRef expt : expts) {
		AudioSourceRef src = expt->Source();
		off32 begin_offset = expt->GetOffset();
		
		expt->SetOffset(begin_offset);
		expt->Update(dt);
		
		off32 end_offset = expt->GetOffset();
		src->SetOffset(begin_offset, end_offset);
		
		#if DEBUG_AUDIO_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			auto sink = expt->Sink();
			LOG("AUDIO DEBUG: sink " << HexStr((size_t)&*sink) << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
	}
	
	for (AudioSourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_AUDIO_PIPE
			LOG("AUDIO DEBUG: end source " << HexStr((size_t)&*src) << src->GetConfigString() << ">");
			#endif
			
			src->EndAudioSource();
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
