// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

static bool Crypt_Initialize(NativeCrypt& dev, AtomBase&, const Script::WorldState&);
static bool Crypt_Start(NativeCrypt& dev);
static void Crypt_Stop(NativeCrypt& dev);
static void Crypt_Uninitialize(NativeCrypt& dev);
static bool Crypt_ProcessPacket(NativeCrypt& dev, PacketValue& v);

static bool Crypt_CreateNativeCrypt(NativeCrypt& o);
static void Crypt_ClearNativeCrypt(NativeCrypt& o);
static void Crypt_Encrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out);
static void Crypt_Decrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out);
	
