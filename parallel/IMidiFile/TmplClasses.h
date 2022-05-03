// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMidiFile_TmplClasses_h_
#define _IMidiFile_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Mif> struct MidiFileMidiFileT;


template <class Mif>
struct MidiFileMidiFileT : MifMidiFile {
	using CLASSNAME = MidiFileMidiFileT<Mif>;
	RTTI_DECL1(CLASSNAME, MifMidiFile)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<MifMidiFile>(this);}
	
	typename Mif::NativeMidiFile file;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Mif::MidiFile_Initialize(file, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Mif::MidiFile_PostInitialize(file, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Mif::MidiFile_Start(file, *this);
	}

	void Stop() override {
		Mif::MidiFile_Stop(file, *this);
	}

	void Uninitialize() override {
		Mif::MidiFile_Uninitialize(file, *this);
	}

	bool Send(PacketValue& out, int src_ch) override {
		if (!Mif::MidiFile_Send(file, *this, out))
			return false;
		return true;
	}

	bool CreateMidiFile() {
		return Mif::MidiFile_CreateMidiFile(this->file);
	}
	
	void ClearMidiFile() {
		Mif::MidiFile_ClearMidiFile(this->file);
	}
	
	
};


NAMESPACE_PARALLEL_END



#endif

