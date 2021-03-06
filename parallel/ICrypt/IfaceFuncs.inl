// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool Crypt_Initialize(NativeCrypt& dev, AtomBase&, const Script::WorldState&);
static bool Crypt_PostInitialize(NativeCrypt& dev, AtomBase&);
static bool Crypt_Start(NativeCrypt& dev, AtomBase&);
static void Crypt_Stop(NativeCrypt& dev, AtomBase&);
static void Crypt_Uninitialize(NativeCrypt& dev, AtomBase&);
static bool Crypt_Send(NativeCrypt& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);

static bool Crypt_CreateNativeCrypt(NativeCrypt& o);
static void Crypt_ClearNativeCrypt(NativeCrypt& o);
static void Crypt_Encrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out);
static void Crypt_Decrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out);
	
