#ifndef _AtomAudio_Generated_h_
#define _AtomAudio_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

class MidiFileReaderPipe : public MidiFileReaderAtom {

public:
	RTTI_DECL1(MidiFileReaderPipe, MidiFileReaderAtom)
	COPY_PANIC(MidiFileReaderPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("midi.file.reader.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class MidiFileReader : public MidiFileReaderAtom {

public:
	RTTI_DECL1(MidiFileReader, MidiFileReaderAtom)
	COPY_PANIC(MidiFileReader)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("midi.file.reader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class MidiNullSink : public MidiNullAtom {

public:
	RTTI_DECL1(MidiNullSink, MidiNullAtom)
	COPY_PANIC(MidiNullSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("midi.null.sink")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class FluidsynthPipe : public FluidsynthInstrument {

public:
	RTTI_DECL1(FluidsynthPipe, FluidsynthInstrument)
	COPY_PANIC(FluidsynthPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("fluidsynth.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SoftInstrumentPipe : public SoftInstrument {

public:
	RTTI_DECL1(SoftInstrumentPipe, SoftInstrument)
	COPY_PANIC(SoftInstrumentPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("softinstru.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class FmSynthPipe : public FmSynthInstrument {

public:
	RTTI_DECL1(FmSynthPipe, FmSynthInstrument)
	COPY_PANIC(FmSynthPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("fmsynth.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class CoreSynthPipe : public CoreSynthInstrument {

public:
	RTTI_DECL1(CoreSynthPipe, CoreSynthInstrument)
	COPY_PANIC(CoreSynthPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("coresynth.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

using MidiFileReaderPipeRef = Ref<MidiFileReaderPipe, AtomParent>;

using MidiFileReaderRef = Ref<MidiFileReader, AtomParent>;

using MidiNullSinkRef = Ref<MidiNullSink, AtomParent>;

using FluidsynthPipeRef = Ref<FluidsynthPipe, AtomParent>;

using SoftInstrumentPipeRef = Ref<SoftInstrumentPipe, AtomParent>;

using FmSynthPipeRef = Ref<FmSynthPipe, AtomParent>;

using CoreSynthPipeRef = Ref<CoreSynthPipe, AtomParent>;

}

}



#endif
