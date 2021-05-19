#include "AudioCore.h"
#include "System.h"


NAMESPACE_TOPSIDE_BEGIN


DummySoundGeneratorAudio::DummySoundGeneratorAudio() {
	fmt.channels = 2;
	fmt.sample_rate = 777;
	fmt.freq = 44100;
	fmt.is_var_bigendian = false;
	fmt.is_var_float = 0;
	fmt.is_var_signed = 0;
	fmt.var_size = 1;
	gen.GenerateStereoSine(fmt);
}

void DummySoundGeneratorAudio::Exchange(AudioEx& e) {
	if (e.IsStoring()) {
		Audio& sink = e.Sink();
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		AudioVolatileBuffer* vol_aud = dynamic_cast<AudioVolatileBuffer*>(&sink);
		if (vol_aud) {
			while (!vol_aud->IsQueueFull()) {
				AudioPacket p = CreateAudioPacket();
				p->Set(fmt, offset, time);
				p->Data().SetCount(fmt.GetFrameBytes(), 0);
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

AudioFormat DummySoundGeneratorAudio::GetAudioFormat() const {
	return fmt;
}

bool DummySoundGeneratorAudio::IsQueueFull() const {
	return true;
}














SoundGeneratorComponent::SoundGeneratorComponent() {
	
}

void SoundGeneratorComponent::Initialize() {
	AddToSystem<AudioSystem>(AsRef<AudioSource>());
	
}

void SoundGeneratorComponent::Uninitialize() {
	
	RemoveFromSystem<AudioSystem>(AsRef<AudioSource>());
}

void SoundGeneratorComponent::RecvMidi(const MidiFrame& e) {
	TODO
}

void SoundGeneratorComponent::Configure(const Midi::File& file) {
	/*if (mode == MODE_TRACK_NUM) {
		if (track_i >= 0 && track_i < file.GetTrackCount()) {
			Ref<FluidsynthSystem> fs_sys = GetMachine().Get<FluidsynthSystem>();
			fs_sys->Assign(file, track_i, this);
		}
	}*/
}

AudioStream& SoundGeneratorComponent::GetAudioSource() {
	return gen;
}

void SoundGeneratorComponent::BeginAudioSource() {
	
}

void SoundGeneratorComponent::EndAudioSource() {
	
}




NAMESPACE_TOPSIDE_END
