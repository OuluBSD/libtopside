#include "AudioCore.h"

#if HAVE_FLUIDSYNTH



NAMESPACE_TOPSIDE_BEGIN

Fluidsynth::Fluidsynth() {
	
}

Fluidsynth::~Fluidsynth() {
	Clear();
}

void Fluidsynth::Init() {
	Clear();
	
#ifdef flagLINUX
	bool use_alsa = false;
	const char *adrivers[] = {"portaudio", "alsa", 0};
	int res = fluid_audio_driver_register(adrivers);
	if(res == FLUID_OK)
		use_alsa = true;
	
	settings = new_fluid_settings();
	if (use_alsa)
		res = fluid_settings_setstr(settings, "audio.driver", adrivers[0]);
#else
	settings = new_fluid_settings();
#endif
	
	synth = new_fluid_synth(settings);
	adriver = new_fluid_audio_driver(settings, synth);
}

void Fluidsynth::Clear() {
	if (settings) {
		delete_fluid_audio_driver(adriver);
		delete_fluid_synth(synth);
		delete_fluid_settings(settings);
	}
	settings = 0;
	synth = 0;
	adriver = 0;
	sfont_id = -1;
    sf_loaded = false;
}

bool Fluidsynth::LoadSoundfontFile(String path) {
	if (!settings)
		Init();
	
    sf_loaded = false;
    
	sfont_id = fluid_synth_sfload(synth, path.Begin(), 1);
    if (sfont_id == FLUID_FAILED)
        return false;
    
    sf_loaded = true;
    return true;
}

void Fluidsynth::ConfigureTrack(const MidiIO::File& file, int track_i) {
	int tracks = file.GetTrackCount();
	int fs_tracks = fluid_synth_count_midi_channels(synth);
	
	if (track_i < 0 || track_i >= tracks) {
		LOG("FluidsynthSystem: error: invalid track_i " << track_i << " based on file");
		return;
	}
	
	if (track_i < 0 || track_i >= fs_tracks) {
		LOG("FluidsynthSystem: error: invalid track_i " << track_i << " based on fluidsynth");
		return;
	}
	
	const MidiIO::EventList& track = file[track_i];
	for(int i = 0; i < track.GetCount(); i++) {
		const MidiIO::Event& e = track[i];
		if (e.tick > 0)
			break;
		
		if (e.IsController()) {
			int channel = e.GetChannel();
			if (channel == track_i) {
				int num = e.GetP1();
				int value = e.GetP2();
				LOG("Configure event " << i << ": " <<
					e.ToString() << ": " <<
					MidiIO::GetEventCtrlString(num) << " = " << value);
				fluid_synth_cc(synth, channel, num, value);
			}
		}
		else if (e.IsMeta()) {
			bool send = false;
			int mnum = e.GetP1();
			int strlen = e.GetP2();
			String str;
			for(int i = 3; i < 3 + strlen; i++) {
				int chr = e[i];
				str.Cat(i);
			}
			switch (mnum) {
				case MidiIO::MIDIMETA_SEQNUM:
					break;
				case MidiIO::MIDIMETA_TEXT:
					LOG("Midi-string: " << str);
					break;
				case MidiIO::MIDIMETA_COPYRIGHT:
					LOG("Copyright: " << str);
					break;
				case MidiIO::MIDIMETA_TRACKNAME:
					LOG("Track name: " << str);
					break;
				case MidiIO::MIDIMETA_INSTRNAME:
					LOG("Instrument name: " << str);
					break;
				case MidiIO::MIDIMETA_LYRICS:
					break;
				case MidiIO::MIDIMETA_MARKER:
					break;
				case MidiIO::MIDIMETA_CUEPOINT:
					break;
				case MidiIO::MIDIMETA_CHPREFIX:
					break;
				case MidiIO::MIDIMETA_TRACKEND:
					break;
				case MidiIO::MIDIMETA_TEMPO:
					break;
				case MidiIO::MIDIMETA_SMPTE:
					break;
				case MidiIO::MIDIMETA_TIMESIG:
					break;
				case MidiIO::MIDIMETA_KEYSIG:
					break;
				case MidiIO::MIDIMETA_CUSTOM:
					break;
			}
			
		}
		else if (e.IsNoteOff()) {
			LOG("Ignore note-off " << i << ": " << e.ToString());
		}
		else if (e.IsNoteOn()) {
			LOG("Ignore note-on " << i << ": " << e.ToString());
		}
		else if (e.IsNote()) {
			LOG("Ignore note " << i << ": " << e.ToString());
		}
		else if (e.IsAftertouch()) {
			LOG("Ignore aftertouch " << i << ": " << e.ToString());
		}
		else if (e.IsTimbre() || e.IsPatchChange()) {
			int channel = e.GetChannel();
			int value = e.GetP1();
			if (channel == track_i) {
				LOG("Changing channel patch " << i << ": channel " << channel << " to " << value);
				fluid_synth_program_select(synth, channel, sfont_id, value, 0);
			}
		}
		else if (e.IsPressure()) {
			LOG("Ignore pressure " << i << ": " << e.ToString());
		}
		else if (e.IsPitchbend()) {
			int channel = e.GetChannel();
			int value = e.GetP1();
			if (channel == track_i) {
				LOG("Setting pitch bend " << i << ": channel " << channel << " to " << value);
				fluid_synth_pitch_bend(synth, channel, value);
			}
		}
		else {
			LOG("Unexpected configure event " << i << ": " << e.ToString());
		}
		
	}
	
	LOG("");
}









NAMESPACE_TOPSIDE_END

#endif
