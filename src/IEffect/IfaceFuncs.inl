// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool Effect_Create(NativeEffect*& dev);
static void Effect_Destroy(NativeEffect*& dev);
static bool Effect_Initialize(NativeEffect&, AtomBase&, const Script::WorldState&);
static bool Effect_PostInitialize(NativeEffect&, AtomBase&);
static bool Effect_Start(NativeEffect&, AtomBase&);
static void Effect_Stop(NativeEffect&, AtomBase&);
static void Effect_Uninitialize(NativeEffect&, AtomBase&);
static bool Effect_Send(NativeEffect&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void Effect_Visit(NativeEffect&, AtomBase&, RuntimeVisitor& vis);
static bool Effect_Recv(NativeEffect&, AtomBase&, int, const Packet&);
static void Effect_Finalize(NativeEffect&, AtomBase&, RealtimeSourceConfig&);
static bool Effect_IsReady(NativeEffect&, AtomBase&, PacketIO& io);

