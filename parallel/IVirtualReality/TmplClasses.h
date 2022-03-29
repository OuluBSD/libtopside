// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

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
	typename Vr::NativeMotionController ctrl;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Vr::MotionController_Initialize(ctrl, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Vr::MotionController_Uninitialize(ctrl);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Vr::MotionController_ProcessPacket(ctrl, v))
			return false;
		return true;
	}

	void SendContinuousBuzzForDuration(float a1) {
		Vr::MotionController_SendContinuousBuzzForDuration(this->ctrl, a1);
	}
	
	
};

template <class Vr>
struct VirtualRealityMotionControllerSystemT : VrMotionControllerSystem {
	typename Vr::NativeMotionControllerSystem sys;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Vr::MotionControllerSystem_Initialize(sys, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Vr::MotionControllerSystem_Uninitialize(sys);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Vr::MotionControllerSystem_ProcessPacket(sys, v))
			return false;
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityAppViewT : VrAppView {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityCameraResourcesT : VrCameraResources {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityControllerModelCacheT : VrControllerModelCache {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityDeviceResourcesT : VrDeviceResources {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityHolographicRendererT : VrHolographicRenderer {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityHolographicSceneT : VrHolographicScene {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealitySpatialInteractionSystemT : VrSpatialInteractionSystem {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vr>
struct VirtualRealityRendererT : VrRenderer {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

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


NAMESPACE_PARALLEL_END



#endif

