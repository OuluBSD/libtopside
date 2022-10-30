#include "AtomAudio.h"

// This file is generated. Do not modify this file.

INITBLOCK_(AtomAudio) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	Factory::RegisterAtom<MidiFileReaderPipe>();
	Factory::RegisterAtom<MidiFileReader>();
	Factory::RegisterAtom<MidiFileReader16>();
	Factory::RegisterAtom<MidiNullSink>();
	#if (defined flagFLUIDLITE) || (defined flagFLUIDSYNTH)
	Factory::RegisterAtom<FluidsynthPipe>();
	#endif
	Factory::RegisterAtom<SoftInstrumentPipe>();
	Factory::RegisterAtom<FmSynthPipe>();
	#if defined flagLV2
	Factory::RegisterAtom<LV2InstrumentPipe>();
	#endif
	Factory::RegisterAtom<CoreSynthPipe>();
	Factory::RegisterAtom<CoreDrummerPipe>();
	Factory::RegisterAtom<CoreEffectPipe>();
	Factory::RegisterAtom<CoreEffectAtom>();
	#if defined flagLV2
	Factory::RegisterAtom<LV2EffectPipe>();
	#endif
	#if (defined flagBUILTIN_PORTMIDI) || (defined flagPORTMIDI)
	Factory::RegisterAtom<PortmidiPipe>();
	#endif
	#if (defined flagBUILTIN_PORTMIDI) || (defined flagPORTMIDI)
	Factory::RegisterAtom<PortmidiSend>();
	#endif
	Factory::RegisterAtom<CoreAudioFileOut>();
}

