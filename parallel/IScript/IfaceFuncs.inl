// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

static bool Runner_Initialize(AtomBase&, const Script::WorldState&);
static void Runner_Start();
static void Runner_Stop();
static void Runner_Uninitialize();
static bool Runner_ProcessPacket(PacketValue& v);

	
static bool Thread_Initialize(AtomBase&, const Script::WorldState&);
static void Thread_Start();
static void Thread_Stop();
static void Thread_Uninitialize();
static bool Thread_ProcessPacket(PacketValue& v);

	
bool CreateRunner(NativeRunner& a0);
void ClearRunner(NativeRunner& a0);
bool CreateThread(NativeRunner& a0, NativeThread& a1);
void ClearThread(NativeThread& a0);
bool Run(NativeThread& a0, String filepath, String script, const StringMap* args);
void Stop(NativeThread& a0);
bool IsRunning(NativeThread& a0);
