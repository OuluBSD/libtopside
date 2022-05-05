// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool SourceDevice_Initialize(NativeSourceDevice& dev, AtomBase&, const Script::WorldState&);
static bool SourceDevice_PostInitialize(NativeSourceDevice& dev, AtomBase&);
static bool SourceDevice_Start(NativeSourceDevice& dev, AtomBase&);
static void SourceDevice_Stop(NativeSourceDevice& dev, AtomBase&);
static void SourceDevice_Uninitialize(NativeSourceDevice& dev, AtomBase&);
static bool SourceDevice_Send(NativeSourceDevice& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

static bool SourceDevice_Poll(NativeSourceDevice& o, UPP::CtrlEvent& e);
static uint32 SourceDevice_GetTickCount(NativeSourceDevice& o);
static void SourceDevice_WaitEvent(NativeSourceDevice& o, int ms);
static bool SourceDevice_IsWaitingEvent(NativeSourceDevice& o);
	
