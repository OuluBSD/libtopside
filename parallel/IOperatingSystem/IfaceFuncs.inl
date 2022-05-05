// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool MessageBus_Initialize(AtomBase&, const Script::WorldState&);
static bool MessageBus_PostInitialize(AtomBase&);
static bool MessageBus_Start(AtomBase&);
static void MessageBus_Stop(AtomBase&);
static void MessageBus_Uninitialize(AtomBase&);
static bool MessageBus_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool ProcessManager_Initialize(AtomBase&, const Script::WorldState&);
static bool ProcessManager_PostInitialize(AtomBase&);
static bool ProcessManager_Start(AtomBase&);
static void ProcessManager_Stop(AtomBase&);
static void ProcessManager_Uninitialize(AtomBase&);
static bool ProcessManager_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool DesktopManager_Initialize(AtomBase&, const Script::WorldState&);
static bool DesktopManager_PostInitialize(AtomBase&);
static bool DesktopManager_Start(AtomBase&);
static void DesktopManager_Stop(AtomBase&);
static void DesktopManager_Uninitialize(AtomBase&);
static bool DesktopManager_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
bool CreateMessageBus(NativeMessageBus& a0);
void ClearMessageBus(NativeMessageBus& a0);
