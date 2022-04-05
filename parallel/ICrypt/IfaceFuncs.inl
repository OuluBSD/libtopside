// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 0:00:44

static bool Crypt_Initialize(NativeCrypt& dev, AtomBase&, const Script::WorldState&);
static bool Crypt_PostInitialize(NativeCrypt& dev, AtomBase&);
static bool Crypt_Start(NativeCrypt& dev, AtomBase&);
static void Crypt_Stop(NativeCrypt& dev, AtomBase&);
static void Crypt_Uninitialize(NativeCrypt& dev, AtomBase&);
static bool Crypt_ProcessPacket(NativeCrypt& dev, AtomBase&, PacketValue& in, PacketValue& out);

static bool Crypt_CreateNativeCrypt(NativeCrypt& o);
static void Crypt_ClearNativeCrypt(NativeCrypt& o);
static void Crypt_Encrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out);
static void Crypt_Decrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out);
	
