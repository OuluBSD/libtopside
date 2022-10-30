#include "AtomAudio.h"

NAMESPACE_UPP


INITBLOCK_(AtomAudio) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	
	Factory::RegisterAtom<MidiFileReader>();
	Factory::RegisterAtom<MidiFileReader16>();
	Factory::RegisterAtom<MidiFileReaderPipe>();
	Factory::RegisterAtom<MidiNullSink>();
	#if defined flagFLUIDSYNTH || defined flagFLUIDLITE
	Factory::RegisterAtom<FluidsynthPipe>();
	#endif
	Factory::RegisterAtom<SoftInstrumentPipe>();
	Factory::RegisterAtom<FmSynthPipe>();
	Factory::RegisterAtom<CoreSynthPipe>();
	Factory::RegisterAtom<CoreDrummerPipe>();
	Factory::RegisterAtom<CoreEffectPipe>();
	Factory::RegisterAtom<CoreEffectAtom>();
	#ifdef flagLV2
	Factory::RegisterAtom<LV2InstrumentPipe>();
	Factory::RegisterAtom<LV2EffectPipe>();
	#endif
	#if (defined flagBUILTIN_PORTMIDI) || (defined flagPORTMIDI)
	Factory::RegisterAtom<PortmidiPipe>();
	Factory::RegisterAtom<PortmidiSend>();
	#endif
	Factory::RegisterAtom<CoreAudioFileOut>();
	
}


END_UPP_NAMESPACE
