// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.5 17:55:33

static bool Runner_Initialize(AtomBase&, const Script::WorldState&);
static bool Runner_PostInitialize(, AtomBase&);
static bool Runner_Start(, AtomBase&);
static void Runner_Stop(, AtomBase&);
static void Runner_Uninitialize(, AtomBase&);
static bool Runner_ProcessPacket(AtomBase&, PacketValue& in, PacketValue& out);

	
static bool Thread_Initialize(AtomBase&, const Script::WorldState&);
static bool Thread_PostInitialize(, AtomBase&);
static bool Thread_Start(, AtomBase&);
static void Thread_Stop(, AtomBase&);
static void Thread_Uninitialize(, AtomBase&);
static bool Thread_ProcessPacket(AtomBase&, PacketValue& in, PacketValue& out);

	
bool CreateRunner(NativeRunner& a0);
void ClearRunner(NativeRunner& a0);
bool CreateThread(NativeRunner& a0, NativeThread& a1);
void ClearThread(NativeThread& a0);
bool Run(NativeThread& a0, String filepath, String script, const StringMap* args);
void Stop(NativeThread& a0);
bool IsRunning(NativeThread& a0);
