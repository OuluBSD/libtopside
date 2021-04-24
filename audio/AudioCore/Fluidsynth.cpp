#if HAVE_FLUIDSYNTH

#include "AudioCore.h"
#include "System.h"


NAMESPACE_OULU_BEGIN

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

void Fluidsynth::ConfigureTrack(const Midi::File& file, int track_i) {
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
	
	const Midi::EventList& track = file[track_i];
	for(int i = 0; i < track.GetCount(); i++) {
		const Midi::Event& e = track[i];
		if (e.tick > 0)
			break;
		
		if (e.IsController()) {
			int channel = e.GetChannel();
			if (channel == track_i) {
				int num = e.GetP1();
				int value = e.GetP2();
				LOG("Configure event " << i << ": " <<
					e.ToString() << ": " <<
					Midi::GetEventCtrlString(num) << " = " << value);
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
				case Midi::MIDIMETA_SEQNUM:
					break;
				case Midi::MIDIMETA_TEXT:
					LOG("Midi-string: " << str);
					break;
				case Midi::MIDIMETA_COPYRIGHT:
					LOG("Copyright: " << str);
					break;
				case Midi::MIDIMETA_TRACKNAME:
					LOG("Track name: " << str);
					break;
				case Midi::MIDIMETA_INSTRNAME:
					LOG("Instrument name: " << str);
					break;
				case Midi::MIDIMETA_LYRICS:
					break;
				case Midi::MIDIMETA_MARKER:
					break;
				case Midi::MIDIMETA_CUEPOINT:
					break;
				case Midi::MIDIMETA_CHPREFIX:
					break;
				case Midi::MIDIMETA_TRACKEND:
					break;
				case Midi::MIDIMETA_TEMPO:
					break;
				case Midi::MIDIMETA_SMPTE:
					break;
				case Midi::MIDIMETA_TIMESIG:
					break;
				case Midi::MIDIMETA_KEYSIG:
					break;
				case Midi::MIDIMETA_CUSTOM:
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












FluidsynthSystem::FluidsynthSystem(Machine& m) : System<FluidsynthSystem>(m) {
	track_comps.SetCount(32, 0);
}

bool FluidsynthSystem::Initialize() {
	Index<String> dirs;
	dirs.Add( ShareDirFile("soundfonts") );
	dirs.Add( ConfigFile("") );
	dirs.Add( "/usr/share/sounds/sf2" );
	dirs.Add( "/usr/share/soundfonts" );
	dirs.Add( "/usr/local/share/soundfonts" );
	
	Index<String> files;
	files.Add("TimGM6mb.sf2");
	files.Add("ChoriumRevA.sf2");
	files.Add("WeedsGM3.sf2");
	files.Add("UHD3.sf2");
	files.Add("FluidR3 GM.sf2");
	files.Add("FluidR3_GM.sf2");
	files.Add("FluidR3_GS.sf2");
	
	bool loaded = false;
	for(String dir : dirs) {
		for(String file : files) {
			String path = AppendFileName(dir, file);
			if (FileExists(path)) {
				if (fs.LoadSoundfontFile(path))
					loaded = true;
			}
			if (loaded) break;
		}
		if (loaded) break;
	}
	if (!loaded) {
		LOG("FluidsynthSystem: error: could not load any soundfont");
		return false;
	}
	
	
	return true;
}

void FluidsynthSystem::Start() {
	
}

void FluidsynthSystem::Update(float dt) {
	
	#if 0
	// lookup number of audio and effect (stereo-)channels of the synth
    // see "synth.audio-channels", "synth.effects-channels" and "synth.effects-groups" settings respectively
    int n_aud_chan = fluid_synth_count_audio_channels(synth);
    
    // by default there are two effects stereo channels (reverb and chorus) ...
    int n_fx_chan = fluid_synth_count_effects_channels(synth);
    
    // ... for each effects unit. Each unit takes care of the effects of one MIDI channel.
    // If there are less units than channels, it wraps around and one unit may render effects of multiple
    // MIDI channels.
    n_fx_chan *= fluid_synth_count_effects_groups();
    // for simplicity, allocate one single sample pool
    float samp_buf[SAMPLES * (n_aud_chan + n_fx_chan) * 2];
    // array of buffers used to setup channel mapping
    float *dry[n_aud_chan * 2], *fx[n_fx_chan * 2];
    // setup buffers to mix dry stereo audio to
    // buffers are alternating left and right for each n_aud_chan,
    // please review documentation of fluid_synth_process()
    for(int i = 0; i < n_aud_chan * 2; i++)
    {
        dry[i] = &samp_buf[i * SAMPLES];
    }
    // setup buffers to mix effects stereo audio to
    // similar channel layout as above, revie fluid_synth_process()
    for(int i = 0; i < n_fx_chan * 2; i++)
    {
        fx[i] = &samp_buf[n_aud_chan * 2 * SAMPLES + i * SAMPLES];
    }
    // dont forget to zero sample buffer(s) before each rendering
    memset(samp_buf, 0, sizeof(samp_buf));
    int err = fluid_synth_process(synth, SAMPLES, n_fx_chan * 2, fx, n_aud_chan * 2, dry);
    if(err == FLUID_FAILED)
    {
        puts("oops");
    }
    #endif
}

void FluidsynthSystem::Stop() {
	
}

void FluidsynthSystem::Uninitialize() {
	fs.Clear();
}

void FluidsynthSystem::AddContext(FluidsynthComponent& comp) {
	VectorFindAdd(comps, &comp);
}

void FluidsynthSystem::RemoveContext(FluidsynthComponent& comp) {
	VectorRemoveKey(comps, &comp);
	
	for(FluidsynthComponent*& track_comp : track_comps)
		if (track_comp == &comp)
			track_comp = 0;
}

void FluidsynthSystem::Assign(const Midi::File& file, int track_i, FluidsynthComponent* comp) {
	if (track_i >= 0 && track_i < track_comps.GetCount()) {
		track_comps[track_i] = comp;
	}
	fs.ConfigureTrack(file, track_i);
}







FluidsynthComponent::FluidsynthComponent() {
	
}

void FluidsynthComponent::Initialize() {
	
}

void FluidsynthComponent::Uninitialize() {
	
}

void FluidsynthComponent::RecvMidi(const MidiFrame& e) {
	TODO
}

void FluidsynthComponent::Configure(const Midi::File& file) {
	if (mode == MODE_TRACK_NUM) {
		if (track_i >= 0 && track_i < file.GetTrackCount()) {
			Ref<FluidsynthSystem> fs_sys = GetMachine().Get<FluidsynthSystem>();
			fs_sys->Assign(file, track_i, this);
		}
	}
}

void FluidsynthComponent::OpenTrackListener(int track_i) {
	mode = MODE_TRACK_NUM;
	this->track_i = track_i;
}

NAMESPACE_OULU_END

#endif
