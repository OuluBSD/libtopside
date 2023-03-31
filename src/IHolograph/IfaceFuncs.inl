// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool SinkDevice_Create(NativeSinkDevice*& dev);
static void SinkDevice_Destroy(NativeSinkDevice*& dev);
static bool SinkDevice_Initialize(NativeSinkDevice&, AtomBase&, const Script::WorldState&);
static bool SinkDevice_PostInitialize(NativeSinkDevice&, AtomBase&);
static bool SinkDevice_Start(NativeSinkDevice&, AtomBase&);
static void SinkDevice_Stop(NativeSinkDevice&, AtomBase&);
static void SinkDevice_Uninitialize(NativeSinkDevice&, AtomBase&);
static bool SinkDevice_Send(NativeSinkDevice&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void SinkDevice_Visit(NativeSinkDevice&, AtomBase&, RuntimeVisitor& vis);
static bool SinkDevice_Recv(NativeSinkDevice&, AtomBase&, int, const Packet&);
static void SinkDevice_Finalize(NativeSinkDevice&, AtomBase&, RealtimeSourceConfig&);
static bool SinkDevice_IsReady(NativeSinkDevice&, AtomBase&, PacketIO& io);

