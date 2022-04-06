// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 12:22:22

static bool AudioSinkDevice_Initialize(NativeAudioSinkDevice& dev, AtomBase&, const Script::WorldState&);
static bool AudioSinkDevice_PostInitialize(NativeAudioSinkDevice& dev, AtomBase&);
static bool AudioSinkDevice_Start(NativeAudioSinkDevice& dev, AtomBase&);
static void AudioSinkDevice_Stop(NativeAudioSinkDevice& dev, AtomBase&);
static void AudioSinkDevice_Uninitialize(NativeAudioSinkDevice& dev, AtomBase&);
static bool AudioSinkDevice_ProcessPacket(NativeAudioSinkDevice& dev, AtomBase&, PacketValue& in, PacketValue& out);

	
static bool CenterVideoSinkDevice_Initialize(NativeVideoSink& dev, AtomBase&, const Script::WorldState&);
static bool CenterVideoSinkDevice_PostInitialize(NativeVideoSink& dev, AtomBase&);
static bool CenterVideoSinkDevice_Start(NativeVideoSink& dev, AtomBase&);
static void CenterVideoSinkDevice_Stop(NativeVideoSink& dev, AtomBase&);
static void CenterVideoSinkDevice_Uninitialize(NativeVideoSink& dev, AtomBase&);
static bool CenterVideoSinkDevice_ProcessPacket(NativeVideoSink& dev, AtomBase&, PacketValue& in, PacketValue& out);

	
static bool ContextBase_Initialize(NativeContextBase& ctx, AtomBase&, const Script::WorldState&);
static bool ContextBase_PostInitialize(NativeContextBase& ctx, AtomBase&);
static bool ContextBase_Start(NativeContextBase& ctx, AtomBase&);
static void ContextBase_Stop(NativeContextBase& ctx, AtomBase&);
static void ContextBase_Uninitialize(NativeContextBase& ctx, AtomBase&);
static bool ContextBase_ProcessPacket(NativeContextBase& ctx, AtomBase&, PacketValue& in, PacketValue& out);
static bool ContextBase_AttachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other);
static void ContextBase_DetachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other);

	
