// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool NetFile_Initialize(AtomBase&, const Script::WorldState&);
static bool NetFile_PostInitialize(AtomBase&);
static bool NetFile_Start(AtomBase&);
static void NetFile_Stop(AtomBase&);
static void NetFile_Uninitialize(AtomBase&);
static bool NetFile_Send(AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

	
bool CreateNetFile(NativeNetFile& a0);
void ClearNetFile(NativeNetFile& a0);
