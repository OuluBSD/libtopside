// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

static bool MotionController_Initialize(NativeMotionController& ctrl, AtomBase&, const Script::WorldState&);
static bool MotionController_PostInitialize(NativeMotionController& ctrl);
static bool MotionController_Start(NativeMotionController& ctrl);
static void MotionController_Stop(NativeMotionController& ctrl);
static void MotionController_Uninitialize(NativeMotionController& ctrl);
static bool MotionController_ProcessPacket(NativeMotionController& ctrl, PacketValue& v);

static void MotionController_SendContinuousBuzzForDuration(NativeMotionController& o, float a1);
	
static bool MotionControllerSystem_Initialize(NativeMotionControllerSystem& sys, AtomBase&, const Script::WorldState&);
static bool MotionControllerSystem_PostInitialize(NativeMotionControllerSystem& sys);
static bool MotionControllerSystem_Start(NativeMotionControllerSystem& sys);
static void MotionControllerSystem_Stop(NativeMotionControllerSystem& sys);
static void MotionControllerSystem_Uninitialize(NativeMotionControllerSystem& sys);
static bool MotionControllerSystem_ProcessPacket(NativeMotionControllerSystem& sys, PacketValue& v);

	
static bool AppView_Initialize(AtomBase&, const Script::WorldState&);
static bool AppView_PostInitialize();
static bool AppView_Start();
static void AppView_Stop();
static void AppView_Uninitialize();
static bool AppView_ProcessPacket(PacketValue& v);

	
static bool CameraResources_Initialize(AtomBase&, const Script::WorldState&);
static bool CameraResources_PostInitialize();
static bool CameraResources_Start();
static void CameraResources_Stop();
static void CameraResources_Uninitialize();
static bool CameraResources_ProcessPacket(PacketValue& v);

	
static bool ControllerModelCache_Initialize(AtomBase&, const Script::WorldState&);
static bool ControllerModelCache_PostInitialize();
static bool ControllerModelCache_Start();
static void ControllerModelCache_Stop();
static void ControllerModelCache_Uninitialize();
static bool ControllerModelCache_ProcessPacket(PacketValue& v);

	
static bool DeviceResources_Initialize(AtomBase&, const Script::WorldState&);
static bool DeviceResources_PostInitialize();
static bool DeviceResources_Start();
static void DeviceResources_Stop();
static void DeviceResources_Uninitialize();
static bool DeviceResources_ProcessPacket(PacketValue& v);

	
static bool HolographicRenderer_Initialize(AtomBase&, const Script::WorldState&);
static bool HolographicRenderer_PostInitialize();
static bool HolographicRenderer_Start();
static void HolographicRenderer_Stop();
static void HolographicRenderer_Uninitialize();
static bool HolographicRenderer_ProcessPacket(PacketValue& v);

	
static bool HolographicScene_Initialize(AtomBase&, const Script::WorldState&);
static bool HolographicScene_PostInitialize();
static bool HolographicScene_Start();
static void HolographicScene_Stop();
static void HolographicScene_Uninitialize();
static bool HolographicScene_ProcessPacket(PacketValue& v);

	
static bool SpatialInteractionSystem_Initialize(AtomBase&, const Script::WorldState&);
static bool SpatialInteractionSystem_PostInitialize();
static bool SpatialInteractionSystem_Start();
static void SpatialInteractionSystem_Stop();
static void SpatialInteractionSystem_Uninitialize();
static bool SpatialInteractionSystem_ProcessPacket(PacketValue& v);

	
static bool Renderer_Initialize(AtomBase&, const Script::WorldState&);
static bool Renderer_PostInitialize();
static bool Renderer_Start();
static void Renderer_Stop();
static void Renderer_Uninitialize();
static bool Renderer_ProcessPacket(PacketValue& v);

	
