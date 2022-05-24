// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IVR_TmplClasses_h_
#define _IVR_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Vr> struct VRMotionControllerT;
template <class Vr> struct VRMotionControllerSystemT;
template <class Vr> struct VRAppViewT;
template <class Vr> struct VRCameraResourcesT;
template <class Vr> struct VRControllerModelCacheT;
template <class Vr> struct VRDeviceResourcesT;
template <class Vr> struct VRHolographicRendererT;
template <class Vr> struct VRHolographicSceneT;
template <class Vr> struct VRSpatialInteractionSystemT;
template <class Vr> struct VRRendererT;



template <class Vr>
struct VRMotionControllerT : VrMotionController {
	using CLASSNAME = VRMotionControllerT<Vr>;
	RTTI_DECL1(CLASSNAME, VrMotionController)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrMotionController>(this);}
	
	typename Vr::NativeMotionController ctrl;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Vr::MotionController_Initialize(ctrl, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Vr::MotionController_PostInitialize(ctrl, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Vr::MotionController_Start(ctrl, *this);
	}

	void Stop() override {
		Vr::MotionController_Stop(ctrl, *this);
	}

	void Uninitialize() override {
		Vr::MotionController_Uninitialize(ctrl, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Vr::MotionController_Send(ctrl, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	void SendContinuousBuzzForDuration(float a1) {
		Vr::MotionController_SendContinuousBuzzForDuration(this->ctrl, a1);
	}
	
	
};


template <class Vr>
struct VRMotionControllerSystemT : VrMotionControllerSystem {
	using CLASSNAME = VRMotionControllerSystemT<Vr>;
	RTTI_DECL1(CLASSNAME, VrMotionControllerSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrMotionControllerSystem>(this);}
	
	typename Vr::NativeMotionControllerSystem sys;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Vr::MotionControllerSystem_Initialize(sys, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Vr::MotionControllerSystem_PostInitialize(sys, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Vr::MotionControllerSystem_Start(sys, *this);
	}

	void Stop() override {
		Vr::MotionControllerSystem_Stop(sys, *this);
	}

	void Uninitialize() override {
		Vr::MotionControllerSystem_Uninitialize(sys, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Vr::MotionControllerSystem_Send(sys, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	
};


template <class Vr>
struct VRAppViewT : VrAppView {
	using CLASSNAME = VRAppViewT<Vr>;
	RTTI_DECL1(CLASSNAME, VrAppView)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrAppView>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


template <class Vr>
struct VRCameraResourcesT : VrCameraResources {
	using CLASSNAME = VRCameraResourcesT<Vr>;
	RTTI_DECL1(CLASSNAME, VrCameraResources)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrCameraResources>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


template <class Vr>
struct VRControllerModelCacheT : VrControllerModelCache {
	using CLASSNAME = VRControllerModelCacheT<Vr>;
	RTTI_DECL1(CLASSNAME, VrControllerModelCache)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrControllerModelCache>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


template <class Vr>
struct VRDeviceResourcesT : VrDeviceResources {
	using CLASSNAME = VRDeviceResourcesT<Vr>;
	RTTI_DECL1(CLASSNAME, VrDeviceResources)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrDeviceResources>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


template <class Vr>
struct VRHolographicRendererT : VrHolographicRenderer {
	using CLASSNAME = VRHolographicRendererT<Vr>;
	RTTI_DECL1(CLASSNAME, VrHolographicRenderer)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrHolographicRenderer>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


template <class Vr>
struct VRHolographicSceneT : VrHolographicScene {
	using CLASSNAME = VRHolographicSceneT<Vr>;
	RTTI_DECL1(CLASSNAME, VrHolographicScene)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrHolographicScene>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


template <class Vr>
struct VRSpatialInteractionSystemT : VrSpatialInteractionSystem {
	using CLASSNAME = VRSpatialInteractionSystemT<Vr>;
	RTTI_DECL1(CLASSNAME, VrSpatialInteractionSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrSpatialInteractionSystem>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


template <class Vr>
struct VRRendererT : VrRenderer {
	using CLASSNAME = VRRendererT<Vr>;
	RTTI_DECL1(CLASSNAME, VrRenderer)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VrRenderer>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};

#if defined flagOGL
using FakeMotionController = VRMotionControllerT<VrFake>;
using FakeMotionControllerSystem = VRMotionControllerSystemT<VrFake>;
using FakeAppView = VRAppViewT<VrFake>;
using FakeCameraResources = VRCameraResourcesT<VrFake>;
using FakeControllerModelCache = VRControllerModelCacheT<VrFake>;
using FakeDeviceResources = VRDeviceResourcesT<VrFake>;
using FakeHolographicRenderer = VRHolographicRendererT<VrFake>;
using FakeHolographicScene = VRHolographicSceneT<VrFake>;
using FakeSpatialInteractionSystem = VRSpatialInteractionSystemT<VrFake>;
using FakeRenderer = VRRendererT<VrFake>;
#endif

#if 0
using HoloMotionController = VRMotionControllerT<VrHolo>;
using HoloMotionControllerSystem = VRMotionControllerSystemT<VrHolo>;
using HoloAppView = VRAppViewT<VrHolo>;
using HoloCameraResources = VRCameraResourcesT<VrHolo>;
using HoloControllerModelCache = VRControllerModelCacheT<VrHolo>;
using HoloDeviceResources = VRDeviceResourcesT<VrHolo>;
using HoloHolographicRenderer = VRHolographicRendererT<VrHolo>;
using HoloHolographicScene = VRHolographicSceneT<VrHolo>;
using HoloSpatialInteractionSystem = VRSpatialInteractionSystemT<VrHolo>;
using HoloRenderer = VRRendererT<VrHolo>;
#endif

#if 0
using OvrMotionController = VRMotionControllerT<VrOvr>;
using OvrMotionControllerSystem = VRMotionControllerSystemT<VrOvr>;
using OvrAppView = VRAppViewT<VrOvr>;
using OvrCameraResources = VRCameraResourcesT<VrOvr>;
using OvrControllerModelCache = VRControllerModelCacheT<VrOvr>;
using OvrDeviceResources = VRDeviceResourcesT<VrOvr>;
using OvrHolographicRenderer = VRHolographicRendererT<VrOvr>;
using OvrHolographicScene = VRHolographicSceneT<VrOvr>;
using OvrSpatialInteractionSystem = VRSpatialInteractionSystemT<VrOvr>;
using OvrRenderer = VRRendererT<VrOvr>;
#endif

#if 0
using HmdMotionController = VRMotionControllerT<VrHmd>;
using HmdMotionControllerSystem = VRMotionControllerSystemT<VrHmd>;
using HmdAppView = VRAppViewT<VrHmd>;
using HmdCameraResources = VRCameraResourcesT<VrHmd>;
using HmdControllerModelCache = VRControllerModelCacheT<VrHmd>;
using HmdDeviceResources = VRDeviceResourcesT<VrHmd>;
using HmdHolographicRenderer = VRHolographicRendererT<VrHmd>;
using HmdHolographicScene = VRHolographicSceneT<VrHmd>;
using HmdSpatialInteractionSystem = VRSpatialInteractionSystemT<VrHmd>;
using HmdRenderer = VRRendererT<VrHmd>;
#endif


NAMESPACE_PARALLEL_END

#endif

