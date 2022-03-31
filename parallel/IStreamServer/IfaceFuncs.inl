// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

static bool StreamServer_Initialize(AtomBase&, const Script::WorldState&);
static bool StreamServer_PostInitialize();
static bool StreamServer_Start();
static void StreamServer_Stop();
static void StreamServer_Uninitialize();
static bool StreamServer_ProcessPacket(PacketValue& v);

	
bool CreateServerInstance(NativeStreamServer& a0);
void ClearServerInstance(NativeStreamServer& a0);
void SetPort(NativeStreamServer& a0, int port);
bool Open(NativeStreamServer& a0);
bool Close(NativeStreamServer& a0);
