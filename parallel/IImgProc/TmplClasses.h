// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IImgProc_TmplClasses_h_
#define _IImgProc_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Imp> struct ImgProcImageT;


template <class Imp>
struct ImgProcImageT : ImpImage {
	typename Imp::NativeImage dev;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Imp::Image_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Imp::Image_Uninitialize(dev);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Imp::Image_ProcessPacket(dev, v))
			return false;
		return true;
	}

	bool CreateImage() {
		return Imp::Image_CreateImage(this->dev);
	}
	
	void ClearImage() {
		Imp::Image_ClearImage(this->dev);
	}
	
	
};



NAMESPACE_PARALLEL_END



#endif

