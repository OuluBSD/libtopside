#include "ISynth.h"
#include <ports/lilv/lilv.h>
#include <ports/lilv/lilv_config.h>
#include <ports/lilv/lilvmm.hpp>
#include <LV2Host/LV2Host.h>


NAMESPACE_PARALLEL_BEGIN


struct SynLV2::NativeInstrument {
    Index<String> lv2_list;
    One<Lv2Host> host;
    
};


bool SynLV2::Instrument_Create(One<NativeInstrument>& dev){
	dev.Create();
	return true;
}

void SynLV2::Instrument_Destroy(One<NativeInstrument>& dev){
	dev.Clear();
}

bool SynLV2::Instrument_Initialize(NativeInstrument& dev, AtomBase& a, const Script::WorldState& ws){
	String preset = ws.GetString("preset", "piano");
	
	LoadAllLV2Plugins(dev.lv2_list);
	
	String plugin_uri = ws.GetString("path", "");
	
	if (plugin_uri.IsEmpty()) {
		plugin_uri = FindLv2InstrumentForPreset(preset, dev.lv2_list);
	}
	
	if (plugin_uri.IsEmpty()) {
		LOG("SynLV2::Instrument_Initialize: error: empty lv2 uri '" << plugin_uri << "'");
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
	
	ASSERT(plugin_uri.GetCount());
	dev.host = new Lv2Host(0, freq, sample_rate, plugin_uri);
	if (dev.host.IsEmpty() || !dev.host->IsInitialized()) {
		LOG("SynLV2::Instrument_Initialize: error: could not load lv2 uri '" << plugin_uri << "' with"
			" frequency " << freq <<
			", sample-rate " << sample_rate);
		return false;
	}
	
	return true;
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

bool SynLV2::Instrument_Recv(NativeInstrument&, AtomBase&, int, const Packet&) {
	
}

void SynLV2::Instrument_Finalize(NativeInstrument&, AtomBase&, RealtimeSourceConfig&) {
	
}

bool SynLV2::Instrument_IsReady(NativeInstrument&, AtomBase&, PacketIO& io) {
	
}


NAMESPACE_PARALLEL_END
