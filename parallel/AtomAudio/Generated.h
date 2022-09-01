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

#if defined flagFLUIDSYNTH
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

}

}
#endif
