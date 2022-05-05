// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool MotionController_Initialize(NativeMotionController& ctrl, AtomBase&, const Script::WorldState&);
static bool MotionController_PostInitialize(NativeMotionController& ctrl, AtomBase&);
static bool MotionController_Start(NativeMotionController& ctrl, AtomBase&);
static void MotionController_Stop(NativeMotionController& ctrl, AtomBase&);
static void MotionController_Uninitialize(NativeMotionController& ctrl, AtomBase&);
static bool MotionController_Send(NativeMotionController& ctrl, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

static void MotionController_SendContinuousBuzzForDuration(NativeMotionController& o, float a1);
	
static bool MotionControllerSystem_Initialize(NativeMotionControllerSystem& sys, AtomBase&, const Script::WorldState&);
static bool MotionControllerSystem_PostInitialize(NativeMotionControllerSystem& sys, AtomBase&);
static bool MotionControllerSystem_Start(NativeMotionControllerSystem& sys, AtomBase&);
static void MotionControllerSystem_Stop(NativeMotionControllerSystem& sys, AtomBase&);
static void MotionControllerSystem_Uninitialize(NativeMotionControllerSystem& sys, AtomBase&);
static bool MotionControllerSystem_Send(NativeMotionControllerSystem& sys, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool AppView_Initialize(AtomBase&, const Script::WorldState&);
static bool AppView_PostInitialize(AtomBase&);
static bool AppView_Start(AtomBase&);
static void AppView_Stop(AtomBase&);
static void AppView_Uninitialize(AtomBase&);
static bool AppView_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool CameraResources_Initialize(AtomBase&, const Script::WorldState&);
static bool CameraResources_PostInitialize(AtomBase&);
static bool CameraResources_Start(AtomBase&);
static void CameraResources_Stop(AtomBase&);
static void CameraResources_Uninitialize(AtomBase&);
static bool CameraResources_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool ControllerModelCache_Initialize(AtomBase&, const Script::WorldState&);
static bool ControllerModelCache_PostInitialize(AtomBase&);
static bool ControllerModelCache_Start(AtomBase&);
static void ControllerModelCache_Stop(AtomBase&);
static void ControllerModelCache_Uninitialize(AtomBase&);
static bool ControllerModelCache_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool DeviceResources_Initialize(AtomBase&, const Script::WorldState&);
static bool DeviceResources_PostInitialize(AtomBase&);
static bool DeviceResources_Start(AtomBase&);
static void DeviceResources_Stop(AtomBase&);
static void DeviceResources_Uninitialize(AtomBase&);
static bool DeviceResources_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool HolographicRenderer_Initialize(AtomBase&, const Script::WorldState&);
static bool HolographicRenderer_PostInitialize(AtomBase&);
static bool HolographicRenderer_Start(AtomBase&);
static void HolographicRenderer_Stop(AtomBase&);
static void HolographicRenderer_Uninitialize(AtomBase&);
static bool HolographicRenderer_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool HolographicScene_Initialize(AtomBase&, const Script::WorldState&);
static bool HolographicScene_PostInitialize(AtomBase&);
static bool HolographicScene_Start(AtomBase&);
static void HolographicScene_Stop(AtomBase&);
static void HolographicScene_Uninitialize(AtomBase&);
static bool HolographicScene_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool SpatialInteractionSystem_Initialize(AtomBase&, const Script::WorldState&);
static bool SpatialInteractionSystem_PostInitialize(AtomBase&);
static bool SpatialInteractionSystem_Start(AtomBase&);
static void SpatialInteractionSystem_Stop(AtomBase&);
static void SpatialInteractionSystem_Uninitialize(AtomBase&);
static bool SpatialInteractionSystem_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool Renderer_Initialize(AtomBase&, const Script::WorldState&);
static bool Renderer_PostInitialize(AtomBase&);
static bool Renderer_Start(AtomBase&);
static void Renderer_Stop(AtomBase&);
static void Renderer_Uninitialize(AtomBase&);
static bool Renderer_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
