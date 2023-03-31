#include "ISynth.h"

#if 1
NAMESPACE_PARALLEL_BEGIN


struct SynCoreSynth::NativeInstrument {
    Array<Audio::Instrument> voices;
    Vector<int> notes;
    Vector<dword> seqs;
    int sample_rate;
    float multiplier;
    int polyphone;
    dword seq;
};





template <class T>
void CreateSynCoreInstrument(SynCoreSynth::NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws) {
	for(int i = 0; i < dev.polyphone; i++) {
		T* t = new T();
		dev.voices.Add(t);
		dev.notes.Add(-1);
		dev.seqs.Add(0);
	}
}

bool SynCoreSynth::Instrument_Create(NativeInstrument*& dev) {
	dev = new NativeInstrument;
	return true;
}

void SynCoreSynth::Instrument_Destroy(NativeInstrument*& dev) {
	delete dev;
}

void SynCoreSynth::Instrument_Visit(NativeInstrument& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool SynCoreSynth::Instrument_Initialize(NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.polyphone = min(128, max(0, ws.GetInt(".polyphone", 12)));
	
	String instrument = ToLower(ws.GetString(".instrument", "plucked"));
	
	if (instrument == "bandedwaveguide")	CreateSynCoreInstrument<Audio::BandedWaveGuide>(dev, a, ws);
	else if (instrument == "beethree")		CreateSynCoreInstrument<Audio::BeeThree>(dev, a, ws);
	else if (instrument == "blowbottle")	CreateSynCoreInstrument<Audio::BlowBottle>(dev, a, ws);
	//else if (instrument == "blowhole")		CreateSynCoreInstrument<Audio::BlowHole>(dev, a, ws);
	else if (instrument == "bowed")			CreateSynCoreInstrument<Audio::Bowed>(dev, a, ws);
	else if (instrument == "brass")			CreateSynCoreInstrument<Audio::Brass>(dev, a, ws);
	else if (instrument == "clarinet")		CreateSynCoreInstrument<Audio::Clarinet>(dev, a, ws);
	//else if (instrument == "drummer")		CreateSynCoreInstrument<Audio::Drummer>(dev, a, ws);
	//else if (instrument == "guitar")		CreateSynCoreInstrument<Audio::Guitar>(dev, a, ws);
	else if (instrument == "heavymetal")	CreateSynCoreInstrument<Audio::HeavyMetal>(dev, a, ws);
	else if (instrument == "mandolin")		CreateSynCoreInstrument<Audio::Mandolin>(dev, a, ws);
	//else if (instrument == "mesh2d")		CreateSynCoreInstrument<Audio::Mesh2D>(dev, a, ws);
	else if (instrument == "modalbar")		CreateSynCoreInstrument<Audio::ModalBar>(dev, a, ws);
	else if (instrument == "moog")			CreateSynCoreInstrument<Audio::Moog>(dev, a, ws);
	else if (instrument == "percflut")		CreateSynCoreInstrument<Audio::PercFlut>(dev, a, ws);
	else if (instrument == "plucked")		CreateSynCoreInstrument<Audio::Plucked>(dev, a, ws);
	//else if (instrument == "resonate")		CreateSynCoreInstrument<Audio::Resonate>(dev, a, ws);
	else if (instrument == "rhodey")		CreateSynCoreInstrument<Audio::Rhodey>(dev, a, ws);
	//else if (instrument == "saxofony")		CreateSynCoreInstrument<Audio::Saxofony>(dev, a, ws);
	else if (instrument == "shakers")		CreateSynCoreInstrument<Audio::Shakers>(dev, a, ws);
	else if (instrument == "simple")		CreateSynCoreInstrument<Audio::Simple>(dev, a, ws);
	else if (instrument == "sitar")			CreateSynCoreInstrument<Audio::Sitar>(dev, a, ws);
	//else if (instrument == "stifkarp")		CreateSynCoreInstrument<Audio::StifKarp>(dev, a, ws);
	else if (instrument == "tubebell")		CreateSynCoreInstrument<Audio::TubeBell>(dev, a, ws);
	else if (instrument == "voiceformant")	CreateSynCoreInstrument<Audio::VoiceFormant>(dev, a, ws);
	//else if (instrument == "whistle")		CreateSynCoreInstrument<Audio::Whistle>(dev, a, ws);
	else if (instrument == "wurley")		CreateSynCoreInstrument<Audio::Wurley>(dev, a, ws);
	else {
		LOG("SynCoreSynth::Instrument_Initialize: error: unrecognized instrument: " << instrument);
		return false;
	}
	
	dev.seq = 0;
	dev.multiplier = 1;
	dev.sample_rate = ws.GetInt(".samplerate", 1024);
	
	ISourceRef src = a.GetSource();
	int c = src->GetSourceCount();
	Value& v = src->GetSourceValue(c-1);
	Format fmt = v.GetFormat();
	if (!fmt.IsAudio())
		return false;
	
	AudioFormat& afmt = fmt;
	afmt.SetType(BinarySample::FLT_LE);
	afmt.SetSampleRate(dev.sample_rate);
	for(int i = 0; i < dev.voices.GetCount(); i++) {
		Audio::Instrument& instrument = dev.voices[i];
		instrument.SetSampleRate(afmt.freq);
	}
	
	v.SetFormat(fmt);
	
	return true;
}

bool SynCoreSynth::Instrument_PostInitialize(NativeInstrument& dev, AtomBase& a) {
	return true;
}

bool SynCoreSynth::Instrument_Start(NativeInstrument& dev, AtomBase& a) {
	return true;
}

void SynCoreSynth::Instrument_Stop(NativeInstrument& dev, AtomBase& a) {
	
}

void SynCoreSynth::Instrument_Uninitialize(NativeInstrument& dev, AtomBase& a) {
	
}

bool SynCoreSynth::Instrument_Send(NativeInstrument& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
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
			
			Audio::Instrument& instrument = dev.voices[i];
			float* f = begin;
			const Audio::AudioFrames& last_frame = instrument.GetLastFrame();
			int frame_channel_count = last_frame.GetChannelCount();
			float mul = dev.multiplier;
			for(int i = 0; i < sr; i++) {
				float v = instrument.Tick() * mul + *f;
				float av = fabsf(v);
				if (av > abs_max)
					abs_max = av;
				*f++ = v;
				
				for (int j = 1; j < frame_channel_count; j++ )
					*f++ += last_frame[j];
				for (int j = frame_channel_count; j < channel_count; j++ ) {
					float prev = f[-1];
					*f++ += prev;
				}
			}
		}
		
		if (abs_max > 1.0f) {
			float mul = (1.0f / abs_max) * 0.99;
			dev.multiplier *= mul;
			float* f = begin;
			for(int i = 0; i < sr; i++)
				for (int j = 0; j < channel_count; j++ )
					*f++ *= mul;
		}
		
		#if HAVE_PACKETTIMING
		out.SetBeginTime();
		#endif
	}
	return true;
}

bool SynCoreSynth::Instrument_Recv(NativeInstrument& dev, AtomBase& a, int sink_ch, const Packet& in) {
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

void SynCoreSynth::Instrument_Finalize(NativeInstrument& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool SynCoreSynth::Instrument_IsReady(NativeInstrument& dev, AtomBase& a, PacketIO& io) {
	// Primary sink is required always (continuous audio) so ignore midi input, which is mixed
	// to primary occasionally.
	return (io.active_sink_mask & 0x1) && io.full_src_mask == 0;
}





NAMESPACE_PARALLEL_END
#endif

