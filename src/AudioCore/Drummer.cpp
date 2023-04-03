#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN


unsigned char gen_midi_map[128] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,		// 8
	0, 0, 0, 0, 0, 0, 0, 0,		// 16
	0, 0, 0, 0, 0, 0, 0, 0,		// 24
	0, 0, 0, 0, 1, 0, 2, 0,		// 32, kick, snare
	2, 3, 6, 3, 6, 4, 7, 4,		// 40, esnare, low tom, chh, floor tom, phh, low tom, ohh, mid tom, lmid tom, mid tom
	5, 8, 5, 7, 0, 0, 10, 0,	// 48, hmid tom, crash, high tom, chinese symbal
	9, 0, 0, 0, 0, 0, 0, 0,		// 56, cowbell
	0, 0, 0, 0, 0, 0, 0, 0,		// 64
	0, 0, 0, 0, 0, 0, 0, 0,		// 72
	0, 0, 0, 0, 0, 0, 0, 0,		// 80
	0, 0, 0, 0, 0, 0, 0, 0,		// 88
	0, 0, 0, 0, 0, 0, 0, 0,		// 96
	0, 0, 0, 0, 0, 0, 0, 0,		// 104
	0, 0, 0, 0, 0, 0, 0, 0,		// 112
	0, 0, 0, 0, 0, 0, 0, 0		// 120
};

const char wave_names[DRUM_NUMWAVES][16] = {
	"dope.raw",
	"bassdrum.raw",
	"snardrum.raw",
	"tomlowdr.raw",
	"tommiddr.raw",
	"tomhidrm.raw",
	"hihatcym.raw",
	"ridecymb.raw",
	"crashcym.raw",
	"cowbell1.raw",
	"tambourn.raw"
};









Drummer::Drummer() : Instrument() {
	sounding_count = 0;
	sound_order_.SetCount(DRUM_POLYPHONY, -1);
	sound_number_.SetCount(DRUM_POLYPHONY, -1);
	
	for(int i = 0; i < 128; i++) {
		preset.Add(i, wave_names[gen_midi_map[i]]);
	}
}

Drummer::~Drummer() {

}

void Drummer::SetPreset(String preset_txt) {
	this->preset.Clear();
	Vector<String> lines = Split(preset_txt, "\n");
	String dir;
	for (const String& line : lines) {
		Vector<String> parts = Split(line, ",");
		if (parts.GetCount() != 2)
			continue;
		String key = TrimBoth(parts[0]);
		String value = TrimBoth(parts[1]);
		
		if (key == "dir") {
			dir = value;
		}
		else {
			int note = StrInt(key.Left(2));
			String path = AppendFileName(dir, value);
			path = RealizeShareFile(path);
			ASSERT(FileExists(path));
			if (FileExists(path))
				preset.Add(note, path);
		}
	}
	//DUMPM(preset);
}

float Drummer::Tick(int) {
	last_frame_.Zero();
	
	if (sounding_count == 0)
		return last_frame_[0];
		
	for (int i = 0; i < DRUM_POLYPHONY; i++) {
		if (sound_order_[i] >= 0) {
			auto& w = waves_[i];
			
			if (w.IsFinished() || !w.GetChannelsOut()) {
				for (int j = 0; j < DRUM_POLYPHONY; j++) {
					if (sound_order_[j] > sound_order_[i])
						sound_order_[j] -= 1;
				}
				
				sound_order_[i] = -1;
				sounding_count--;
			}
			else {
				w.Tick();
				
				const auto& src_frame = w.GetLastFrame();
				int chs = src_frame.GetChannelCount();
				for(int ch = 0; ch < chs; ch++) {
					last_frame_[ch] += filters_[i].Tick(src_frame[ch]);
				}
			}
		}
	}
	
	return last_frame_[0];
}

AudioFrames& Drummer::Tick(AudioFrames& frames, int channel) {
	int channel_count = last_frame_.GetChannelCount();
#if defined(flagDEBUG)
	
	if (channel > frames.GetChannelCount() - channel_count) {
		LOG("Drummer::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError(AudioError::FUNCTION_ARGUMENT);
	}
	
#endif
	float* samples = &frames[channel];
	int j, step = frames.GetChannelCount() - channel_count;
	
	if (channel_count == 1) {
		for (int i = 0; i < frames.GetFrameCount(); i++, samples += step)
			* samples++ = Tick();
	}
	
	else {
		for (int i = 0; i < frames.GetFrameCount(); i++, samples += step) {
			*samples++ = Tick();
			
			for (j = 1; j < channel_count; j++)
				*samples++ = last_frame_[j];
		}
	}
	
	return frames;
}

void Drummer::NoteOn(float instrument, float amplitude) {
	if (amplitude < 0.0f || amplitude > 1.0f) {
		LOG("Drummer::noteOn: amplitude parameter is out of bounds!");
		HandleError(AudioError::WARNING);
		return;
	}
	
	int note_number = (int)((12 * log(instrument / 220.0f) / log(2.0f)) + 57.01f);
	int i_wave;
	
	for (i_wave = 0; i_wave < DRUM_POLYPHONY; i_wave++) {
		if (sound_number_[i_wave] == note_number) {
			if (waves_[i_wave].IsFinished()) {
				sound_order_[i_wave] = sounding_count;
				sounding_count++;
				
				waves_[i_wave].Reset();
				
				filters_[i_wave].SetPole(0.999f - (amplitude * 0.6f));
				filters_[i_wave].SetGain(amplitude);
				break;
			}
		}
	}
	
	if (i_wave == DRUM_POLYPHONY) {
		if (sounding_count < DRUM_POLYPHONY) {
			for (i_wave = 0; i_wave < DRUM_POLYPHONY; i_wave++)
				if (sound_order_[i_wave] < 0)
					break;
					
			sounding_count += 1;
		}
		
		else {
			for (i_wave = 0; i_wave < DRUM_POLYPHONY; i_wave++)
				if (sound_order_[i_wave] == 0)
					break;
					
			for (int j = 0; j < DRUM_POLYPHONY; j++) {
				if (sound_order_[j] > sound_order_[i_wave])
					sound_order_[j] -= 1;
			}
		}
		
		sound_order_[i_wave] = sounding_count - 1;
		sound_number_[i_wave] = note_number;
		
		#if 0
		waves_[i_wave].OpenFile((Audio::GetRawWavePath() + wave_names[ gen_midi_map[ note_number ] ]).Begin(), true);
		#else
		String path = preset.Get(note_number, String());
		if (!path.IsEmpty())
			waves_[i_wave].OpenFile(path.Begin(), false);
		#endif
		
		if (Audio::GetSampleRate() != 44100.0f)
			waves_[i_wave].SetRate(44100.0f / Audio::GetSampleRate());
			
		filters_[i_wave].SetPole(0.999f - (amplitude * 0.6f));
		filters_[i_wave].SetGain(amplitude);
	}
}

void Drummer::NoteOff(float amplitude) {
	if (skip_note_off)
		return;
	
	int i = 0;
	
	while (i < sounding_count)
		filters_[i++].SetGain(amplitude * 0.01f);
}

NAMESPACE_AUDIO_END
