#include "ISynth.h"
#include <MidiFile/MidiFile.h>


NAMESPACE_PARALLEL_BEGIN

struct SynSoft::NativeInstrument {
    SoftInstru::Instrument instrument;
    bool sf_loaded;
    int sample_rate;
};



bool SynSoft::Instrument_Create(NativeInstrument*& dev) {
	dev = new NativeInstrument;
	return true;
}

void SynSoft::Instrument_Destroy(NativeInstrument*& dev) {
	delete dev;
}

void SynSoft::Instrument_Visit(NativeInstrument& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool SynSoft::Instrument_Initialize(NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.sample_rate = 1024;
	
	//String sf2 = ws.GetString(".filepath", "FluidR3_GM.sf2");
	String sf2 = ws.GetString(".filepath", "TimGM6mb.sf2");
	sf2 = RealizeShareFile(sf2);
	
	if (!dev.instrument.LoadFilename(sf2)) {
		LOG("SynSoft::Instrument_Initialize: error: could not load sf2: "<< sf2);
		return false;
	}
	
	ISourceRef src = a.GetSource();
	int c = src->GetSourceCount();
	Value& v = src->GetSourceValue(c-1);
	Format fmt = v.GetFormat();
	if (!fmt.IsAudio())
		return false;
	
	AudioFormat& afmt = fmt;
	//afmt.SetType(BinarySample::S16_LE);
	afmt.SetType(BinarySample::FLT_LE);
	afmt.SetSampleRate(dev.sample_rate);
	v.SetFormat(fmt);
	
	
	// Initialize preset on special 10th MIDI channel to use percussion sound bank (128) if available
	dev.instrument.SetChannelBankPreset(9, 128, 0);
	dev.instrument.SetOutput(SoftInstru::STEREO_INTERLEAVED, (int)afmt.freq, -9);
	
	
	//a.SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	
	return true;
}

bool SynSoft::Instrument_PostInitialize(NativeInstrument& dev, AtomBase& a) {
    return true;
}

bool SynSoft::Instrument_Start(NativeInstrument& dev, AtomBase& a) {
    return true;
}

void SynSoft::Instrument_Stop(NativeInstrument& dev, AtomBase& a) {
	
}

void SynSoft::Instrument_Uninitialize(NativeInstrument& dev, AtomBase& a) {
	
}

bool SynSoft::Instrument_Send(NativeInstrument& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	if (fmt.IsAudio()) {
		AudioFormat& afmt = fmt;
		int sr = afmt.GetSampleRate();
		ASSERT(sr == dev.sample_rate);
		ASSERT(afmt.GetSize() == 2);
		
		Vector<byte>& data = out.Data();
		int sz = afmt.GetFrameSize();
		data.SetCount(sz);
		
		if (afmt.GetType() == BinarySample::S16_LE)
			dev.instrument.RenderShort((short*)(byte*)data.Begin(), dev.sample_rate, 0);
		else if (afmt.GetType() == BinarySample::FLT_LE)
			dev.instrument.RenderFloat((float*)(byte*)data.Begin(), dev.sample_rate, 0);
	}
	return true;
}

bool SynSoft::Instrument_Recv(NativeInstrument& dev, AtomBase& a, int sink_ch, const Packet& in) {
	Format fmt = in->GetFormat();
	if (fmt.IsMidi()) {
		const Vector<byte>& data = in->Data();
		int count = data.GetCount() / sizeof(MidiIO::Event);
		
		const MidiIO::Event* ev  = (const MidiIO::Event*)(const byte*)data.Begin();
		const MidiIO::Event* end = ev + count;
		
		while (ev != end) {
			dev.instrument.HandleEvent(*ev);
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

void SynSoft::Instrument_Finalize(NativeInstrument& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool SynSoft::Instrument_IsReady(NativeInstrument& dev, AtomBase& a, PacketIO& io) {
	// Primary sink is required always (continuous audio) so ignore midi input, which is mixed
	// to primary occasionally.
	return (io.active_sink_mask & 0x1) && io.full_src_mask == 0;
}





NAMESPACE_PARALLEL_END

