#include "IEffect.h"
#include <SerialMach/SerialMach.h>


#if 1
NAMESPACE_PARALLEL_BEGIN


struct FxAudioCore::NativeEffect {
    One<Audio::Effect> effect;
    int channel_count;
    int sample_rate;
    int prim_audio_sink_ch;
    dword packet_in_mask;
    Packet last_audio_in;
    ArrayMap<int, Packet> last_audio_side_in;
    Vector<float> buffer;
    float buffer_time;
};




bool FxAudioCore::Effect_Create(NativeEffect*& dev) {
	dev = new NativeEffect;
	return true;
}

void FxAudioCore::Effect_Destroy(NativeEffect*& dev) {
	delete dev;
}

void FxAudioCore::Effect_Visit(NativeEffect& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

template <class T>
void CreateSynCoreEffect(FxAudioCore::NativeEffect& dev, AtomBase& a, const Script::WorldState& ws) {
	T* t = new T();
	t->LoadState(ws.GetValues());
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
	else if (instrument == "compressor")		CreateSynCoreEffect<Audio::Compressor>(dev, a, ws);
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
	
	dev.sample_rate = ws.GetInt(".samplerate", 128);
	{
		ISinkRef sink = a.GetSink();
		int c = sink->GetSinkCount();
		
		dev.prim_audio_sink_ch = -1;
		float freq = 0;
		for(int i = 0; i < c; i++) {
			Value& v = sink->GetValue(i);
			Format fmt = v.GetFormat();
			if (fmt.IsAudio()) {
				AudioFormat& afmt = fmt;
				if (dev.prim_audio_sink_ch < 0) {
					freq = (float)afmt.freq;
					dev.prim_audio_sink_ch = i;
				}

				afmt.SetType(BinarySample::FLT_LE);
				afmt.SetSampleRate(dev.sample_rate);
				v.SetFormat(fmt);
			}
		}
		if (dev.prim_audio_sink_ch < 0)
			return false;
		
		
		dev.effect->SetSampleRate(freq);
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
		dev.effect->SetSampleRate((float)afmt.freq);
		
		v.SetFormat(fmt);
	}
	
	return true;
}

bool FxAudioCore::Effect_PostInitialize(NativeEffect& dev, AtomBase& a) {
	dev.packet_in_mask = 0x1;
	dev.packet_in_mask |= 1 << dev.prim_audio_sink_ch;
	Serial::Link* lb = a.GetLink();
	const auto& srcs = lb->SideSources();
	for(const auto& src : srcs) {
		int ch = src.local_ch_i;
		dev.packet_in_mask |= 1 << ch;
	}
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
	if (fmt.IsAudio()) {
		if (dev.buffer.GetCount()) {
			Vector<byte>& d = out.Data();
			int bytes = dev.buffer.GetCount() * sizeof(float);
			d.SetCount(bytes, 0);
			float* f = (float*)(byte*)d.Begin();
			memcpy(f, dev.buffer.Begin(), bytes);
		}
		out.SetAge(dev.buffer_time);
		ASSERT(dev.buffer_time);
	}
	return true;
}

bool FxAudioCore::Effect_Recv(NativeEffect& dev, AtomBase& a, int sink_ch, const Packet& in) {
	Format fmt = in->GetFormat();
	if (fmt.IsAudio()) {
		if (sink_ch == dev.prim_audio_sink_ch)
			dev.last_audio_in = in;
		else
			dev.last_audio_side_in.GetAdd(sink_ch) = in;
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
	if (dev.last_audio_in) {
		if (dev.last_audio_side_in.IsEmpty()) {
			Format fmt = dev.last_audio_in->GetFormat();
			
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
			
			dev.buffer.SetCount(sr * ch, 0);
			float* f = (float*)dev.buffer.Begin();
			
			Audio::Effect& fx = *dev.effect;
			ch = min(ch, dev.channel_count);
			
			for(int i = 0; i < sr; i++) {
				for(int j = 0; j < ch; j++) {
					float iv = *in_f++;
					float ov = fx.Tick(iv, j);
					*f++ = ov;
				}
			}
			
			dev.buffer_time = (float)dev.last_audio_in->GetBeginTime();
			dev.last_audio_in.Clear();
		}
		else {
			Format fmt = dev.last_audio_in->GetFormat();
			
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
			
			
			const float* side_in_f[16];
			const int side_c = min(16,dev.last_audio_side_in.GetCount());
			for(int i = 0; i < side_c; i++) {
				Packet& side_p = dev.last_audio_side_in[i];
				const Vector<byte>& side_in = side_p->Data();
				side_in_f[i] = (const float*)(const byte*)side_in.Begin();
			}
			
			dev.buffer.SetCount(afmt.GetSampleRate() * afmt.GetSize(), 0);
			float* f = (float*)dev.buffer.Begin();
			
			Audio::Effect& fx = *dev.effect;
			ch = min(ch, dev.channel_count);
			
			for(int i = 0; i < sr; i++) {
				for(int j = 0; j < ch; j++) {
					float iv = *in_f++;
					float siv = 0;
					for(int k = 0; k < side_c; k++)
						siv += *side_in_f[k]++;
					float ov = fx.Tick2(iv, siv, j);
					*f++ = ov;
				}
			}
			
			dev.buffer_time = (float)dev.last_audio_in->GetBeginTime();
			dev.last_audio_in.Clear();
			dev.last_audio_side_in.Clear();
		}
	}
}

bool FxAudioCore::Effect_IsReady(NativeEffect& dev, AtomBase& a, PacketIO& io) {
	// Primary sink is required always (continuous audio) so ignore midi input, which is mixed
	// to primary occasionally.
	bool b = ((io.active_sink_mask & dev.packet_in_mask) == dev.packet_in_mask) && io.full_src_mask == 0;
	return b;
}





NAMESPACE_PARALLEL_END
#endif

