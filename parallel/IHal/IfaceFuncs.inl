// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 22:44:00

static bool AudioSinkDevice_Initialize(NativeAudioSinkDevice& dev, AtomBase&, const Script::WorldState&);
static bool AudioSinkDevice_PostInitialize(NativeAudioSinkDevice& dev, AtomBase&);
static bool AudioSinkDevice_Start(NativeAudioSinkDevice& dev, AtomBase&);
static void AudioSinkDevice_Stop(NativeAudioSinkDevice& dev, AtomBase&);
static void AudioSinkDevice_Uninitialize(NativeAudioSinkDevice& dev, AtomBase&);
static bool AudioSinkDevice_ProcessPacket(NativeAudioSinkDevice& dev, AtomBase&, PacketValue& in, PacketValue& out);

	
static bool Window_Initialize(NativeWindow& win, AtomBase&, const Script::WorldState&);
static bool Window_PostInitialize(NativeWindow& win, AtomBase&);
static bool Window_Start(NativeWindow& win, AtomBase&);
static void Window_Stop(NativeWindow& win, AtomBase&);
static void Window_Uninitialize(NativeWindow& win, AtomBase&);
static bool Window_ProcessPacket(NativeWindow& win, AtomBase&, PacketValue& in, PacketValue& out);

	
static bool Renderer_Initialize(NativeRenderer& rend, AtomBase&, const Script::WorldState&);
static bool Renderer_PostInitialize(NativeRenderer& rend, AtomBase&);
static bool Renderer_Start(NativeRenderer& rend, AtomBase&);
static void Renderer_Stop(NativeRenderer& rend, AtomBase&);
static void Renderer_Uninitialize(NativeRenderer& rend, AtomBase&);
static bool Renderer_ProcessPacket(NativeRenderer& rend, AtomBase&, PacketValue& in, PacketValue& out);


static bool CenterVideoSinkDevice_Initialize(AtomBase&, const Script::WorldState&);
static bool CenterVideoSinkDevice_PostInitialize(AtomBase&);
static bool CenterVideoSinkDevice_Start(AtomBase&);
static void CenterVideoSinkDevice_Stop(AtomBase&);
static void CenterVideoSinkDevice_Uninitialize(AtomBase&);
static bool CenterVideoSinkDevice_ProcessPacket(AtomBase&, PacketValue& in, PacketValue& out);

	
static bool ContextBase_Initialize(NativeContextBase& ctx, AtomBase&, const Script::WorldState&);
static bool ContextBase_PostInitialize(NativeContextBase& ctx, AtomBase&);
static bool ContextBase_Start(NativeContextBase& ctx, AtomBase&);
static void ContextBase_Stop(NativeContextBase& ctx, AtomBase&);
static void ContextBase_Uninitialize(NativeContextBase& ctx, AtomBase&);
static bool ContextBase_ProcessPacket(NativeContextBase& ctx, AtomBase&, PacketValue& in, PacketValue& out);
static bool ContextBase_AttachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other);
static void ContextBase_DetachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other);

	
