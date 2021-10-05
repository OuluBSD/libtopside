#include <Local/Local.h>
using namespace TS::Crypto;
using namespace TS;
using namespace UPP;



CONSOLE_APP_MAIN {
	SetCoutLog();
	
	if (1) {
		LOG("---- Manual usage test ----");
		key64 p = Basic::GenerateProst();
		key64 q = Basic::GenerateProst();
		key64 f = (p-1)*(q-1);
		key64 n = p*q;
		key64 e = Basic::GenerateCoprime(f);
		key64 d = Basic::GenerateD(f,e);
		ASSERT(n != 121 || p != 11 || q != 11);
		
		LOG("p = " << IntStr64(p));
		LOG("q = " << IntStr64(q));
		LOG("n = " << IntStr64(n));
		LOG("f = " << IntStr64(f));
		LOG("e = " << IntStr64(e));
		LOG("d = " << IntStr64(d));
	
		String a, b;
		Vector<key64> c;
		
		//Encryption
		a = "crypto";
		LOG("Input: " << a);
		for (int i = 0; i < a.GetCount(); i++) {
			key64 x = (byte)a[i];
			key64 chr = Basic::PowerMod(x,e,n);
			c.Add(chr);
		}
		
		LOG("Mid:");
		for(int i = 0; i < c.GetCount(); i++) {
			LOG("\tc[" << i << "] = " << IntStr64(c[i]));
		}
	
		// Decryption
		for (int i = 0; i < c.GetCount(); i++) {
			key64 chr = c[i];
			key64 v = Basic::PowerMod(chr,d,n);
			b.Cat((byte)v);
		}
		LOG("Output: " << b);
	}
	
	
	if (1) {
		LOG("\n\n---- Crypto class test ----");
		//String msg = "Hello host!";
		String msg;
		for(int i = 0; i < 6; i++) {
		//for(int i = 0; i < 10*1024; i++) {
			msg.Cat(Random(0x100));
		}
		
		String pub;
		String priv;
		String enc_msg, enc_msg_chk;
		String dec_msg;
		{
			Crypto::Basic gen;
			gen.GenerateKeys();
			pub = gen.GetPublicKey();
			priv = gen.GetPrivateKey();
			LOG("Generated keys:");
			LOG("\tPublic:  " << pub);
			LOG("\tPrivate: " << priv);
			
			
			// Somehow this fails in WIN32 & MSC...
			// The reason is very weird and even the debugger doesn't behave right.
			ASSERT(msg == BZ2Decompress(BZ2Compress(msg)));
			String enc = gen.Encrypt(msg);
			DUMPC(enc);
			enc_msg_chk = BZ2Compress(enc);
			String decomp = BZ2Decompress(enc_msg_chk);
			DUMPC(decomp);
			if (enc.GetCount() == decomp.GetCount()) {
				for(int i = 0; i < enc.GetCount(); i++) {
					int a = enc[i];
					int b = decomp[i];
					int diff = a-b;
					LOG(a << " - " << b << " = " << diff);
					ASSERT(!diff);
				}
			}
			bool same = enc == decomp;
			ASSERT(enc == decomp);
			String dec = gen.Decrypt(decomp);
			DUMPC(dec);
			DUMPC(msg);
			same = dec == msg;
			ASSERT(dec == msg);
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
			ASSERT(enc_msg == enc_msg_chk);
			
			LOG("Encrypted message:");
			LOG("\tPublic:    " << someone.GetPublicKey());
			LOG("\tOriginal:  " << HexEncode(msg).Left(80));
			LOG("\tEncrypted: " << HexEncode(enc_msg).Left(80));
			LOG("\tSize:      " << msg.GetCount() << " --> " << enc_msg.GetCount());
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
			
			LOG("Decrypted message:");
			LOG("\tPrivate:   " << receiver.GetPrivateKey());
			LOG("\tEncrypted: " << HexEncode(enc_msg).Left(80));
			LOG("\tDecrypted: " << HexEncode(dec_msg).Left(80));
			if (0) for(int i = 0; i < msg.GetCount() && i < dec_msg.GetCount(); i++) {
				LOG("\t\t" << i << ": " << (int)msg[i] << "\t" << (int)dec_msg[i]);
			}
		}
		
		if (msg == dec_msg)	{LOG("Success");}
		else				{LOG("Fail"); SetExitCode(1);}
	}
	
	
	if (1) {
		LOG("\n\n---- Trust chain test ----");
		
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
				return send.Get(id).Encrypt(msg);
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
					LOG(id << " verified " << parent.id << " successfully");
				}
				else {
					LOG(id << " verification of " << parent.id << " failed");
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
							LOG("---> Link transfer failed");
							return false;
						}
						link_msg = link_dec_msg;
						
						cur = parent_n;
					}
					Reverse(path);
				}
				
				if (link_msg != enc_pub_key) {
					LOG("---> Mesh transfer failed");
					return false;
				}
				
				ASSERT(cur->parent < 0);
				String master_recv_pub_key = cur->recv.Decrypt(link_msg);
				if (master_recv_pub_key != pub_key) {
					LOG("---> Master received incorrect public key");
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
							LOG("<--- Link transfer failed");
							return false;
						}
						link_msg = link_dec_msg;
						
						cur = &child;
					}
				}
				
				if (link_msg != enc_cert) {
					LOG("<--- Mesh transfer failed");
					return false;
				}
				
				// Node receives the certificate
				String recv_cert = recv.Decrypt(link_msg);
				if (recv_cert != cert) {
					LOG("<--- Cert transfer failed (" << recv_cert << " != " << cert << ")");
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
				LOG(from << " --> " << to << " sent successfully");
			}
			else {
				LOG(from << " --> " << to << " sending failed");
				SetExitCode(1);
			}
		}
	}
}
