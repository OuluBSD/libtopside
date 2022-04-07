// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.7 20:44:33

static bool ServerInstance_Initialize(AtomBase&, const Script::WorldState&);
static bool ServerInstance_PostInitialize(AtomBase&);
static bool ServerInstance_Start(AtomBase&);
static void ServerInstance_Stop(AtomBase&);
static void ServerInstance_Uninitialize(AtomBase&);
static bool ServerInstance_ProcessPacket(AtomBase&, PacketValue& in, PacketValue& out);

	
bool CreateServerInstance(NativeServerInstance& a0);
void ClearServerInstance(NativeServerInstance& a0);
void SetRootPath(NativeServerInstance& a0, String path);
void SetPort(NativeServerInstance& a0, int port);
bool Open(NativeServerInstance& a0);
bool Close(NativeServerInstance& a0);
