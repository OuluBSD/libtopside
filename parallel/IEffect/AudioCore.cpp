#include "IEffect.h"

#if 1
NAMESPACE_PARALLEL_BEGIN


struct FxAudioCore::NativeEffect {
    One<Audio::Effect> effect;
    int channel_count;
    int sample_rate;
    Packet last_audio_in;
};




bool FxAudioCore::Effect_Create(One<NativeEffect>& dev) {
	dev.Create();
	return true;
}

void FxAudioCore::Effect_Destroy(One<NativeEffect>& dev) {
	dev.Clear();
}

void FxAudioCore::Effect_Visit(NativeEffect& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

template <class T>
void CreateSynCoreEffect(FxAudioCore::NativeEffect& dev, AtomBase& a, const Script::WorldState& ws) {
	T* t = new T();
	dev.effect = t;
}

bool FxAudioCore::Effect_Initialize(NativeEffect& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.channel_count = min(16, max(0, ws.GetInt(".channels", 2)));
	
	String instrument = ToLower(ws.GetString(".filter", "chorus"));
	
	if      (instrument == "chorus")			CreateSynCoreEffect<Audio::Chorus>(dev, a, ws);
	else if (instrument == "jcrev")				CreateSynCoreEffect<Audio::JCRev>(dev, a, ws);
	else if (instrument == "pitchshift")		CreateSynCoreEffect<Audio::PitchShift>(dev, a, ws);
	else if (instrument == "prcrev")			CreateSynCoreEffect<Audio::PRCRev>(dev, a, ws);
	else if (instrument == "echo")				CreateSynCoreEffect<Audio::Echo>(dev, a, ws);
	else if (instrument == "freeverb")			CreateSynCoreEffect<Audio::FreeVerb>(dev, a, ws);
	else if (instrument == "nrev")				CreateSynCoreEffect<Audio::NRev>(dev, a, ws);
	else if (instrument == "lentpitchshift")	CreateSynCoreEffect<Audio::LentPitchShift>(dev, a, ws);
	/*
	else if (instrument == "delay")			CreateSynCoreEffect<Audio::Delay>(dev, a, ws);
	else if (instrument == "delaya")		CreateSynCoreEffect<Audio::DelayA>(dev, a, ws);
	else if (instrument == "delayl")		CreateSynCoreEffect<Audio::DelayL>(dev, a, ws);
	else if (instrument == "fir")			CreateSynCoreEffect<Audio::Fir>(dev, a, ws);
	else if (instrument == "flute")			CreateSynCoreEffect<Audio::Flute>(dev, a, ws);
	else if (instrument == "formswep")		CreateSynCoreEffect<Audio::FormSwep>(dev, a, ws);
	else if (instrument == "iir")			CreateSynCoreEffect<Audio::Iir>(dev, a, ws);
	else if (instrument == "onepole")		CreateSynCoreEffect<Audio::OnePole>(dev, a, ws);
	else if (instrument == "onezero")		CreateSynCoreEffect<Audio::OneZero>(dev, a, ws);
	else if (instrument == "polezero")		CreateSynCoreEffect<Audio::PoleZero>(dev, a, ws);
	else if (instrument == "tapdelay")		CreateSynCoreEffect<Audio::TapDelay>(dev, a, ws);
	else if (instrument == "twopole")		CreateSynCoreEffect<Audio::TwoPole>(dev, a, ws);
	else if (instrument == "twozero")		CreateSynCoreEffect<Audio::TwoZero>(dev, a, ws);
	*/
	else {
		LOG("FxAudioCore::Effect_Initialize: error: unrecognized instrument: " << instrument);
		return false;
	}
	
	dev.sample_rate = ws.GetInt(".samplerate", 1024);
	{
		ISinkRef sink = a.GetSink();
		int c = sink->GetSinkCount();
		Value& v = sink->GetValue(c-1);
		Format fmt = v.GetFormat();
		if (!fmt.IsAudio())
			return false;
		
		AudioFormat& afmt = fmt;
		afmt.SetType(BinarySample::FLT_LE);
		afmt.SetSampleRate(dev.sample_rate);
		dev.effect->SetSampleRate(afmt.freq);
		
		v.SetFormat(fmt);
	}
	{
		ISourceRef src = a.GetSource();
		int c = src->GetSourceCount();
		Value& v = src->GetSourceValue(c-1);
		Format fmt = v.GetFormat();
		if (!fmt.IsAudio())
			return false;
		
		AudioFormat& afmt = fmt;
		afmt.SetType(BinarySample::FLT_LE);
		afmt.SetSampleRate(dev.sample_rate);
		dev.effect->SetSampleRate(afmt.freq);
		
		v.SetFormat(fmt);
	}
	
	return true;
}

bool FxAudioCore::Effect_PostInitialize(NativeEffect& dev, AtomBase& a) {
	return true;
}

bool FxAudioCore::Effect_Start(NativeEffect& dev, AtomBase& a) {
	return true;
}

void FxAudioCore::Effect_Stop(NativeEffect& dev, AtomBase& a) {
	
}

void FxAudioCore::Effect_Uninitialize(NativeEffect& dev, AtomBase& a) {
	
}

bool FxAudioCore::Effect_Send(NativeEffect& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	if (fmt.IsAudio() && dev.last_audio_in) {
		AudioFormat& afmt = fmt;
		int sr = afmt.GetSampleRate();
		int ch = afmt.GetSize();
		ASSERT(ch == dev.channel_count);
		ASSERT(afmt.IsSampleFloat());
		
		Format in_fmt = dev.last_audio_in->GetFormat();
		AudioFormat& in_afmt = in_fmt;
		int in_sr = in_afmt.GetSampleRate();
		const Vector<byte>& in = dev.last_audio_in->Data();
		const float* in_f = (const float*)(const byte*)in.Begin();
		
		Vector<byte>& d = out.Data();
		d.SetCount(afmt.GetFrameSize(), 0);
		float* f = (float*)(byte*)d.Begin();
		
		Audio::Effect& fx = *dev.effect;
		ch = min(ch, dev.channel_count);
		
		for(int i = 0; i < sr; i++) {
			for(int j = 0; j < ch; j++) {
				float iv = *in_f++;
				float ov = fx.Tick(iv, j);
				*f++ = ov;
			}
		}
		dev.last_audio_in.Clear();
	}
	return true;
}

bool FxAudioCore::Effect_Recv(NativeEffect& dev, AtomBase& a, int sink_ch, const Packet& in) {
	Format fmt = in->GetFormat();
	if (fmt.IsAudio()) {
		dev.last_audio_in = in;
	}
	else if (fmt.IsOrder()) {
		// pass
	}
	else {
		TODO
	}
	return true;
}

void FxAudioCore::Effect_Finalize(NativeEffect& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool FxAudioCore::Effect_IsReady(NativeEffect& dev, AtomBase& a, PacketIO& io) {
	// Primary sink is required always (continuous audio) so ignore midi input, which is mixed
	// to primary occasionally.
	return (io.active_sink_mask & 0x1) && io.full_src_mask == 0;
}





NAMESPACE_PARALLEL_END
#endif

