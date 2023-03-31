#include "ISynth.h"

#ifdef flagLV2

#include <ports/lilv/lilv.h>
#include <ports/lilv/lilv_config.h>
#include <ports/lilv/lilvmm.hpp>
#include <AudioHost/AudioHost.h>


NAMESPACE_PARALLEL_BEGIN


struct SynLV2::NativeInstrument {
    Index<String> lv2_list;
    One<Lv2Host> host;
    int nframes;
};


bool SynLV2::Instrument_Create(NativeInstrument*& dev){
	dev = new NativeInstrument;
	return true;
}

void SynLV2::Instrument_Destroy(NativeInstrument*& dev){
	delete dev;
}

bool SynLV2::Instrument_Initialize(NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws){
	String preset = ws.GetString("preset", "piano");
	
	LoadAllLV2Plugins(dev.lv2_list);
	
	dev.nframes = ws.GetInt(".nframes", 128);
	
	String plugin_uri = ws.GetString(".path", "");
	Index<String> plugin_uris;
	
	if (plugin_uri.GetCount()) {
		plugin_uris.Add(plugin_uri);
	}
	else {
		GetLv2InstrumentCandidates(preset, dev.lv2_list, plugin_uris);
	}
	
	if (plugin_uris.IsEmpty()) {
		LOG("SynLV2::Instrument_Initialize: error: empty lv2 uri");
		return false;
	}
	
	ISourceRef src = a.GetSource();
	int c = src->GetSourceCount();
	Value& v = src->GetSourceValue(c-1);
	Format fmt = v.GetFormat();
	if (!fmt.IsAudio()) {
		LOG("SynLV2::Instrument_Initialize: error: internal error");
		return false;
	}
	
	AudioFormat& afmt = fmt;
	int sample_rate = afmt.GetSampleRate();
	int freq = afmt.GetFrequency();
	
	for (String plugin_uri : plugin_uris) {
		ASSERT(plugin_uri.GetCount());
		dev.host = new Lv2Host(0, freq, sample_rate, plugin_uri);
		if (dev.host && dev.host->IsInitialized()) {
			return true;
		}
	}
	
	LOG("SynLV2::Instrument_Initialize: error: could not load lv2 preset '" + preset + "' with"
		" frequency " << freq <<
		", sample-rate " << sample_rate);
	
	return false;
}

bool SynLV2::Instrument_PostInitialize(NativeInstrument&, AtomBase&) {
	return true;
}

bool SynLV2::Instrument_Start(NativeInstrument&, AtomBase&) {
	return true;
}

void SynLV2::Instrument_Stop(NativeInstrument&, AtomBase&) {
	
}

void SynLV2::Instrument_Uninitialize(NativeInstrument&, AtomBase&) {
	
}

bool SynLV2::Instrument_Send(NativeInstrument&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	
}

void SynLV2::Instrument_Visit(NativeInstrument&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool SynLV2::Instrument_Recv(NativeInstrument& dev, AtomBase& a, int src_ch, const Packet& p) {
	Format fmt = p->GetFormat();
	
	if (fmt.IsMidi()) {
		const Vector<byte>& data = p->Data();
		int count = data.GetCount() / sizeof(MidiIO::Event);
		
		const MidiIO::Event* ev  = (const MidiIO::Event*)(const byte*)data.Begin();
		const MidiIO::Event* end = ev + count;
		
		while (ev != end) {
			dev.host->HandleEvent(*ev);
			ev++;
		}
		return true;
	}
	else if (fmt.IsOrder()) {
		// pass
	}
	else return false;
	
	return true;
}

void SynLV2::Instrument_Finalize(NativeInstrument&, AtomBase&, RealtimeSourceConfig&) {
	
}

bool SynLV2::Instrument_IsReady(NativeInstrument&, AtomBase&, PacketIO& io) {
	return io.active_sink_mask & 0x1;
}


NAMESPACE_PARALLEL_END

#endif
