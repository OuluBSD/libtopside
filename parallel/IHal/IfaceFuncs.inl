// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool AudioSinkDevice_Initialize(NativeAudioSinkDevice& dev, AtomBase&, const Script::WorldState&);
static bool AudioSinkDevice_PostInitialize(NativeAudioSinkDevice& dev, AtomBase&);
static bool AudioSinkDevice_Start(NativeAudioSinkDevice& dev, AtomBase&);
static void AudioSinkDevice_Stop(NativeAudioSinkDevice& dev, AtomBase&);
static void AudioSinkDevice_Uninitialize(NativeAudioSinkDevice& dev, AtomBase&);
static bool AudioSinkDevice_Send(NativeAudioSinkDevice& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool AudioSinkDevice_Recv(NativeAudioSinkDevice& dev, AtomBase&, int, const Packet&);
static void AudioSinkDevice_Finalize(NativeAudioSinkDevice& dev, AtomBase&, RealtimeSourceConfig&);
static void AudioSinkDevice_Update(NativeAudioSinkDevice& dev, AtomBase&, double dt);
static bool AudioSinkDevice_IsReady(NativeAudioSinkDevice& dev, AtomBase&, PacketIO& io);

	
static bool CenterVideoSinkDevice_Initialize(NativeVideoSink& dev, AtomBase&, const Script::WorldState&);
static bool CenterVideoSinkDevice_PostInitialize(NativeVideoSink& dev, AtomBase&);
static bool CenterVideoSinkDevice_Start(NativeVideoSink& dev, AtomBase&);
static void CenterVideoSinkDevice_Stop(NativeVideoSink& dev, AtomBase&);
static void CenterVideoSinkDevice_Uninitialize(NativeVideoSink& dev, AtomBase&);
static bool CenterVideoSinkDevice_Send(NativeVideoSink& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool CenterVideoSinkDevice_Recv(NativeVideoSink& dev, AtomBase&, int, const Packet&);
static void CenterVideoSinkDevice_Finalize(NativeVideoSink& dev, AtomBase&, RealtimeSourceConfig&);
static void CenterVideoSinkDevice_Update(NativeVideoSink& dev, AtomBase&, double dt);
static bool CenterVideoSinkDevice_IsReady(NativeVideoSink& dev, AtomBase&, PacketIO& io);

	
static bool CenterFboSinkDevice_Initialize(NativeSw3dVideoSink& dev, AtomBase&, const Script::WorldState&);
static bool CenterFboSinkDevice_PostInitialize(NativeSw3dVideoSink& dev, AtomBase&);
static bool CenterFboSinkDevice_Start(NativeSw3dVideoSink& dev, AtomBase&);
static void CenterFboSinkDevice_Stop(NativeSw3dVideoSink& dev, AtomBase&);
static void CenterFboSinkDevice_Uninitialize(NativeSw3dVideoSink& dev, AtomBase&);
static bool CenterFboSinkDevice_Send(NativeSw3dVideoSink& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool CenterFboSinkDevice_Recv(NativeSw3dVideoSink& dev, AtomBase&, int, const Packet&);
static void CenterFboSinkDevice_Finalize(NativeSw3dVideoSink& dev, AtomBase&, RealtimeSourceConfig&);
static void CenterFboSinkDevice_Update(NativeSw3dVideoSink& dev, AtomBase&, double dt);
static bool CenterFboSinkDevice_IsReady(NativeSw3dVideoSink& dev, AtomBase&, PacketIO& io);

	
#if defined flagOGL
static bool OglVideoSinkDevice_Initialize(NativeOglVideoSink& dev, AtomBase&, const Script::WorldState&);
static bool OglVideoSinkDevice_PostInitialize(NativeOglVideoSink& dev, AtomBase&);
static bool OglVideoSinkDevice_Start(NativeOglVideoSink& dev, AtomBase&);
static void OglVideoSinkDevice_Stop(NativeOglVideoSink& dev, AtomBase&);
static void OglVideoSinkDevice_Uninitialize(NativeOglVideoSink& dev, AtomBase&);
static bool OglVideoSinkDevice_Send(NativeOglVideoSink& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool OglVideoSinkDevice_Recv(NativeOglVideoSink& dev, AtomBase&, int, const Packet&);
static void OglVideoSinkDevice_Finalize(NativeOglVideoSink& dev, AtomBase&, RealtimeSourceConfig&);
static void OglVideoSinkDevice_Update(NativeOglVideoSink& dev, AtomBase&, double dt);
static bool OglVideoSinkDevice_IsReady(NativeOglVideoSink& dev, AtomBase&, PacketIO& io);

#endif
	
static bool ContextBase_Initialize(NativeContextBase& ctx, AtomBase&, const Script::WorldState&);
static bool ContextBase_PostInitialize(NativeContextBase& ctx, AtomBase&);
static bool ContextBase_Start(NativeContextBase& ctx, AtomBase&);
static void ContextBase_Stop(NativeContextBase& ctx, AtomBase&);
static void ContextBase_Uninitialize(NativeContextBase& ctx, AtomBase&);
static bool ContextBase_Send(NativeContextBase& ctx, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool ContextBase_AttachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other);
static void ContextBase_DetachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other);
static bool ContextBase_Recv(NativeContextBase& ctx, AtomBase&, int, const Packet&);
static void ContextBase_Finalize(NativeContextBase& ctx, AtomBase&, RealtimeSourceConfig&);
static void ContextBase_Update(NativeContextBase& ctx, AtomBase&, double dt);
static bool ContextBase_IsReady(NativeContextBase& ctx, AtomBase&, PacketIO& io);

	
static bool EventsBase_Initialize(NativeEventsBase& ctx, AtomBase&, const Script::WorldState&);
static bool EventsBase_PostInitialize(NativeEventsBase& ctx, AtomBase&);
static bool EventsBase_Start(NativeEventsBase& ctx, AtomBase&);
static void EventsBase_Stop(NativeEventsBase& ctx, AtomBase&);
static void EventsBase_Uninitialize(NativeEventsBase& ctx, AtomBase&);
static bool EventsBase_Send(NativeEventsBase& ctx, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
static bool EventsBase_Recv(NativeEventsBase& ctx, AtomBase&, int, const Packet&);
static void EventsBase_Finalize(NativeEventsBase& ctx, AtomBase&, RealtimeSourceConfig&);
static void EventsBase_Update(NativeEventsBase& ctx, AtomBase&, double dt);
static bool EventsBase_IsReady(NativeEventsBase& ctx, AtomBase&, PacketIO& io);

	
