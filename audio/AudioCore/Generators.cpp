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

void SoundGeneratorComponent::EmitAudioSource(double dt) {
	DefaultEmitAudioSource(dt);
}

void SoundGeneratorComponent::Play(const AudioSinkConfig& config, Sound& snd) {
	SoundFormat fmt = snd.GetSoundFormat();
	if (fmt.is_var_float && fmt.var_size == 4) {
		gen_f32.Play(config, snd);
	}
	else if (!fmt.is_var_float && fmt.var_size == 2) {
		gen_u16.Play(config, snd);
	}
	else {
		Panic("Invalid format");
	}
}




NAMESPACE_OULU_END
