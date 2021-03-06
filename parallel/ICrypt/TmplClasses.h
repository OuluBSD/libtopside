// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ICrypt_TmplClasses_h_
#define _ICrypt_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Cry> struct CryptCryptT;



template <class Cry>
struct CryptCryptT : CryCrypt {
	using CLASSNAME = CryptCryptT<Cry>;
	RTTI_DECL1(CLASSNAME, CryCrypt)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<CryCrypt>(this);}
	
	typename Cry::NativeCrypt dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Cry::Crypt_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Cry::Crypt_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Cry::Crypt_Start(dev, *this);
	}

	void Stop() override {
		Cry::Crypt_Stop(dev, *this);
	}

	void Uninitialize() override {
		Cry::Crypt_Uninitialize(dev, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Cry::Crypt_Send(dev, *this, cfg, out, src_ch))
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

