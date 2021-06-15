#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN
namespace Crypto {

double Basic::log(double d) {return log_fast_lb(d);}
double Basic::sqrt(double d) {return pow_fast(d, 0.5);}
double Basic::pow(double a, double b) {return std::pow(a, b);}



Basic::Basic() {
	Clear();
}

void Basic::Clear() {
	pub = 0;
	priv = 0;
	n = 0;
}

void Basic::GenerateKeys() {
	String a;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 0x100; j++)
			a.Cat(j);
	
	int iter = 0;
	while(true) {
		for(int i = 0; i < parts; i++) {
			key64 p = Basic::GenerateProst();
			key64 q = Basic::GenerateProst();
			key64 f = (p - 1) * (q - 1);
			
			key64 n = p * q;
			key64 pub = Basic::GenerateCoprime(f);
			key64 priv = Basic::GenerateD(f, pub);
			
			if (n < 0x10000 && pub < 0x10000 && priv < 0x10000 &&
				n > 0 && pub > 0 && priv > 0) {
				n16[i]    = (uint16)n;
				pub16[i]  = (uint16)pub;
				priv16[i] = (uint16)priv;
			}
			else {
				i--;
			}
		}
		
		String b = Decrypt(Encrypt(a));
		if (a.GetCount() == b.GetCount() &&
			MemoryCompare(a.Begin(), b.Begin(), a.GetCount()) == 0)
			return;
		
		++iter;
	}
	Panic("Could not generate key");
}

bool Basic::SetKeys(String pub, String priv) {
	const int len = (sizeof(key64) * 2) * 2;
	if (pub.GetCount() != len || priv.GetCount() != len)
		return false;
	
	key64 pub_n		= StrKey(pub.Mid(16));
	key64 priv_n	= StrKey(priv.Mid(16));
	
	if (pub_n != priv_n || pub_n == 0)
		return false;
	
	this->pub  = StrKey(pub.Left(16));
	this->priv = StrKey(priv.Left(16));
	
	return this->pub != 0 && this->priv != 0;
}

bool Basic::SetPublicKey(String key) {
	const int len = (sizeof(key64) * 2) * 2;
	if (key.GetCount() != len)
		return false;
	
	n   = StrKey(key.Mid(16));
	pub = StrKey(key.Left(16));
	return pub != 0 && n != 0;
}

bool Basic::SetPrivateKey(String key) {
	const int len = (sizeof(key64) * 2) * 2;
	if (key.GetCount() != len)
		return false;
	
	n    = StrKey(key.Mid(16));
	priv = StrKey(key.Left(16));
	return priv != 0 && n != 0;
}

bool Basic::SetCertificateKey(const Signer& sign, String cert) {
	if (!sign.Verify(GetPublicKey(), cert))
		return false;
	this->cert = cert;
	return true;
}

String Basic::KeyStr(key64 k) {
	union {
		uint64 u64;
		uint8 bytes[8];
	};
	u64 = k;
	String out;
	out.Reserve(16);
	for(int i = 0; i < 8; i++) {
		uint8 b = bytes[i];
		uint8 hi = b >> 4;
		uint8 lo = b & 0xF;
		out.Cat(HexDigit(hi));
		out.Cat(HexDigit(lo));
	}
	return out;
}

int DigitHex(int chr) {
	if (chr >= '0' && chr <= '9')
		return chr - '0';
	if (chr >= 'a' && chr <= 'z')
		return chr - 'a' + 10;
	if (chr >= 'A' && chr <= 'Z')
		return chr - 'A' + 10;
	return -1;
}
key64 Basic::StrKey(String s) {
	union {
		uint64 u64;
		uint8 bytes[8];
	};
	if (s.GetCount() != 16)
		return 0;
	for(int i = 0; i < 8; i++) {
		uint8 hi = DigitHex(s[2 * i]);
		uint8 lo = DigitHex(s[2 * i + 1]);
		uint8 b = (hi << 4) | lo;
		bytes[i] = b;
	}
	return u64;
}

String Basic::GetPublicKey() const {
	return KeyStr(pub) + KeyStr(n);
}

String Basic::GetPrivateKey() const {
	return KeyStr(priv) + KeyStr(n);
}

String Basic::Encrypt(String msg) const {
	ASSERT(n && pub);
	String out;
	out.Reserve(msg.GetCount() * 2);
	uint16 prev_u16 = 0;
	const char* it = msg.Begin();
	const char* end = msg.End();
	while (it != end) {
		union {
			uint16 u16;
			char b[2];
		};
		b[0] = (byte)*it++;
		b[1] = 0;
		uint16 tmp = u16;
		for(int j = 0; j < parts; j++) {
			key64 u64 = PowerMod(u16, pub16[j], n16[j]);
			ASSERT(u64 < 0x10000);
			u16 = (uint16)u64;
		}
		u16 = u16 ^ prev_u16;
		prev_u16 = tmp;
		out.Cat(b[0]);
		out.Cat(b[1]);
	}
	return out;
}

String Basic::Decrypt(String msg) const {
	ASSERT(n && priv);
	String out;
	out.Reserve(msg.GetCount() / 2);
	uint16 prev_u16 = 0;
	if (msg.GetCount() % 2)
		msg.Cat(0); // shouldn't happen
	const char* it = msg.Begin();
	const char* end = msg.End();
	while (it != end) {
		union {
			uint16 u16;
			char b[2];
		};
		b[0] = *it++;
		b[1] = *it++;
		u16 = u16 ^ prev_u16;
		for(int j = parts-1; j >= 0; j--) {
			key64 u64 = PowerMod(u16, priv16[j], n16[j]);
			ASSERT(u64 < 0x10000);
			u16 = (uint16)u64;
		}
		prev_u16 = u16;
		out.Cat(b[0]);
	}
	return out;
}

key64 Basic::powxy(key64 x, key64 y) {
	const key64 M = (key64)(1e9 + 7.0);
    if (y == 0) return 1;
    if (y%2 == 1) return (x*powxy(x, y-1)) % M;
    key64 t = powxy(x, y/2);
    return (t*t)%M;
}

key64 Basic::PowerMod(key64 pa_, key64 pd_, key64 pn_) {
	//typedef __int128 BigInt;
	typedef key64 BigInt;
	BigInt pa = pa_;
	BigInt pd = pd_;
	BigInt pn = pn_;
	
	static thread_local int r;
	static thread_local BigInt prev_pd;
	if (prev_pd != pd) {
		r = (int)(log((double)Abs(pd))/log(2) + 1);
		prev_pd = pd;
	}
	
	BigInt one = 1;
	BigInt prev = pa;
	for (int i = 1; i < r; i++){
		BigInt shift = r-1-i;
		bool bit = pd & (one << shift);
		BigInt a = prev % pn;
		if (bit)
			prev = (((a * a) % pn) * (pa % pn)) % pn;
		else
			prev = ((a * a) % pn);
	}
	return prev;
}

bool Basic::IsProst(key64 n) {
	bool k = true;
	if (n != 2){
		key64 end = (key64) sqrt((double)n) + 1;
		for (key64 i = 2; i < end; i++){
			if (n % i == 0){
				k = false;
				break;
			}
		}
	}
	return k;
}

key64 Basic::GenerateProst() {
	key64 r = Random();
	key64 t = 10 + r % 90ULL;

	do{
		t++;
	}
	while (!IsProst(t));

	return t;
}

key64 Basic::Evklid(key64 num1, key64 num2) {
	key64 prev1 = max(num1,num2);
	key64 prev0 = min(num1,num2);
	while (prev0 != 0) {
		key64 cur = prev1 % prev0;
		prev1 = prev0;
		prev0 = cur;
	}
	return prev1;
}

key64 Basic::GenerateCoprime(key64 x) {
	key64 i = 1 + rand() % 99;
	do {
		i++;
	}
	while (Evklid(x,i) != 1);
	return i;
}

key64 Basic::GenerateD(key64 f, key64 e) {
	//return (int) ((f * (1 + rand() % 4) + 1) / e);
	for (int i = 1; i < 100; i++) {
		key64 v = (f * (i) + 1);
		if ((v % e) == 0) {
			return (key64) (v / e);
		}
	}
	return 0;
}




















Signer::Signer() {
	
}

bool Signer::SetKeys(String priv, String pub) {
	return crypto.SetKeys(priv, pub); // priv/pub crossed intentionally
}

bool Signer::SetPublicKey(String key) {
	return crypto.SetPrivateKey(key); // priv/pub crossed intentionally
}

bool Signer::SetPrivateKey(String key) {
	return crypto.SetPublicKey(key); // priv/pub crossed intentionally
}

String Signer::GetPublicKey() const {
	return crypto.GetPrivateKey(); // priv/pub crossed intentionally
}

String Signer::GetPrivateKey() const {
	return crypto.GetPublicKey(); // priv/pub crossed intentionally
}

String Signer::Sign(String msg) const {
	String hash = MD5String(msg);
	return crypto.Encrypt(hash);
}

bool Signer::Verify(String msg, String sign) const {
	String hash = MD5String(msg);
	String exp_hash = crypto.Decrypt(sign);
	return hash.GetCount() && hash == exp_hash;
}

bool Signer::VerifyCertification(const Basic& crypto) const {
	String cert = crypto.GetCertificateKey();
	String pub_key = crypto.GetPublicKey();
	String hash = MD5String(pub_key);
	String exp_hash = this->crypto.Decrypt(cert);
	return hash.GetCount() && hash == exp_hash;
}






}
NAMESPACE_TOPSIDE_END
