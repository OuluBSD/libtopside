// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool StreamServer_Initialize(AtomBase&, const Script::WorldState&);
static bool StreamServer_PostInitialize(AtomBase&);
static bool StreamServer_Start(AtomBase&);
static void StreamServer_Stop(AtomBase&);
static void StreamServer_Uninitialize(AtomBase&);
static bool StreamServer_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
bool CreateServerInstance(NativeStreamServer& a0);
void ClearServerInstance(NativeStreamServer& a0);
void SetPort(NativeStreamServer& a0, int port);
bool Open(NativeStreamServer& a0);
bool Close(NativeStreamServer& a0);
