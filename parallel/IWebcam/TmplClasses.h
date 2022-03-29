// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IWebcam_TmplClasses_h_
#define _IWebcam_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Cam> struct WebcamWebcamT;


template <class Cam>
struct WebcamWebcamT : CamWebcam {
	typename Cam::NativeWebcam dev;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Cam::Webcam_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Cam::Webcam_Uninitialize(dev);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Cam::Webcam_ProcessPacket(dev, v))
			return false;
		return true;
	}

	bool CreateWebcam() {
		return Cam::Webcam_CreateWebcam(this->dev);
	}
	
	void ClearWebcam() {
		Cam::Webcam_ClearWebcam(this->dev);
	}
	
	
};



NAMESPACE_PARALLEL_END



#endif

