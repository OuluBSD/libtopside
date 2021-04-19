#include "Oulu.h"

NAMESPACE_OULU_BEGIN
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
		if (a == b)
			break;
	}
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
			uint8 b[2];
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
			uint8 b[2];
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
		r = (log(Abs(pd))/log(2)) + 1;
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
		key64 end = (key64) sqrt(n) + 1;
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
	key64 t = 10 + rand() % 90;

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
		if (((f * (i) + 1) % e) == 0) {
			return (key64) ((f * (i) + 1) / e);
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














void EncryptionTest() {
	
	if (1) {
		COUT("---- Manual usage test ----");
		key64 p = Basic::GenerateProst();
		key64 q = Basic::GenerateProst();
		key64 f = (p-1)*(q-1);
		key64 n = p*q;
		key64 e = Basic::GenerateCoprime(f);
		key64 d = Basic::GenerateD(f,e);
	
		COUT("p = " << p);
		COUT("q = " << q);
		COUT("n = " << n);
		COUT("f = " << f);
		COUT("e = " << e);
		COUT("d = " << d);
	
		String a, b;
		Vector<key64> c;
		
		//Encryption
		a = "crypto";
		COUT("Input: " << a);
		for (int i = 0; i < a.GetCount(); i++) {
			key64 x = a[i];
			c.Add(Basic::PowerMod(x,e,n));
		}
		
		COUT("Mid:");
		for(int i = 0; i < c.GetCount(); i++) {
			COUT("\tc[" << i << "] = " << c[i]);
		}
	
		// Decryption
		for (int i = 0; i < c.GetCount(); i++) {
			b.Cat(Basic::PowerMod(c[i],d,n));
		}
		COUT("Output: " << b);
	}
	
	
	if (1) {
		COUT("\n\n---- Crypto class test ----");
		//String msg = "Hello host!";
		String msg;
		for(int i = 0; i < 10*1024; i++) {
			msg.Cat(Random(0x100));
		}
		
		String pub;
		String priv;
		String enc_msg;
		String dec_msg;
		{
			Crypto::Basic gen;
			gen.GenerateKeys();
			pub = gen.GetPublicKey();
			priv = gen.GetPrivateKey();
			COUT("Generated keys:");
			COUT("\tPublic:  " << pub);
			COUT("\tPrivate: " << priv);
		}
		
		{
			Crypto::Basic someone;
			someone.SetPublicKey(pub);
			//1.6 enc_msg = BZ2Compress(someone.Encrypt(msg));
			//1.7 enc_msg = ZCompress(someone.Encrypt(msg));
			//1.8 enc_msg = BZ2Compress(someone.Encrypt(BZ2Compress(msg)));
			//1.8 enc_msg = ZCompress(someone.Encrypt(ZCompress(msg)));
			//2.0 enc_msg = someone.Encrypt(ZCompress(msg));
			//2.0 enc_msg = someone.Encrypt(msg);
			//2.1 enc_msg = someone.Encrypt(BZ2Compress(msg));
			//2.4 enc_msg = Encode64(ZCompress(someone.Encrypt(ZCompress(msg))));
			
			enc_msg = BZ2Compress(someone.Encrypt(msg));
			
			COUT("Encrypted message:");
			COUT("\tPublic:    " << someone.GetPublicKey());
			COUT("\tOriginal:  " << HexEncode(msg).Left(80));
			COUT("\tEncrypted: " << HexEncode(enc_msg).Left(80));
			COUT("\tSize:      " << msg.GetCount() << " --> " << enc_msg.GetCount());
		}
		
		{
			Crypto::Basic receiver;
			receiver.SetPrivateKey(priv);
			//dec_msg = receiver.Decrypt(BZ2Decompress(enc_msg));
			//dec_msg = receiver.Decrypt(ZDecompress(enc_msg));
			//dec_msg = BZ2Decompress(receiver.Decrypt(BZ2Decompress(enc_msg)));
			//dec_msg = ZDecompress(receiver.Decrypt(ZDecompress(enc_msg)));
			//dec_msg = ZDecompress(receiver.Decrypt(enc_msg));
			//dec_msg = receiver.Decrypt(enc_msg);
			//dec_msg = BZ2Decompress(receiver.Decrypt(enc_msg));
			//dec_msg = ZDecompress(receiver.Decrypt(ZDecompress(Decode64(enc_msg))));
			
			dec_msg = receiver.Decrypt(BZ2Decompress(enc_msg));
			
			COUT("Decrypted message:");
			COUT("\tPrivate:   " << receiver.GetPrivateKey());
			COUT("\tEncrypted: " << HexEncode(enc_msg).Left(80));
			COUT("\tDecrypted: " << HexEncode(dec_msg).Left(80));
			if (0) for(int i = 0; i < msg.GetCount() && i < dec_msg.GetCount(); i++) {
				COUT("\t\t" << i << ": " << (int)msg[i] << "\t" << (int)dec_msg[i]);
			}
		}
		
		if (msg == dec_msg)	{COUT("Success");}
		else				{COUT("Fail");}
	}
	
	
	if (1) {
		COUT("\n\n---- Trust chain test ----");
		
		struct Node {
			VectorMap<int, Crypto::Basic> send;
			Crypto::Basic recv;
			Crypto::Basic master_send;
			Crypto::Signer sign;
			Crypto::Signer master_sign;
			int id = -1;
			int parent = -1;
			
			void Init() {
				recv.GenerateKeys();
				sign.GenerateKeys();
			}
			String Encrypt(int id, String msg) const {
				return send[id].Encrypt(msg);
			}
			String Decrypt(String msg) const {
				return recv.Decrypt(msg);
			}
			void Add(Node& n) {
				ASSERT(id >= 0);
				n.parent = id;
				send.Add(n.id) << n.recv;
				n.send.Add(id) << recv;
			}
			bool Verify(Node& parent) {
				bool r = master_sign.VerifyCertification(parent.recv);
				if (r) {
					COUTLOG(id << " verified " << parent.id << " successfully");
				}
				else {
					COUTLOG(id << " verification of " << parent.id << " failed");
				}
				return r;
			}
			void GetSelfCertified() {
				String pub_key = recv.GetPublicKey();
				String cert = sign.Sign(pub_key);
				recv.SetCertificateKey(sign, cert);
			}
			bool GetCertified(Array<Node>& nodes) {
				// Node encrypts public key and sends it to the master
				// The public key is not known to other nodes yet
				String pub_key = recv.GetPublicKey();
				String enc_pub_key = master_send.Encrypt(pub_key);
				
				String link_msg = enc_pub_key;
				Vector<int> path;
				Node* cur = this;
				{
					while (cur->parent >= 0) {
						path.Add(cur->id);
						Node* parent_n = &nodes[cur->parent];
						
						// Current sends to parent
						String link_enc_msg = cur->send.Get(cur->parent).Encrypt(link_msg);
						
						// Parent reads message
						String link_dec_msg = parent_n->recv.Decrypt(link_enc_msg);
						if (link_dec_msg != link_msg) {
							COUTLOG("---> Link transfer failed");
							return false;
						}
						link_msg = link_dec_msg;
						
						cur = parent_n;
					}
					Reverse(path);
				}
				
				if (link_msg != enc_pub_key) {
					COUTLOG("---> Mesh transfer failed");
					return false;
				}
				
				ASSERT(cur->parent < 0);
				String master_recv_pub_key = cur->recv.Decrypt(link_msg);
				if (master_recv_pub_key != pub_key) {
					COUTLOG("---> Master received incorrect public key");
					return false;
				}
				
				// Master signs the public key and sends the certificate back
				String cert = cur->sign.Sign(master_recv_pub_key);
				Crypto::Basic send_of_master;
				send_of_master.SetPublicKey(master_recv_pub_key);
				String enc_cert = send_of_master.Encrypt(cert);
				
				link_msg = enc_cert;
				{
					for(int i = 0; i < path.GetCount(); i++) {
						int child_id = path[i];
						
						// Current sends towards original sender
						String link_enc_msg = cur->send.Get(child_id).Encrypt(link_msg);
						
						// Child decrypts the message
						Node& child = nodes[child_id];
						String link_dec_msg = child.recv.Decrypt(link_enc_msg);
						
						if (link_dec_msg != link_msg) {
							COUTLOG("<--- Link transfer failed");
							return false;
						}
						link_msg = link_dec_msg;
						
						cur = &child;
					}
				}
				
				if (link_msg != enc_cert) {
					COUTLOG("<--- Mesh transfer failed");
					return false;
				}
				
				// Node receives the certificate
				String recv_cert = recv.Decrypt(link_msg);
				if (recv_cert != cert) {
					COUTLOG("<--- Cert transfer failed (" << recv_cert << " != " << cert << ")");
					return false;
				}
				
				return recv.SetCertificateKey(master_sign, recv_cert);
			}
		};
		Array<Node> nodes;
		
		Node& master = nodes.Add();
		master.id = 0;
		master.Init();
		master.GetSelfCertified();
		
		for(int i = 0; i < 20; i++) {
			int id = nodes.GetCount();
			Node& n = nodes.Add();
			n.id = id;
			n.master_send.SetPublicKey(master.recv.GetPublicKey());
			n.master_sign.SetPublicKey(master.sign.GetPublicKey());
			n.Init();
			Node& m = nodes[Random(nodes.GetCount()-1)];
			m.Add(n);
			if (!n.Verify(m))
				return;
			n.GetCertified(nodes);
		}
		
		TimeStop ts;
		for(int iter = 0; iter < 20; iter++) {
			int from = Random(nodes.GetCount());
			Node& f = nodes[from];
			
			int to;
			if (Random(2) && f.parent >= 0)
				to = f.parent;
			else if (f.send.GetCount())
				to = f.send.GetKey(Random(f.send.GetCount()));
			else
				continue;
			Node& t = nodes[to];
			
			String msg;
			for(int i = 0; i < 10; i++)
				msg.Cat('a' + Random('z' - 'a' + 1));
			
			String enc_msg = f.Encrypt(to, msg);
			String dec_msg = t.Decrypt(enc_msg);
			
			if (dec_msg == msg) {
				COUTLOG(from << " --> " << to << " sent successfully");
			}
			else {
				COUTLOG(from << " --> " << to << " sending failed");
			}
		}
	}
}

}
NAMESPACE_OULU_END
