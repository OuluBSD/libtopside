#include "IMidiHw.h"

#if defined flagPORTMIDI

#if defined flagBUILTIN_PORTMIDI || (defined flagWIN32 && defined flagMSC) || flagFREEBSD
	#include <ports/portmidi/portmidi.h>
	#include <ports/portmidi/pmutil.h>
	#include <ports/portmidi/porttime.h>
#else
	#include <portmidi.h>
	#include <porttime.h>
#endif


// see Sequencer/Midi.h


NAMESPACE_PARALLEL_BEGIN

bool MidPortmidi::Source_Initialize(NativeSource& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

bool MidPortmidi::Source_PostInitialize(NativeSource& dev, AtomBase& a) {
	TODO
}

bool MidPortmidi::Source_Start(NativeSource& dev, AtomBase& a) {
	TODO
}

void MidPortmidi::Source_Stop(NativeSource& dev, AtomBase& a) {
	TODO
}

void MidPortmidi::Source_Uninitialize(NativeSource& dev, AtomBase& a) {
	TODO
}

bool MidPortmidi::Source_Send(NativeSource& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

bool MidPortmidi::Source_IsReady(NativeSource& dev, AtomBase& a, PacketIO& io) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

