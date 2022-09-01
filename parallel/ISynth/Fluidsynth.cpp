#include "ISynth.h"
#include <MidiFile/MidiFile.h>

#if defined flagFLUIDSYNTH


NAMESPACE_PARALLEL_BEGIN


struct SynFluidsynth::NativeInstrument {
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    int sfont_id;
    bool sf_loaded;
    int sample_rate;
    Vector<float> buffer;
    Vector<float*> dry;
    Vector<float*> fx;
    RunningFlag flag;
    Array<Vector<byte>> packets;
    Mutex lock;
};



void SynFluidsynth_ConfigureTrack(SynFluidsynth::NativeInstrument& dev, const MidiIO::File& file, int track_i);
bool SynFluidsynth_LoadSoundfontFile(SynFluidsynth::NativeInstrument& dev, String path);
bool SynFluidsynth_InitializeSoundfont(SynFluidsynth::NativeInstrument& dev);
void SynFluidsynth_Instrument_Update(SynFluidsynth::NativeInstrument& dev, AtomBase& a, Vector<byte>& out);
void SynFluidsynth_HandleEvent(SynFluidsynth::NativeInstrument& dev, const MidiIO::Event& e, int track_i=-1);
void SynFluidsynth_ProcessThread(SynFluidsynth::NativeInstrument* dev, AtomBase* a);


bool SynFluidsynth::Instrument_Initialize(NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.sample_rate = 1024;
	
	
	dev.settings = new_fluid_settings();
	fluid_settings_setnum(dev.settings, "synth.sample-rate", 44100);
	fluid_settings_setstr(dev.settings, "synth.verbose", ws.GetBool(".verbose", false) ? "yes" : "no");
		
	dev.synth = new_fluid_synth(dev.settings);
	
	SynFluidsynth_InitializeSoundfont(dev);
	
	
	ISourceRef src = a.GetSource();
	int c = src->GetSourceCount();
	Value& v = src->GetSourceValue(c-1);
	Format fmt = v.GetFormat();
	if (fmt.IsAudio()) {
		AudioFormat& afmt = fmt;
		//dev.sample_rate = afmt.GetSampleRate();
		afmt.SetType(BinarySample::FLT_LE);
		afmt.SetSampleRate(dev.sample_rate);
		v.SetFormat(fmt);
	}
	
	a.SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
		
    return true;
}

bool SynFluidsynth::Instrument_PostInitialize(NativeInstrument& dev, AtomBase& a) {
    return true;
}

bool SynFluidsynth::Instrument_Start(NativeInstrument& dev, AtomBase& a) {
	dev.flag.Start(1);
	UPP::Thread::Start(callback2(&SynFluidsynth_ProcessThread, &dev, &a));
	return true;
}

void SynFluidsynth::Instrument_Stop(NativeInstrument& dev, AtomBase& a) {
	dev.flag.Stop();
}

void SynFluidsynth::Instrument_Uninitialize(NativeInstrument& dev, AtomBase& a) {
	if (dev.settings) {
		delete_fluid_synth(dev.synth);
		delete_fluid_settings(dev.settings);
	}
	dev.settings = 0;
	dev.synth = 0;
	dev.sfont_id = -1;
    dev.sf_loaded = false;
}

bool SynFluidsynth::Instrument_Send(NativeInstrument& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	if (fmt.IsAudio()) {
		AudioFormat& afmt = fmt;
		int sr = afmt.GetSampleRate();
		ASSERT(sr == dev.sample_rate);
		ASSERT(afmt.GetSize() == 2);
		ASSERT(afmt.IsSampleFloat());
		
		if (dev.packets.GetCount()) {
			dev.lock.Enter();
			Swap(out.Data(), dev.packets[0]);
			dev.packets.Remove(0);
			dev.lock.Leave();
		}
		else out.Data().SetCount(afmt.GetFrameSize(), 0);
	}
	return true;
}

bool SynFluidsynth::Instrument_IsReady(NativeInstrument& dev, AtomBase& a, PacketIO& io) {
	// Primary sink is required always (continuous audio) so ignore midi input, which is mixed
	// to primary occasionally.
	return (io.active_sink_mask & 0x1) && io.full_src_mask == 0;
}

bool SynFluidsynth::Instrument_Recv(NativeInstrument& dev, AtomBase& a, int sink_i, const Packet& in) {
	Format fmt = in->GetFormat();
	if (fmt.IsMidi()) {
		const Vector<byte>& data = in->Data();
		int count = data.GetCount() / sizeof(MidiIO::Event);
		
		const MidiIO::Event* ev  = (const MidiIO::Event*)(const byte*)data.Begin();
		const MidiIO::Event* end = ev + count;
		
		while (ev != end) {
			SynFluidsynth_HandleEvent(dev, *ev);
			ev++;
		}
	}
	else if (fmt.IsOrder()) {
		// pass
	}
	else {
		TODO
	}
	return true;
}

void SynFluidsynth::Instrument_Finalize(NativeInstrument& dev, AtomBase&, RealtimeSourceConfig&) {
	
}









bool SynFluidsynth::Instrument_Create(One<NativeInstrument>& dev) {
	dev.Create();
	return true;
}

void SynFluidsynth::Instrument_Destroy(One<NativeInstrument>& dev) {
	dev.Clear();
}

bool SynFluidsynth_InitializeSoundfont(SynFluidsynth::NativeInstrument& dev) {
	Index<String> dirs;
	dirs.Add( ShareDirFile("soundfonts") );
	dirs.Add( ConfigFile("") );
	dirs.Add( "/usr/share/sounds/sf2" );
	dirs.Add( "/usr/share/soundfonts" );
	dirs.Add( "/usr/local/share/soundfonts" );
	
	Index<String> files;
	files.Add("TimGM6mb.sf2");
	files.Add("FluidR3 GM.sf2");
	files.Add("FluidR3_GM.sf2");
	files.Add("FluidR3_GS.sf2");
	files.Add("ChoriumRevA.sf2");
	files.Add("WeedsGM3.sf2");
	files.Add("UHD3.sf2");
	
	bool loaded = false;
	for(String file : files) {
		for(String dir : dirs) {
			String path = AppendFileName(dir, file);
			if (FileExists(path)) {
				LOG("Loading soundfont: " << path);
				if (SynFluidsynth_LoadSoundfontFile(dev, path))
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

void SynFluidsynth_ProcessThread(SynFluidsynth::NativeInstrument* dev, AtomBase* a) {
	int max_cache = 32;
	int buf_size = 2 * dev->sample_rate * sizeof(float);
	float wait_time = dev->sample_rate / 44100.;
	
	while (dev->flag.IsRunning()) {
		if (dev->packets.GetCount() >= max_cache) {
			Sleep(1);
			continue;
		}
		
		Vector<byte>* p = new Vector<byte>();
		p->SetCount(buf_size);
		
		SynFluidsynth_Instrument_Update(*dev, *a, *p);
		
		dev->lock.Enter();
		dev->packets.Add(p);
		dev->lock.Leave();
	}
	
	dev->flag.DecreaseRunning();
	
}

void SynFluidsynth_Instrument_Update(SynFluidsynth::NativeInstrument& dev, AtomBase& a, Vector<byte>& out) {
	
	// lookup number of audio and effect (stereo-)channels of the synth
    // see "synth.audio-channels", "synth.effects-channels" and "synth.effects-groups" settings respectively
    int n_aud_chan = fluid_synth_count_audio_channels(dev.synth);
    
    // by default there are two effects stereo channels (reverb and chorus) ...
    int n_fx_chan = fluid_synth_count_effects_channels(dev.synth);
    
    // ... for each effects unit. Each unit takes care of the effects of one MIDI channel.
    // If there are less units than channels, it wraps around and one unit may render effects of multiple
    // MIDI channels.
    //n_fx_chan *= fluid_synth_count_effects_groups(dev.synth);
    
    // for simplicity, allocate one single sample pool
    int sample_count = dev.sample_rate * (n_aud_chan + n_fx_chan) * 2;
    dev.buffer.SetCount(sample_count);
    float* samp_buf = (float*)dev.buffer.Begin();
    
    // array of buffers used to setup channel mapping
    Vector<float*>& dry = dev.dry;
    Vector<float*>& fx = dev.fx;
    dry.SetCount(n_aud_chan * 2);
    fx.SetCount(n_fx_chan * 2);
    
    // setup buffers to mix dry stereo audio to
    // buffers are alternating left and right for each n_aud_chan,
    // please review documentation of fluid_synth_process()
    for(int i = 0; i < n_aud_chan * 2; i++)
    {
        dry[i] = &samp_buf[i * dev.sample_rate];
    }
    
    // setup buffers to mix effects stereo audio to
    // similar channel layout as above, revie fluid_synth_process()
    for(int i = 0; i < n_fx_chan * 2; i++)
    {
        fx[i] = &samp_buf[n_aud_chan * 2 * dev.sample_rate + i * dev.sample_rate];
    }
    
    int out_samples = dev.sample_rate * 2;
    int out_size = out_samples * sizeof(float);
    out.SetCount(out_size);
    float* o = (float*)(byte*)out.Begin();
    
    #if 1
    
    fluid_synth_write_float(dev.synth, dev.sample_rate,
		o, 0, 2,
		o, 1, 2);
	
	
    #elif 1
    
    
    // dont forget to zero sample buffer(s) before each rendering
    memset(samp_buf, 0, sample_count * sizeof(float));
    int err = fluid_synth_process(dev.synth, dev.sample_rate, n_fx_chan * 2, fx.Begin(), n_aud_chan * 2, dry.Begin());
    if(err == FLUID_FAILED) {
        ASSERT_(0, "oops");
    }
    
    const float* l_from = dry[0];
    const float* r_from = dry[1];
    for(int i = 0; i < dev.sample_rate; i++) {
		*o++ = *l_from++;
		*o++ = *r_from++;
    }
    
    
    #else
    
    
    #define FLT_TO_S16(x) (x) * INT16_MAX
    #define FLT_TO_U16(x) ((x) + 1) * 0.5 * UINT16_MAX
    static int sample_i;
    int len = 1.0 / 440.0 * 44100;
    for(int i = 0; i < dev.sample_rate; i++) {
        float f = sin(sample_i / (float)len * 2 * M_PI);
		*o++ = FLT_TO_S16(f);
		*o++ = FLT_TO_S16(f);
		sample_i = (sample_i + 1) % len;
    }
    
    
    #endif
    
}

bool SynFluidsynth_LoadSoundfontFile(SynFluidsynth::NativeInstrument& dev, String path) {
	ASSERT(dev.synth);
	ASSERT(dev.settings);
	
    dev.sf_loaded = false;
    
	dev.sfont_id = fluid_synth_sfload(dev.synth, path.Begin(), 1);
    if (dev.sfont_id < 0)
        return false;
    
    dev.sf_loaded = true;
    return true;
}

void SynFluidsynth_ConfigureTrack(SynFluidsynth::NativeInstrument& dev, const MidiIO::File& file, int track_i) {
	int tracks = file.GetTrackCount();
	int fs_tracks = fluid_synth_count_midi_channels(dev.synth);
	
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
		
		SynFluidsynth_HandleEvent(dev, e, track_i);
	}
}

void SynFluidsynth_HandleEvent(SynFluidsynth::NativeInstrument& dev, const MidiIO::Event& e, int track_i) {
	int channel = e.GetChannel();

	if (e.IsController()) {
		if (track_i < 0 || channel == track_i) {
			int num = e.GetP1();
			int value = e.GetP2();
			LOG("Configure event: " <<
				e.ToString() << ": " <<
				MidiIO::GetEventCtrlString(num) << " = " << value);
			fluid_synth_cc(dev.synth, channel, num, value);
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
		fluid_synth_noteoff(dev.synth, channel, e.GetP1());
	}
	else if (e.IsNoteOn()) {
		fluid_synth_noteon(dev.synth, channel, e.GetP1(), e.GetP2());
	}
	else if (e.IsNote()) {
		LOG("Ignore note: " << e.ToString());
	}
	else if (e.IsAftertouch()) {
		LOG("Ignore aftertouch: " << e.ToString());
	}
	else if (e.IsTimbre() || e.IsPatchChange()) {
		int channel = e.GetChannel();
		int value = e.GetP1();
		if (track_i < 0 || channel == track_i) {
			LOG("Changing channel patch: channel " << channel << " to " << value << ": " << e.ToString());
			int bank = 0;
			// if channel is the midi-standard drum channel
			if (channel == 9) {
				bank = 128;
			}
			fluid_synth_program_select(dev.synth, channel, dev.sfont_id, bank, value);
		}
	}
	else if (e.IsPressure()) {
		LOG("Ignore pressure: " << e.ToString());
	}
	else if (e.IsPitchbend()) {
		int channel = e.GetChannel();
		int value = e.GetP1();
		if (track_i < 0 || channel == track_i) {
			LOG("Setting pitch bend: channel " << channel << " to " << value);
			int fs_pbend = (128 + value) * 0x4000 / 256;
			fluid_synth_pitch_bend(dev.synth, channel, fs_pbend);
		}
	}
	else {
		LOG("Unexpected configure event: " << e.ToString());
	}
}


NAMESPACE_PARALLEL_END

#endif

