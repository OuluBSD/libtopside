// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

static bool SourceDevice_Initialize(NativeSourceDevice& dev, AtomBase&, const Script::WorldState&);
static void SourceDevice_Start(NativeSourceDevice& dev);
static void SourceDevice_Stop(NativeSourceDevice& dev);
static void SourceDevice_Uninitialize(NativeSourceDevice& dev);
static bool SourceDevice_ProcessPacket(NativeSourceDevice& dev, PacketValue& v);

static bool SourceDevice_Poll(NativeSourceDevice& o, UPP::CtrlEvent& e);
static uint32 SourceDevice_GetTickCount(NativeSourceDevice& o);
static void SourceDevice_WaitEvent(NativeSourceDevice& o, int ms);
static bool SourceDevice_IsWaitingEvent(NativeSourceDevice& o);
	
