// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IAvFile_TmplClasses_h_
#define _IAvFile_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class AV> struct AvFileAVFileT;


template <class AV>
struct AvFileAVFileT : AVAVFile {
	typename AV::NativeAVFile file;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!AV::AVFile_Initialize(file, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		AV::AVFile_Uninitialize(file);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!AV::AVFile_ProcessPacket(file, v))
			return false;
		return true;
	}

	bool CreateAVFile() {
		return AV::AVFile_CreateAVFile(this->file);
	}
	
	void ClearAVFile() {
		AV::AVFile_ClearAVFile(this->file);
	}
	
	
};



NAMESPACE_PARALLEL_END



#endif

