#include "ISynth.h"

#if 1
NAMESPACE_PARALLEL_BEGIN


struct SynCoreDrummer::NativeInstrument {
    Array<Audio::Instrument> voices;
    Vector<int> notes;
    Vector<dword> seqs;
    int sample_rate;
    float multiplier;
    int polyphone;
    dword seq;
    
    enum {
        OH,
        KICK,
        SNARE,
        TOMS,
        
        GROUP_COUNT
    };
    
    int group_ch[GROUP_COUNT] = {-1,-1,-1,-1};
    
    static const int* group_notes[GROUP_COUNT];
    static const int kick_notes[];
    static const int snare_notes[];
    static const int toms_notes[];
    
};

const int* SynCoreDrummer::NativeInstrument::group_notes[GROUP_COUNT] = {
	0,
	&SynCoreDrummer::NativeInstrument::kick_notes[0],
	&SynCoreDrummer::NativeInstrument::snare_notes[0],
	&SynCoreDrummer::NativeInstrument::toms_notes[0]
};

const int SynCoreDrummer::NativeInstrument::kick_notes[] = {35,36,-1};
const int SynCoreDrummer::NativeInstrument::snare_notes[] = {37,38,39,40,-1};
const int SynCoreDrummer::NativeInstrument::toms_notes[] = {41,43,45,47,48,50,60,61,62,63,64,76,77,-1};


template <class T>
void CreateSynCoreInstrument(SynCoreDrummer::NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws) {
	String preset_file = ws.Get(".preset");
	String preset;
	
	preset_file = RealizeShareFile(preset_file);
	if (FileExists(preset_file))
		preset = LoadFile(preset_file);
	
	for(int i = 0; i < dev.polyphone; i++) {
		T* t = new T();
		t->SetPreset(preset);
		dev.voices.Add(t);
		dev.notes.Add(-1);
		dev.seqs.Add(0);
	}
}

bool SynCoreDrummer::Instrument_Create(NativeInstrument*& dev) {
	dev = new NativeInstrument;
	return true;
}

void SynCoreDrummer::Instrument_Destroy(NativeInstrument*& dev) {
	delete dev;
}

void SynCoreDrummer::Instrument_Visit(NativeInstrument& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool SynCoreDrummer::Instrument_Initialize(NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.polyphone = min(128, max(0, ws.GetInt(".polyphone", 12)));
	
	String instrument = ToLower(ws.GetString(".instrument", "plucked"));
	
	CreateSynCoreInstrument<Audio::Drummer>(dev, a, ws);
	
	dev.seq = 0;
	dev.multiplier = 1;
	dev.sample_rate = ws.GetInt(".samplerate", 128);
	
	dev.group_ch[NativeInstrument::OH] = ws.GetInt(".ch.oh", -1);
	dev.group_ch[NativeInstrument::KICK] = ws.GetInt(".ch.kick", -1);
	dev.group_ch[NativeInstrument::SNARE] = ws.GetInt(".ch.snare", -1);
	dev.group_ch[NativeInstrument::TOMS] = ws.GetInt(".ch.toms", -1);
	
	ISourceRef src = a.GetSource();
	int c = src->GetSourceCount();
	float freq = 44100.f;
	for(int i = 1; i < c; i++) {
		Value& v = src->GetSourceValue(i);
		Format fmt = v.GetFormat();
		if (fmt.IsAudio()) {
			AudioFormat& afmt = fmt;
			afmt.SetType(BinarySample::FLT_LE);
			afmt.SetSampleRate(dev.sample_rate);
			v.SetFormat(fmt);
			freq = (float)afmt.freq;
		}
	}
	for(int i = 0; i < dev.voices.GetCount(); i++) {
		Audio::Instrument& instrument = dev.voices[i];
		instrument.SetSampleRate(freq);
	}
	
	//a.SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	
	return true;
}

bool SynCoreDrummer::Instrument_PostInitialize(NativeInstrument& dev, AtomBase& a) {
		
	return true;
}

bool SynCoreDrummer::Instrument_Start(NativeInstrument& dev, AtomBase& a) {
	return true;
}

void SynCoreDrummer::Instrument_Stop(NativeInstrument& dev, AtomBase& a) {
	
}

void SynCoreDrummer::Instrument_Uninitialize(NativeInstrument& dev, AtomBase& a) {
	
}

bool SynCoreDrummer::Instrument_Send(NativeInstrument& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	if (fmt.IsAudio()) {
		AudioFormat& afmt = fmt;
		int sr = afmt.GetSampleRate();
		int channel_count = afmt.GetSize();
		ASSERT(channel_count == 2);
		ASSERT(afmt.IsSampleFloat());
		
		Vector<byte>& d = out.Data();
		int sz = afmt.GetFrameSize();
		d.SetCount(sz);
		float* begin = (float*)(byte*)d.Begin();
		memset(begin, 0, sz);
		
		float abs_max = 0;
		for(int i = 0; i < dev.voices.GetCount(); i++) {
			int note = dev.notes[i];
			if (note < 0)
				continue;
			
			// Find group of the note
			int group = 0;
			for(int i = 1; i < NativeInstrument::GROUP_COUNT && !group; i++) {
				const int* gnote = NativeInstrument::group_notes[i];
				while (*gnote != -1) {
					if (*gnote == note) {
						group = i;
						break;
					}
					gnote++;
				}
			}
			
			// If group doesn't match current note's output connection, then skip the note
			ASSERT(group >= 0 && group < NativeInstrument::GROUP_COUNT);
			int group_src_ch = dev.group_ch[group];
			if (group_src_ch >= 0 && group_src_ch != src_ch)
				continue;
			
			Audio::Instrument& instrument = dev.voices[i];
			float* f = begin;
			const Audio::AudioFrames& last_frame = instrument.GetLastFrame();
			int frame_channel_count = last_frame.GetChannelCount();
			float mul = dev.multiplier;
			for(int i = 0; i < sr; i++) {
				instrument.Tick();
				
				float v = last_frame[0] * mul + *f;
				float av = fabsf(v);
				if (av > abs_max)
					abs_max = av;
				
				for (int j = 0; j < frame_channel_count; j++ )
					*f++ += last_frame[j] * mul;
				for (int j = frame_channel_count; j < channel_count; j++ ) {
					float prev = f[-1];
					*f++ += prev;
				}
			}
		}
		
		if (abs_max > 1.0f) {
			float mul = (1.0f / abs_max) * 0.99f;
			dev.multiplier *= mul;
			float* f = begin;
			for(int i = 0; i < sr; i++)
				for (int j = 0; j < channel_count; j++ )
					*f++ *= mul;
		}
		
		#if HAVE_PACKETTIMING
		out.SetBeginTime();
		#endif
		
		ASSERT(out.GetBeginTime());
	}
	return true;
}

bool SynCoreDrummer::Instrument_Recv(NativeInstrument& dev, AtomBase& a, int sink_ch, const Packet& in) {
	Format fmt = in->GetFormat();
	if (fmt.IsMidi()) {
		const Vector<byte>& data = in->Data();
		int count = data.GetCount() / sizeof(MidiIO::Event);
		
		const MidiIO::Event* ev  = (const MidiIO::Event*)(const byte*)data.Begin();
		const MidiIO::Event* end = ev + count;
		
		while (ev != end) {
			if (ev->IsController() ||
				ev->IsMeta() ||
				ev->IsPatchChange() ||
				ev->IsPitchbend()) {
				for (auto& v : dev.voices)
					v.HandleEvent(*ev);
			}
			else if (ev->IsNoteOn()) {
				int new_note = ev->GetP1();
				
				// Find best voice to use
				int vi = 0;
				dword oldest = UINT32_MAX;
				for(int i = 0; i < dev.voices.GetCount(); i++) {
					int note = dev.notes[i];
					if (note < 0) {
						vi = i;
						break;
					}
					dword seq = dev.seqs[i];
					if (seq < oldest) {
						vi = i;
						oldest = seq;
					}
				}
				
				Audio::Instrument& v = dev.voices[vi];
				dev.seqs[vi] = dev.seq;
				dev.notes[vi] = new_note;
				dev.seq++;
				
				v.HandleEvent(*ev);
			}
			else if (ev->IsNoteOff()) {
				int old_note = ev->GetP1();
				int vi = 0;
				for(int i = 0; i < dev.voices.GetCount(); i++) {
					int& note = dev.notes[i];
					if (note == old_note) {
						note = -1;
						vi = i;
						break;
					}
				}
				Audio::Instrument& v = dev.voices[vi];
				v.HandleEvent(*ev);
			}
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

void SynCoreDrummer::Instrument_Finalize(NativeInstrument& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool SynCoreDrummer::Instrument_IsReady(NativeInstrument& dev, AtomBase& a, PacketIO& io) {
	// Primary sink is required always (continuous audio) so ignore midi input, which is mixed
	// to primary occasionally.
	return (io.active_sink_mask & 0x1) && io.full_src_mask == 0;
}





NAMESPACE_PARALLEL_END
#endif

