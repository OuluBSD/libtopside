// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool VirtualMachine_Initialize(AtomBase&, const Script::WorldState&);
static bool VirtualMachine_PostInitialize(AtomBase&);
static bool VirtualMachine_Start(AtomBase&);
static void VirtualMachine_Stop(AtomBase&);
static void VirtualMachine_Uninitialize(AtomBase&);
static bool VirtualMachine_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
static bool Thread_Initialize(AtomBase&, const Script::WorldState&);
static bool Thread_PostInitialize(AtomBase&);
static bool Thread_Start(AtomBase&);
static void Thread_Stop(AtomBase&);
static void Thread_Uninitialize(AtomBase&);
static bool Thread_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
bool CreateVirtualMachine(NativeVirtualMachine& a0);
void ClearVirtualMachine(NativeVirtualMachine& a0);
bool CreateThread(NativeVirtualMachine& a0, NativeThread& a1);
void ClearThread(NativeThread& a0);
bool Run(NativeThread& a0, String filepath, String script, const StringMap* args);
void Stop(NativeThread& a0);
bool IsRunning(NativeThread& a0);
