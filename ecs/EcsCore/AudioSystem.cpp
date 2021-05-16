#include "EcsCore.h"


NAMESPACE_TOPSIDE_BEGIN

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
		
		#if 0 && DEBUG_AUDIO_PIPE
		AUDIOLOG("update source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
		#endif
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_AUDIO_PIPE
			AUDIOLOG("begin source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->BeginAudioSource();
		}
	}
	
	for (AudioExchangePointRef expt : expts) {
		AudioSourceRef src = expt->Source();
		off32 begin_offset = expt->GetOffset();
		
		#if 0 && DEBUG_AUDIO_PIPE
		AUDIOLOG("expt updpate " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		expt->SetOffset(begin_offset);
		expt->Update(dt);
		
		off32 end_offset = expt->GetOffset();
		src->SetOffset(begin_offset, end_offset);
		
		#if DEBUG_AUDIO_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			auto sink = expt->Sink();
			AUDIOLOG("sink " << HexStr((size_t)&*sink) << "<" << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
	}
	
	for (AudioSourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_AUDIO_PIPE
			AUDIOLOG("end source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->EndAudioSource();
		}
	}
	
}

void AudioSystem::Stop() {
	
	
}

void AudioSystem::Uninitialize() {
	srcs.Clear();
	sinks.Clear();
	expts.Clear();
	
	WhenUninit();
}

void AudioSystem::Add(AudioSourceRef src) {
	ASSERT(src);
	srcs.FindAdd(src);
}

void AudioSystem::Remove(AudioSourceRef src) {
	srcs.RemoveKey(src);
}

void AudioSystem::Add(AudioSinkRef sink) {
	ASSERT(sink);
	sinks.FindAdd(sink);
}

void AudioSystem::Remove(AudioSinkRef sink) {
	sinks.RemoveKey(sink);
}

void AudioSystem::Add(AudioExchangePointRef expt) {
	ASSERT(expt);
	expts.FindAdd(expt);
}

void AudioSystem::Remove(AudioExchangePointRef expt) {
	expts.RemoveKey(expt);
}








NAMESPACE_TOPSIDE_END
