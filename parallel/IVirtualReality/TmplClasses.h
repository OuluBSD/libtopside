// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 0:00:44

#ifndef _IVirtualReality_TmplClasses_h_
#define _IVirtualReality_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Vr> struct VirtualRealityMotionControllerT;
template <class Vr> struct VirtualRealityMotionControllerSystemT;
template <class Vr> struct VirtualRealityAppViewT;
template <class Vr> struct VirtualRealityCameraResourcesT;
template <class Vr> struct VirtualRealityControllerModelCacheT;
template <class Vr> struct VirtualRealityDeviceResourcesT;
template <class Vr> struct VirtualRealityHolographicRendererT;
template <class Vr> struct VirtualRealityHolographicSceneT;
template <class Vr> struct VirtualRealitySpatialInteractionSystemT;
template <class Vr> struct VirtualRealityRendererT;


template <class Vr>
struct VirtualRealityMotionControllerT : VrMotionController {
	using CLASSNAME = VirtualRealityMotionControllerT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Vr::MotionController_ProcessPacket(ctrl, *this, in, out))
			return false;
		return true;
	}

	void SendContinuousBuzzForDuration(float a1) {
		Vr::MotionController_SendContinuousBuzzForDuration(this->ctrl, a1);
	}
	
	
};

template <class Vr>
struct VirtualRealityMotionControllerSystemT : VrMotionControllerSystem {
	using CLASSNAME = VirtualRealityMotionControllerSystemT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Vr::MotionControllerSystem_ProcessPacket(sys, *this, in, out))
			return false;
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityAppViewT : VrAppView {
	using CLASSNAME = VirtualRealityAppViewT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityCameraResourcesT : VrCameraResources {
	using CLASSNAME = VirtualRealityCameraResourcesT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityControllerModelCacheT : VrControllerModelCache {
	using CLASSNAME = VirtualRealityControllerModelCacheT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityDeviceResourcesT : VrDeviceResources {
	using CLASSNAME = VirtualRealityDeviceResourcesT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityHolographicRendererT : VrHolographicRenderer {
	using CLASSNAME = VirtualRealityHolographicRendererT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityHolographicSceneT : VrHolographicScene {
	using CLASSNAME = VirtualRealityHolographicSceneT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealitySpatialInteractionSystemT : VrSpatialInteractionSystem {
	using CLASSNAME = VirtualRealitySpatialInteractionSystemT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityRendererT : VrRenderer {
	using CLASSNAME = VirtualRealityRendererT<Vr>;
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

#if 0
using HoloMotionController = VirtualRealityMotionControllerT<VrHolo>;
using HoloMotionControllerSystem = VirtualRealityMotionControllerSystemT<VrHolo>;
using HoloAppView = VirtualRealityAppViewT<VrHolo>;
using HoloCameraResources = VirtualRealityCameraResourcesT<VrHolo>;
using HoloControllerModelCache = VirtualRealityControllerModelCacheT<VrHolo>;
using HoloDeviceResources = VirtualRealityDeviceResourcesT<VrHolo>;
using HoloHolographicRenderer = VirtualRealityHolographicRendererT<VrHolo>;
using HoloHolographicScene = VirtualRealityHolographicSceneT<VrHolo>;
using HoloSpatialInteractionSystem = VirtualRealitySpatialInteractionSystemT<VrHolo>;
using HoloRenderer = VirtualRealityRendererT<VrHolo>;
#endif

#if 0
using OvrMotionController = VirtualRealityMotionControllerT<VrOvr>;
using OvrMotionControllerSystem = VirtualRealityMotionControllerSystemT<VrOvr>;
using OvrAppView = VirtualRealityAppViewT<VrOvr>;
using OvrCameraResources = VirtualRealityCameraResourcesT<VrOvr>;
using OvrControllerModelCache = VirtualRealityControllerModelCacheT<VrOvr>;
using OvrDeviceResources = VirtualRealityDeviceResourcesT<VrOvr>;
using OvrHolographicRenderer = VirtualRealityHolographicRendererT<VrOvr>;
using OvrHolographicScene = VirtualRealityHolographicSceneT<VrOvr>;
using OvrSpatialInteractionSystem = VirtualRealitySpatialInteractionSystemT<VrOvr>;
using OvrRenderer = VirtualRealityRendererT<VrOvr>;
#endif

#if 0
using HmdMotionController = VirtualRealityMotionControllerT<VrHmd>;
using HmdMotionControllerSystem = VirtualRealityMotionControllerSystemT<VrHmd>;
using HmdAppView = VirtualRealityAppViewT<VrHmd>;
using HmdCameraResources = VirtualRealityCameraResourcesT<VrHmd>;
using HmdControllerModelCache = VirtualRealityControllerModelCacheT<VrHmd>;
using HmdDeviceResources = VirtualRealityDeviceResourcesT<VrHmd>;
using HmdHolographicRenderer = VirtualRealityHolographicRendererT<VrHmd>;
using HmdHolographicScene = VirtualRealityHolographicSceneT<VrHmd>;
using HmdSpatialInteractionSystem = VirtualRealitySpatialInteractionSystemT<VrHmd>;
using HmdRenderer = VirtualRealityRendererT<VrHmd>;
#endif


NAMESPACE_PARALLEL_END



#endif

