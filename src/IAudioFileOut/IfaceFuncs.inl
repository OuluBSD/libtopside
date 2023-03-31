// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool Sink_Create(NativeSink*& dev);
static void Sink_Destroy(NativeSink*& dev);
static bool Sink_Initialize(NativeSink&, AtomBase&, const Script::WorldState&);
static bool Sink_PostInitialize(NativeSink&, AtomBase&);
static bool Sink_Start(NativeSink&, AtomBase&);
static void Sink_Stop(NativeSink&, AtomBase&);
static void Sink_Uninitialize(NativeSink&, AtomBase&);
static bool Sink_Send(NativeSink&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void Sink_Visit(NativeSink&, AtomBase&, RuntimeVisitor& vis);
static bool Sink_Recv(NativeSink&, AtomBase&, int, const Packet&);
static void Sink_Finalize(NativeSink&, AtomBase&, RealtimeSourceConfig&);
static bool Sink_IsReady(NativeSink&, AtomBase&, PacketIO& io);

