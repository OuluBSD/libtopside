#include "AudioCore.h"
#include "System.h"


NAMESPACE_OULU_BEGIN


SoundGeneratorComponent::SoundGeneratorComponent() {
	
}

void SoundGeneratorComponent::Initialize() {
	AddToSystem<AudioSystem>(this);
	
}

void SoundGeneratorComponent::Uninitialize() {
	
	RemoveFromSystem<AudioSystem>(this);
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

/*void SoundGeneratorComponent::Play(const RealtimeSourceConfig& config, Audio& aud) {
	AudioFormat fmt = aud.GetAudioFormat();
	if (fmt.is_var_float && fmt.var_size == 4) {
		gen_f32.Play(config, aud);
	}
	else if (!fmt.is_var_float && fmt.var_size == 2) {
		gen_u16.Play(config, aud);
	}
	else {
		Panic("Invalid format");
	}
}*/


AudioStream& SoundGeneratorComponent::GetAudioSource() {
	TODO
}

void SoundGeneratorComponent::BeginAudioSource() {
	TODO
}

void SoundGeneratorComponent::EndAudioSource() {
	TODO
}




NAMESPACE_OULU_END
