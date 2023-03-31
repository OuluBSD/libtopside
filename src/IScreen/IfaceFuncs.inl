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
static bool SinkDevice_NegotiateSinkFormat(NativeSinkDevice&, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt);
static bool SinkDevice_IsReady(NativeSinkDevice&, AtomBase&, PacketIO& io);

static bool Context_Create(NativeContext*& dev);
static void Context_Destroy(NativeContext*& dev);
static bool Context_Initialize(NativeContext&, AtomBase&, const Script::WorldState&);
static bool Context_PostInitialize(NativeContext&, AtomBase&);
static bool Context_Start(NativeContext&, AtomBase&);
static void Context_Stop(NativeContext&, AtomBase&);
static void Context_Uninitialize(NativeContext&, AtomBase&);
static bool Context_Send(NativeContext&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void Context_Visit(NativeContext&, AtomBase&, RuntimeVisitor& vis);
static bool Context_Recv(NativeContext&, AtomBase&, int, const Packet&);
static void Context_Finalize(NativeContext&, AtomBase&, RealtimeSourceConfig&);
static bool Context_NegotiateSinkFormat(NativeContext&, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt);
static bool Context_IsReady(NativeContext&, AtomBase&, PacketIO& io);

static bool EventsBase_Create(NativeEventsBase*& dev);
static void EventsBase_Destroy(NativeEventsBase*& dev);
static bool EventsBase_Initialize(NativeEventsBase&, AtomBase&, const Script::WorldState&);
static bool EventsBase_PostInitialize(NativeEventsBase&, AtomBase&);
static bool EventsBase_Start(NativeEventsBase&, AtomBase&);
static void EventsBase_Stop(NativeEventsBase&, AtomBase&);
static void EventsBase_Uninitialize(NativeEventsBase&, AtomBase&);
static bool EventsBase_Send(NativeEventsBase&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void EventsBase_Visit(NativeEventsBase&, AtomBase&, RuntimeVisitor& vis);
static bool EventsBase_Recv(NativeEventsBase&, AtomBase&, int, const Packet&);
static void EventsBase_Finalize(NativeEventsBase&, AtomBase&, RealtimeSourceConfig&);
static bool EventsBase_NegotiateSinkFormat(NativeEventsBase&, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt);
static bool EventsBase_IsReady(NativeEventsBase&, AtomBase&, PacketIO& io);

