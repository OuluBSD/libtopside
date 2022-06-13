// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase&, const Script::WorldState&);
static bool SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase&);
static bool SinkDevice_Start(NativeSinkDevice& dev, AtomBase&);
static void SinkDevice_Stop(NativeSinkDevice& dev, AtomBase&);
static void SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase&);
static bool SinkDevice_Send(NativeSinkDevice& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool SinkDevice_Recv(NativeSinkDevice& dev, AtomBase&, int, const Packet&);
static void SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase&, RealtimeSourceConfig&);
static bool SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io);

	
