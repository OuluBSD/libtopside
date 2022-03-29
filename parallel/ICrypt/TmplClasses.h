// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _ICrypt_TmplClasses_h_
#define _ICrypt_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Cry> struct CryptCryptT;


template <class Cry>
struct CryptCryptT : CryCrypt {
	typename Cry::NativeCrypt dev;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Cry::Crypt_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Cry::Crypt_Uninitialize(dev);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Cry::Crypt_ProcessPacket(dev, v))
			return false;
		return true;
	}

	bool CreateNativeCrypt() {
		return Cry::Crypt_CreateNativeCrypt(this->dev);
	}
	
	void ClearNativeCrypt() {
		Cry::Crypt_ClearNativeCrypt(this->dev);
	}
	
	void Encrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out) {
		Cry::Crypt_Encrypt(a0, Vector<byte>& in, out);
	}
	
	void Decrypt(NativeCrypt& a0, const Vector<byte>& in, Vector<byte>& out) {
		Cry::Crypt_Decrypt(a0, Vector<byte>& in, out);
	}
	
	
};



NAMESPACE_PARALLEL_END



#endif

