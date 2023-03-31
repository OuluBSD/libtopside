// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ICamera_ICamera_h_
#define _ICamera_ICamera_h_

#include <ParallelLib/ParallelLib.h>
#include <IMedia/IMedia.h>

NAMESPACE_PARALLEL_BEGIN

#define CAM_CLS_LIST(x) \
	CAM_CLS(Camera, x) \

#define CAM_VNDR_LIST \
	CAM_VNDR(CamV4L2OpenCV) \

#define CAM_CLS(x, v) struct v##x;
#define CAM_VNDR(x) CAM_CLS_LIST(x)
CAM_VNDR_LIST
#undef CAM_VNDR
#undef CAM_CLS

#if (defined flagOPENCV && defined flagLINUX)
struct CamV4L2OpenCV {
	struct NativeCamera;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

struct CamCamera : public Atom {
	RTTI_DECL1(CamCamera, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~CamCamera() {}
};


template <class Cam> struct CameraCameraT : CamCamera {
	using CLASSNAME = CameraCameraT<Cam>;
	RTTI_DECL1(CLASSNAME, CamCamera)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Cam::Camera_Visit(*dev, *this, vis);
		vis.VisitThis<CamCamera>(this);
	}
	typename Cam::NativeCamera* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Cam::Camera_Create(dev))
			return false;
		if (!Cam::Camera_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Cam::Camera_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Cam::Camera_Start(*dev, *this);
	}
	void Stop() override {
		Cam::Camera_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Cam::Camera_Uninitialize(*dev, *this);
		Cam::Camera_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Cam::Camera_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool IsReady(PacketIO& io) override {
		return Cam::Camera_IsReady(*dev, *this, io);
	}
};

#if (defined flagOPENCV && defined flagLINUX)
using V4L2OpenCVCamera = CameraCameraT<CamV4L2OpenCV>;
#endif

NAMESPACE_PARALLEL_END

#endif
