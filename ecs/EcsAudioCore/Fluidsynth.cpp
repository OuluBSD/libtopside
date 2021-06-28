#include "EcsAudioCore.h"

#if 0
#if HAVE_FLUIDSYNTH


NAMESPACE_ECS_BEGIN



bool FluidsynthSystem::Initialize() {
	for(int i = 0; i < 16; i++)
		track_comps.Add();
	
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

void FluidsynthSystem::Update(double dt) {
	
	TODO
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

void FluidsynthSystem::Add(FluidsynthComponentRef comp) {
	comps.FindAdd(comp);
}

void FluidsynthSystem::Remove(FluidsynthComponentRef comp) {
	comps.RemoveKey(comp);
	
	for(FluidsynthComponentRef& track_comp : track_comps)
		if (track_comp == comp)
			track_comp.Clear();
}

void FluidsynthSystem::Assign(const MidiIO::File& file, int track_i, FluidsynthComponentRef comp) {
	if (track_i >= 0 && track_i < track_comps.GetCount()) {
		track_comps.At(track_i) = comp;
	}
	fs.ConfigureTrack(file, track_i);
}







FluidsynthComponent::FluidsynthComponent() {
	
}

void FluidsynthComponent::Initialize() {
	
}

void FluidsynthComponent::Uninitialize() {
	
}

void FluidsynthComponent::OpenTrackListener(int track_i) {
	mode = MODE_TRACK_NUM;
	this->track_i = track_i;
}


AudioStream& FluidsynthComponent::GetStream(AudCtx) {
	TODO
}

void FluidsynthComponent::BeginStream(AudCtx) {
	TODO
}

void FluidsynthComponent::EndStream(AudCtx) {
	TODO
}

MidiFormat FluidsynthComponent::GetFormat(MidCtx) {
	TODO
}

Midi& FluidsynthComponent::GetValue(MidCtx) {
	TODO
}



NAMESPACE_ECS_END

#endif
#endif
