// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool AudioSinkDevice_Create(One<NativeAudioSinkDevice>& dev);
static void AudioSinkDevice_Destroy(One<NativeAudioSinkDevice>& dev);
static bool AudioSinkDevice_Initialize(NativeAudioSinkDevice&, AtomBase&, const Script::WorldState&);
static bool AudioSinkDevice_PostInitialize(NativeAudioSinkDevice&, AtomBase&);
static bool AudioSinkDevice_Start(NativeAudioSinkDevice&, AtomBase&);
static void AudioSinkDevice_Stop(NativeAudioSinkDevice&, AtomBase&);
static void AudioSinkDevice_Uninitialize(NativeAudioSinkDevice&, AtomBase&);
static bool AudioSinkDevice_Send(NativeAudioSinkDevice&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void AudioSinkDevice_Visit(NativeAudioSinkDevice&, AtomBase&, RuntimeVisitor& vis);
static bool AudioSinkDevice_Recv(NativeAudioSinkDevice&, AtomBase&, int, const Packet&);
static void AudioSinkDevice_Finalize(NativeAudioSinkDevice&, AtomBase&, RealtimeSourceConfig&);
static void AudioSinkDevice_Update(NativeAudioSinkDevice&, AtomBase&, double dt);
static bool AudioSinkDevice_IsReady(NativeAudioSinkDevice&, AtomBase&, PacketIO& io);
static bool AudioSinkDevice_AttachContext(NativeAudioSinkDevice&, AtomBase& a, AtomBase& other);
static void AudioSinkDevice_DetachContext(NativeAudioSinkDevice&, AtomBase& a, AtomBase& other);

static bool CenterVideoSinkDevice_Create(One<NativeCenterVideoSinkDevice>& dev);
static void CenterVideoSinkDevice_Destroy(One<NativeCenterVideoSinkDevice>& dev);
static bool CenterVideoSinkDevice_Initialize(NativeCenterVideoSinkDevice&, AtomBase&, const Script::WorldState&);
static bool CenterVideoSinkDevice_PostInitialize(NativeCenterVideoSinkDevice&, AtomBase&);
static bool CenterVideoSinkDevice_Start(NativeCenterVideoSinkDevice&, AtomBase&);
static void CenterVideoSinkDevice_Stop(NativeCenterVideoSinkDevice&, AtomBase&);
static void CenterVideoSinkDevice_Uninitialize(NativeCenterVideoSinkDevice&, AtomBase&);
static bool CenterVideoSinkDevice_Send(NativeCenterVideoSinkDevice&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void CenterVideoSinkDevice_Visit(NativeCenterVideoSinkDevice&, AtomBase&, RuntimeVisitor& vis);
static bool CenterVideoSinkDevice_Recv(NativeCenterVideoSinkDevice&, AtomBase&, int, const Packet&);
static void CenterVideoSinkDevice_Finalize(NativeCenterVideoSinkDevice&, AtomBase&, RealtimeSourceConfig&);
static void CenterVideoSinkDevice_Update(NativeCenterVideoSinkDevice&, AtomBase&, double dt);
static bool CenterVideoSinkDevice_IsReady(NativeCenterVideoSinkDevice&, AtomBase&, PacketIO& io);
static bool CenterVideoSinkDevice_AttachContext(NativeCenterVideoSinkDevice&, AtomBase& a, AtomBase& other);
static void CenterVideoSinkDevice_DetachContext(NativeCenterVideoSinkDevice&, AtomBase& a, AtomBase& other);

static bool CenterFboSinkDevice_Create(One<NativeCenterFboSinkDevice>& dev);
static void CenterFboSinkDevice_Destroy(One<NativeCenterFboSinkDevice>& dev);
static bool CenterFboSinkDevice_Initialize(NativeCenterFboSinkDevice&, AtomBase&, const Script::WorldState&);
static bool CenterFboSinkDevice_PostInitialize(NativeCenterFboSinkDevice&, AtomBase&);
static bool CenterFboSinkDevice_Start(NativeCenterFboSinkDevice&, AtomBase&);
static void CenterFboSinkDevice_Stop(NativeCenterFboSinkDevice&, AtomBase&);
static void CenterFboSinkDevice_Uninitialize(NativeCenterFboSinkDevice&, AtomBase&);
static bool CenterFboSinkDevice_Send(NativeCenterFboSinkDevice&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void CenterFboSinkDevice_Visit(NativeCenterFboSinkDevice&, AtomBase&, RuntimeVisitor& vis);
static bool CenterFboSinkDevice_Recv(NativeCenterFboSinkDevice&, AtomBase&, int, const Packet&);
static void CenterFboSinkDevice_Finalize(NativeCenterFboSinkDevice&, AtomBase&, RealtimeSourceConfig&);
static void CenterFboSinkDevice_Update(NativeCenterFboSinkDevice&, AtomBase&, double dt);
static bool CenterFboSinkDevice_IsReady(NativeCenterFboSinkDevice&, AtomBase&, PacketIO& io);
static bool CenterFboSinkDevice_AttachContext(NativeCenterFboSinkDevice&, AtomBase& a, AtomBase& other);
static void CenterFboSinkDevice_DetachContext(NativeCenterFboSinkDevice&, AtomBase& a, AtomBase& other);

#if defined flagOGL
static bool OglVideoSinkDevice_Create(One<NativeOglVideoSinkDevice>& dev);
static void OglVideoSinkDevice_Destroy(One<NativeOglVideoSinkDevice>& dev);
static bool OglVideoSinkDevice_Initialize(NativeOglVideoSinkDevice&, AtomBase&, const Script::WorldState&);
static bool OglVideoSinkDevice_PostInitialize(NativeOglVideoSinkDevice&, AtomBase&);
static bool OglVideoSinkDevice_Start(NativeOglVideoSinkDevice&, AtomBase&);
static void OglVideoSinkDevice_Stop(NativeOglVideoSinkDevice&, AtomBase&);
static void OglVideoSinkDevice_Uninitialize(NativeOglVideoSinkDevice&, AtomBase&);
static bool OglVideoSinkDevice_Send(NativeOglVideoSinkDevice&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void OglVideoSinkDevice_Visit(NativeOglVideoSinkDevice&, AtomBase&, RuntimeVisitor& vis);
static bool OglVideoSinkDevice_Recv(NativeOglVideoSinkDevice&, AtomBase&, int, const Packet&);
static void OglVideoSinkDevice_Finalize(NativeOglVideoSinkDevice&, AtomBase&, RealtimeSourceConfig&);
static void OglVideoSinkDevice_Update(NativeOglVideoSinkDevice&, AtomBase&, double dt);
static bool OglVideoSinkDevice_IsReady(NativeOglVideoSinkDevice&, AtomBase&, PacketIO& io);
static bool OglVideoSinkDevice_AttachContext(NativeOglVideoSinkDevice&, AtomBase& a, AtomBase& other);
static void OglVideoSinkDevice_DetachContext(NativeOglVideoSinkDevice&, AtomBase& a, AtomBase& other);
#endif

static bool ContextBase_Create(One<NativeContextBase>& dev);
static void ContextBase_Destroy(One<NativeContextBase>& dev);
static bool ContextBase_Initialize(NativeContextBase&, AtomBase&, const Script::WorldState&);
static bool ContextBase_PostInitialize(NativeContextBase&, AtomBase&);
static bool ContextBase_Start(NativeContextBase&, AtomBase&);
static void ContextBase_Stop(NativeContextBase&, AtomBase&);
static void ContextBase_Uninitialize(NativeContextBase&, AtomBase&);
static bool ContextBase_Send(NativeContextBase&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void ContextBase_Visit(NativeContextBase&, AtomBase&, RuntimeVisitor& vis);
static bool ContextBase_Recv(NativeContextBase&, AtomBase&, int, const Packet&);
static void ContextBase_Finalize(NativeContextBase&, AtomBase&, RealtimeSourceConfig&);
static void ContextBase_Update(NativeContextBase&, AtomBase&, double dt);
static bool ContextBase_IsReady(NativeContextBase&, AtomBase&, PacketIO& io);
static bool ContextBase_AttachContext(NativeContextBase&, AtomBase& a, AtomBase& other);
static void ContextBase_DetachContext(NativeContextBase&, AtomBase& a, AtomBase& other);

static bool EventsBase_Create(One<NativeEventsBase>& dev);
static void EventsBase_Destroy(One<NativeEventsBase>& dev);
static bool EventsBase_Initialize(NativeEventsBase&, AtomBase&, const Script::WorldState&);
static bool EventsBase_PostInitialize(NativeEventsBase&, AtomBase&);
static bool EventsBase_Start(NativeEventsBase&, AtomBase&);
static void EventsBase_Stop(NativeEventsBase&, AtomBase&);
static void EventsBase_Uninitialize(NativeEventsBase&, AtomBase&);
static bool EventsBase_Send(NativeEventsBase&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static void EventsBase_Visit(NativeEventsBase&, AtomBase&, RuntimeVisitor& vis);
static bool EventsBase_Recv(NativeEventsBase&, AtomBase&, int, const Packet&);
static void EventsBase_Finalize(NativeEventsBase&, AtomBase&, RealtimeSourceConfig&);
static void EventsBase_Update(NativeEventsBase&, AtomBase&, double dt);
static bool EventsBase_IsReady(NativeEventsBase&, AtomBase&, PacketIO& io);
static bool EventsBase_AttachContext(NativeEventsBase&, AtomBase& a, AtomBase& other);
static void EventsBase_DetachContext(NativeEventsBase&, AtomBase& a, AtomBase& other);

