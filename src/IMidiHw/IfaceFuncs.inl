// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool Source_Create(NativeSource*& dev);
static void Source_Destroy(NativeSource*& dev);
static bool Source_Initialize(NativeSource&, AtomBase&, const Script::WorldState&);
static bool Source_PostInitialize(NativeSource&, AtomBase&);
static bool Source_Start(NativeSource&, AtomBase&);
static void Source_Stop(NativeSource&, AtomBase&);
static void Source_Uninitialize(NativeSource&, AtomBase&);
static bool Source_Send(NativeSource&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void Source_Visit(NativeSource&, AtomBase&, RuntimeVisitor& vis);
static bool Source_IsReady(NativeSource&, AtomBase&, PacketIO& io);

