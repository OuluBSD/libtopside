// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool Camera_Create(NativeCamera*& dev);
static void Camera_Destroy(NativeCamera*& dev);
static bool Camera_Initialize(NativeCamera&, AtomBase&, const Script::WorldState&);
static bool Camera_PostInitialize(NativeCamera&, AtomBase&);
static bool Camera_Start(NativeCamera&, AtomBase&);
static void Camera_Stop(NativeCamera&, AtomBase&);
static void Camera_Uninitialize(NativeCamera&, AtomBase&);
static bool Camera_Send(NativeCamera&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void Camera_Visit(NativeCamera&, AtomBase&, RuntimeVisitor& vis);
static bool Camera_IsReady(NativeCamera&, AtomBase&, PacketIO& io);

