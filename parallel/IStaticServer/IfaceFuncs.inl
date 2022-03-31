// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

static bool ServerInstance_Initialize(AtomBase&, const Script::WorldState&);
static bool ServerInstance_Start();
static void ServerInstance_Stop();
static void ServerInstance_Uninitialize();
static bool ServerInstance_ProcessPacket(PacketValue& v);

	
bool CreateServerInstance(NativeServerInstance& a0);
void ClearServerInstance(NativeServerInstance& a0);
void SetRootPath(NativeServerInstance& a0, String path);
void SetPort(NativeServerInstance& a0, int port);
bool Open(NativeServerInstance& a0);
bool Close(NativeServerInstance& a0);
