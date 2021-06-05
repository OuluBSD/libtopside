#include "EcsAudioCore.h"


NAMESPACE_TOPSIDE_BEGIN


DummySoundGeneratorAudio::DummySoundGeneratorAudio() {
	fmt.channels = 2;
	fmt.sample_rate = 777;
	fmt.freq = 44100;
	fmt.SetType(SoundSample::U8_LE);
	gen.GenerateStereoSine(fmt);
}

void DummySoundGeneratorAudio::Exchange(AudioEx& e) {
	if (e.IsStoring()) {
		Audio& sink = e.Sink();
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		AudioVolatileBuffer* vol_aud = CastPtr<AudioVolatileBuffer>(&sink);
		if (vol_aud) {
			while (!vol_aud->IsQueueFull()) {
				AudioPacket p = CreateAudioPacket();
				AudioPacketTracker::Track(TrackerInfo(this, __FILE__, __LINE__), p);
				p->Set(fmt, offset, time);
				p->Data().SetCount(fmt.GetFrameSize(), 0);
				gen.Play(p);
				vol_aud->Put(p, false);
				++offset;
				time += fmt.GetFrameSeconds();
			}
		}
		else TODO
	}
	else TODO
}

int DummySoundGeneratorAudio::GetQueueSize() const {
	return 10;
}

AudioFormat DummySoundGeneratorAudio::GetFormat() const {
	return fmt;
}

bool DummySoundGeneratorAudio::IsQueueFull() const {
	return true;
}














SoundGeneratorComponent::SoundGeneratorComponent() {
	
}

void SoundGeneratorComponent::Initialize() {
	Component::Initialize();
	//AddToContext<CenterSpec>(AsRef<CenterSource>());
	
}

void SoundGeneratorComponent::Uninitialize() {
	Component::Uninitialize();
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSource>());
}

#if 0

void SoundGeneratorComponent::RecvMidi(const MidiFrame& e) {
	TODO
}

void SoundGeneratorComponent::Configure(const Midi::File& file) {
	if (mode == MODE_TRACK_NUM) {
		if (track_i >= 0 && track_i < file.GetTrackCount()) {
			Ref<FluidsynthSystem> fs_sys = GetMachine().Get<FluidsynthSystem>();
			fs_sys->Assign(file, track_i, this);
		}
	}
}

#endif

AudioStream& SoundGeneratorComponent::GetStream(AudCtx) {
	return gen;
}

void SoundGeneratorComponent::BeginStream(AudCtx) {
	
}

void SoundGeneratorComponent::EndStream(AudCtx) {
	
}





NAMESPACE_TOPSIDE_END
