// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

static bool ServerInstance_Initialize(AtomBase&, const Script::WorldState&);
static void ServerInstance_Start();
static void ServerInstance_Stop();
static void ServerInstance_Uninitialize();
static bool ServerInstance_ProcessPacket(PacketValue& v);

	
bool CreateServerInstance(NativeServerInstance& a0);
void ClearServerInstance(NativeServerInstance& a0);
void SetRootPath(NativeServerInstance& a0, String path);
void SetPort(NativeServerInstance& a0, int port);
bool Open(NativeServerInstance& a0);
bool Close(NativeServerInstance& a0);
