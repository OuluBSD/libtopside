#include "ISynth.h"

NAMESPACE_PARALLEL_BEGIN


struct SynLV2::NativeInstrument {
    
};


bool SynLV2::Instrument_Create(One<NativeInstrument>& dev){
	dev.Create();
	return true;
}

void SynLV2::Instrument_Destroy(One<NativeInstrument>& dev){
	dev.Clear();
}

bool SynLV2::Instrument_Initialize(NativeInstrument&, AtomBase&, const Script::WorldState& ws){
	String preset = ws.GetString("preset", "piano");
	
	
	
}

bool SynLV2::Instrument_PostInitialize(NativeInstrument&, AtomBase&){
	
}

bool SynLV2::Instrument_Start(NativeInstrument&, AtomBase&){
	
}

void SynLV2::Instrument_Stop(NativeInstrument&, AtomBase&){
	
}

void SynLV2::Instrument_Uninitialize(NativeInstrument&, AtomBase&){
	
}

bool SynLV2::Instrument_Send(NativeInstrument&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch){
	
}

void SynLV2::Instrument_Visit(NativeInstrument&, AtomBase&, RuntimeVisitor& vis){
	
}

bool SynLV2::Instrument_Recv(NativeInstrument&, AtomBase&, int, const Packet&){
	
}

void SynLV2::Instrument_Finalize(NativeInstrument&, AtomBase&, RealtimeSourceConfig&){
	
}

bool SynLV2::Instrument_IsReady(NativeInstrument&, AtomBase&, PacketIO& io){
	
}


NAMESPACE_PARALLEL_END
