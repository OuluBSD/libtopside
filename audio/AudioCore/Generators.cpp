#include "AudioCore.h"
#include "System.h"


NAMESPACE_OULU_BEGIN


SoundGeneratorComponent::SoundGeneratorComponent() {
	
}

void SoundGeneratorComponent::Initialize() {
	AddAudioSource(*this);
	
}

void SoundGeneratorComponent::Uninitialize() {
	
	RemoveAudioSource(*this);
}

void SoundGeneratorComponent::RecvMidi(const MidiFrame& e) {
	TODO
}

void SoundGeneratorComponent::Configure(const Midi::File& file) {
	/*if (mode == MODE_TRACK_NUM) {
		if (track_i >= 0 && track_i < file.GetTrackCount()) {
			Shared<FluidsynthSystem> fs_sys = GetMachine().Get<FluidsynthSystem>();
			fs_sys->Assign(file, track_i, this);
		}
	}*/
}

void SoundGeneratorComponent::EmitAudioSource(float dt) {
	DefaultEmitAudioSource(dt);
}

void SoundGeneratorComponent::Play(const AudioSinkConfig& config, Sound& snd) {
	SoundFormat fmt = snd.GetFormat();
	if (fmt.is_var_float && fmt.var_size == 4) {
		if (frame.IsEmpty()) {
			GenerateStereoSine(fmt);
		}
		
		snd.Put(frame.Begin() + frame_offset, frame_part_size * sizeof(float), config.sync);
		frame_offset = (frame_offset + frame_part_size) % frame.GetCount();
		ASSERT(frame_offset % fmt.sample_rate == 0);
	}
	else {
		Panic("Invalid format");
	}
}

void SoundGeneratorComponent::GenerateStereoSine(const SoundFormat& fmt) {
	double pan_loop_seconds = 2.0;
	int tone_mul = 4;
	int pan_frames = fmt.freq * pan_loop_seconds / fmt.sample_rate;
	int pan_samples = pan_frames * fmt.sample_rate;
	int pan_i = 0;
	frame_part_size = fmt.sample_rate * fmt.channels;
	int size = frame_part_size * pan_frames;
	frame.SetCount(size);
	float* f = frame.Begin();
	for (int p = 0; p < pan_frames; p++) {
		for(int i = 0; i < fmt.sample_rate; i++) {
			double tonerad = tone_mul * M_2PI * (double)i / (double)fmt.sample_rate;
			double tonesin = FastSin(tonerad);
			double tonevol = (tonesin + 1.0) * 0.5;
			double panrad = M_2PI * (double)pan_i / (double)pan_samples;
			double pansin = FastSin(panrad);
			double panvol = (pansin + 1.0) * 0.5;
			for(int j = 0; j < fmt.channels; j++) {
				double pan = (j % 2 == 0) ? panvol : (1.0 - panvol);
				//pan = j == 0  ? 1.0 : 0.0;
				double value = pan * tonesin;
				//value = tonesin;
				
				*f = value;
				f++;
			}
			pan_i++;
		}
	}
	ASSERT(f == frame.End());
	frame_offset = 0;
}



NAMESPACE_OULU_END
