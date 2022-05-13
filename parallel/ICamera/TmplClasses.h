// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ICamera_TmplClasses_h_
#define _ICamera_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Cam> struct CameraCameraT;



template <class Cam>
struct CameraCameraT : CamCamera {
	using CLASSNAME = CameraCameraT<Cam>;
	RTTI_DECL1(CLASSNAME, CamCamera)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<CamCamera>(this);}
	
	typename Cam::NativeCamera dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Cam::Camera_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Cam::Camera_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Cam::Camera_Start(dev, *this);
	}

	void Stop() override {
		Cam::Camera_Stop(dev, *this);
	}

	void Uninitialize() override {
		Cam::Camera_Uninitialize(dev, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Cam::Camera_Send(dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool IsReady(PacketIO& io) override {
		return Cam::Camera_IsReady(dev, *this, io);
	}

	
};

#if defined flagOPENCV && defined flagLINUX
using V4L2OpenCVCamera = CameraCameraT<CamV4L2OpenCV>;
#endif


NAMESPACE_PARALLEL_END

#endif

