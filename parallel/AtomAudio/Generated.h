#ifndef _AtomAudio_Generated_h_
#define _AtomAudio_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

class MidiFileReaderPipe : public MidiFileReaderAtom {

public:
	RTTI_DECL1(MidiFileReaderPipe, MidiFileReaderAtom)
	COPY_PANIC(MidiFileReaderPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class MidiFileReader : public MidiFileReaderAtom {

public:
	RTTI_DECL1(MidiFileReader, MidiFileReaderAtom)
	COPY_PANIC(MidiFileReader)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class MidiFileReader16 : public MidiFileReaderAtom {

public:
	RTTI_DECL1(MidiFileReader16, MidiFileReaderAtom)
	COPY_PANIC(MidiFileReader16)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class MidiNullSink : public MidiNullAtom {

public:
	RTTI_DECL1(MidiNullSink, MidiNullAtom)
	COPY_PANIC(MidiNullSink)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if (defined flagFLUIDLITE) || (defined flagFLUIDSYNTH)
class FluidsynthPipe : public FluidsynthInstrument {

public:
	RTTI_DECL1(FluidsynthPipe, FluidsynthInstrument)
	COPY_PANIC(FluidsynthPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

class SoftInstrumentPipe : public SoftInstrument {

public:
	RTTI_DECL1(SoftInstrumentPipe, SoftInstrument)
	COPY_PANIC(SoftInstrumentPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class FmSynthPipe : public FmSynthInstrument {

public:
	RTTI_DECL1(FmSynthPipe, FmSynthInstrument)
	COPY_PANIC(FmSynthPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if defined flagLV2
class LV2InstrumentPipe : public LV2Instrument {

public:
	RTTI_DECL1(LV2InstrumentPipe, LV2Instrument)
	COPY_PANIC(LV2InstrumentPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

class CoreSynthPipe : public CoreSynthInstrument {

public:
	RTTI_DECL1(CoreSynthPipe, CoreSynthInstrument)
	COPY_PANIC(CoreSynthPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class CoreDrummerPipe : public CoreDrummerInstrument {

public:
	RTTI_DECL1(CoreDrummerPipe, CoreDrummerInstrument)
	COPY_PANIC(CoreDrummerPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class CoreEffectPipe : public AudioCoreEffect {

public:
	RTTI_DECL1(CoreEffectPipe, AudioCoreEffect)
	COPY_PANIC(CoreEffectPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class CoreEffectAtom : public AudioCoreEffect {

public:
	RTTI_DECL1(CoreEffectAtom, AudioCoreEffect)
	COPY_PANIC(CoreEffectAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if defined flagLV2
class LV2EffectPipe : public LV2Effect {

public:
	RTTI_DECL1(LV2EffectPipe, LV2Effect)
	COPY_PANIC(LV2EffectPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagBUILTIN_PORTMIDI) || (defined flagPORTMIDI)
class PortmidiPipe : public PortmidiSource {

public:
	RTTI_DECL1(PortmidiPipe, PortmidiSource)
	COPY_PANIC(PortmidiPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagBUILTIN_PORTMIDI) || (defined flagPORTMIDI)
class PortmidiSend : public PortmidiSource {

public:
	RTTI_DECL1(PortmidiSend, PortmidiSource)
	COPY_PANIC(PortmidiSend)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

class CoreAudioFileOut : public CoreAudioSink {

public:
	RTTI_DECL1(CoreAudioFileOut, CoreAudioSink)
	COPY_PANIC(CoreAudioFileOut)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

}

}
#endif
