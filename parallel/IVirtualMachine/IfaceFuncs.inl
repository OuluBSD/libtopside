// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

static bool VirtualMachine_Initialize(AtomBase&, const Script::WorldState&);
static void VirtualMachine_Start();
static void VirtualMachine_Stop();
static void VirtualMachine_Uninitialize();
static bool VirtualMachine_ProcessPacket(PacketValue& v);

	
static bool Thread_Initialize(AtomBase&, const Script::WorldState&);
static void Thread_Start();
static void Thread_Stop();
static void Thread_Uninitialize();
static bool Thread_ProcessPacket(PacketValue& v);

	
bool CreateVirtualMachine(NativeVirtualMachine& a0);
void ClearVirtualMachine(NativeVirtualMachine& a0);
bool CreateThread(NativeVirtualMachine& a0, NativeThread& a1);
void ClearThread(NativeThread& a0);
bool Run(NativeThread& a0, String filepath, String script, const StringMap* args);
void Stop(NativeThread& a0);
bool IsRunning(NativeThread& a0);
