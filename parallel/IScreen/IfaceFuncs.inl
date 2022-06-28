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
static bool SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt);
static bool SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io);

	
static bool EventsBase_Initialize(NativeEventsBase& ev, AtomBase&, const Script::WorldState&);
static bool EventsBase_PostInitialize(NativeEventsBase& ev, AtomBase&);
static bool EventsBase_Start(NativeEventsBase& ev, AtomBase&);
static void EventsBase_Stop(NativeEventsBase& ev, AtomBase&);
static void EventsBase_Uninitialize(NativeEventsBase& ev, AtomBase&);
static bool EventsBase_Send(NativeEventsBase& ev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool EventsBase_Recv(NativeEventsBase& ev, AtomBase&, int, const Packet&);
static void EventsBase_Finalize(NativeEventsBase& ev, AtomBase&, RealtimeSourceConfig&);
static bool EventsBase_NegotiateSinkFormat(NativeEventsBase& ev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt);
static bool EventsBase_IsReady(NativeEventsBase& ev, AtomBase&, PacketIO& io);

	
static bool Context_Initialize(NativeContext& ctx, AtomBase&, const Script::WorldState&);
static bool Context_PostInitialize(NativeContext& ctx, AtomBase&);
static bool Context_Start(NativeContext& ctx, AtomBase&);
static void Context_Stop(NativeContext& ctx, AtomBase&);
static void Context_Uninitialize(NativeContext& ctx, AtomBase&);
static bool Context_Send(NativeContext& ctx, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool Context_Recv(NativeContext& ctx, AtomBase&, int, const Packet&);
static void Context_Finalize(NativeContext& ctx, AtomBase&, RealtimeSourceConfig&);
static bool Context_NegotiateSinkFormat(NativeContext& ctx, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt);
static bool Context_IsReady(NativeContext& ctx, AtomBase&, PacketIO& io);

	
