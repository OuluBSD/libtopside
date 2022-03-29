// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IImageFile_TmplClasses_h_
#define _IImageFile_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Img> struct ImageFileImageT;


template <class Img>
struct ImageFileImageT : ImgImage {
	typename Img::NativeImage img;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Img::Image_Initialize(img, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Img::Image_Uninitialize(img);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Img::Image_ProcessPacket(img, v))
			return false;
		return true;
	}

	bool CreateImage() {
		return Img::Image_CreateImage(this->img);
	}
	
	void ClearImage() {
		Img::Image_ClearImage(this->img);
	}
	
	
};



NAMESPACE_PARALLEL_END



#endif

