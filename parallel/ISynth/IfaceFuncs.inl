// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool Instrument_Initialize(NativeInstrument& dev, AtomBase&, const Script::WorldState&);
static bool Instrument_PostInitialize(NativeInstrument& dev, AtomBase&);
static bool Instrument_Start(NativeInstrument& dev, AtomBase&);
static void Instrument_Stop(NativeInstrument& dev, AtomBase&);
static void Instrument_Uninitialize(NativeInstrument& dev, AtomBase&);
static bool Instrument_Send(NativeInstrument& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool Instrument_Recv(NativeInstrument& dev, AtomBase&, int, const Packet&);
static void Instrument_Finalize(NativeInstrument& dev, AtomBase&, RealtimeSourceConfig&);
static bool Instrument_IsReady(NativeInstrument& dev, AtomBase&, PacketIO& io);

	
