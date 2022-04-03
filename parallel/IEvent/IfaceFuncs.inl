// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 11:11:55

static bool SourceDevice_Initialize(NativeSourceDevice& dev, AtomBase&, const Script::WorldState&);
static bool SourceDevice_PostInitialize(NativeSourceDevice& dev, AtomBase&);
static bool SourceDevice_Start(NativeSourceDevice& dev, AtomBase&);
static void SourceDevice_Stop(NativeSourceDevice& dev, AtomBase&);
static void SourceDevice_Uninitialize(NativeSourceDevice& dev, AtomBase&);
static bool SourceDevice_ProcessPacket(NativeSourceDevice& dev, AtomBase&, PacketValue& v);

static bool SourceDevice_Poll(NativeSourceDevice& o, UPP::CtrlEvent& e);
static uint32 SourceDevice_GetTickCount(NativeSourceDevice& o);
static void SourceDevice_WaitEvent(NativeSourceDevice& o, int ms);
static bool SourceDevice_IsWaitingEvent(NativeSourceDevice& o);
	
