// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

static bool MessageBus_Initialize(AtomBase&, const Script::WorldState&);
static bool MessageBus_Start();
static void MessageBus_Stop();
static void MessageBus_Uninitialize();
static bool MessageBus_ProcessPacket(PacketValue& v);

	
static bool ProcessManager_Initialize(AtomBase&, const Script::WorldState&);
static bool ProcessManager_Start();
static void ProcessManager_Stop();
static void ProcessManager_Uninitialize();
static bool ProcessManager_ProcessPacket(PacketValue& v);

	
static bool DesktopManager_Initialize(AtomBase&, const Script::WorldState&);
static bool DesktopManager_Start();
static void DesktopManager_Stop();
static void DesktopManager_Uninitialize();
static bool DesktopManager_ProcessPacket(PacketValue& v);

	
bool CreateMessageBus(NativeMessageBus& a0);
void ClearMessageBus(NativeMessageBus& a0);
