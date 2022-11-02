#ifndef _Local_Crypto_h_
#define _Local_Crypto_h_

NAMESPACE_TOPSIDE_BEGIN
namespace Crypto {
	
typedef uint64 key64;

class Signer;

class Basic : Moveable<Basic> {
	
	static const int parts = 4;
	union {
		key64 pub;
		uint16 pub16[4];
	};
	union {
		key64 priv;
		uint16 priv16[4];
	};
	union {
		key64 n;
		uint16 n16[4];
	};
	String cert;
	
	
public:
	typedef Basic CLASSNAME;
	Basic();
	
	void Clear();
	void GenerateKeys();
	String Encrypt(String msg) const;
	String Decrypt(String msg) const;
	
	bool SetKeys(String pub, String priv);
	bool SetPublicKey(String key);
	bool SetPrivateKey(String key);
	bool SetCertificateKey(const Signer& sign, String key);
	String GetPublicKey() const;
	String GetPrivateKey() const;
	String GetCertificateKey() const {return cert;}
	
	void operator<<(const Basic& c) {Clear(); pub = c.pub; n = c.n;}
	
	
	static double log(double d);
	static double sqrt(double d);
	static double pow(double a, double b);
	static key64 rand() {return Random64();}
	
	static key64 PowerMod(key64 pa, key64 pd, key64 pn);
	static bool IsProst(key64 n);
	static key64 GenerateProst();
	static key64 Evklid(key64 num1, key64 num2);
	static key64 GenerateCoprime(key64 x);
	static key64 GenerateD(key64 f, key64 e);
	static String KeyStr(key64 k);
	static key64 StrKey(String s);
	static key64 powxy(key64 x, key64 y);
	
	static int HexDigit(int c) {return "0123456789ABCDEF"[c & 15];}
	
};


class Signer : Moveable<Signer> {
	Basic crypto;
	
public:
	typedef Signer CLASSNAME;
	Signer();
	
	void GenerateKeys() {crypto.GenerateKeys();}
	
	bool SetKeys(String priv, String pub);
	bool SetPublicKey(String key);
	bool SetPrivateKey(String key);
	String GetPublicKey() const;
	String GetPrivateKey() const;
	
	String Sign(String msg) const;
	bool Verify(String msg, String sign) const;
	bool VerifyCertification(const Basic& crypto) const;
	
};


}
NAMESPACE_TOPSIDE_END

#endif
