#include "Local.h"

INITBLOCK_(Local_Network) {
	using namespace TS;
	
	DaemonBase::Register<SerialServiceServer>("TcpServer");
	DaemonBase::Register<SerialServiceClient>("TcpClient");
	
}

NAMESPACE_TOPSIDE_BEGIN



SerialServiceBase::SerialServiceBase() {
	
}

bool SerialServiceBase::AddTcpSocket(uint32 magic, Callback1<TcpSocket&> cb) {
	int i = handlers.Find(magic);
	if (i >= 0) {
		TcpSocketHandler* h = CastPtr<TcpSocketHandler>(&handlers[i]);
		if (!h)
			return false;
		h->cb << cb;
		return true;
	}
	TcpSocketHandler* h = new TcpSocketHandler();
	h->cb = cb;
	h->magic = magic;
	h->in_sz = 0;
	h->out_sz = 0;
	h->serialized = false;
	h->socket_handler = true;
	handlers.Add(magic, h);
	return true;
}



SerialServiceServer::SerialServiceServer() {
	
}

SerialServiceServer::~SerialServiceServer() {
	CloseTcp();
	StopThread();
}

bool SerialServiceServer::ListenTcp(uint16 port) {
	
	if (tcp.IsOpen())
		CloseTcp();
	
	tcp.Timeout(500);
	
	if (!tcp.Listen(port))
		return false;
	
	return true;
}

void SerialServiceServer::CloseTcp() {
	tcp.Close();
}

void SerialServiceServer::StartThread() {
	StopThread();
	
	ASSERT(tcp.IsOpen());
	if (!tcp.IsOpen()) return;
	
	Thread::Start(THISBACK(ListenerHandler));
}

void SerialServiceServer::ListenerHandler() {
	flag.Start(1);
	
	tcp.Timeout(500);
	
	while (tcp.IsOpen() && flag.IsRunning()) {
		One<TcpSocket> sock;
		sock.Create();
		if (sock->Accept(tcp)) {
			LOG("SerialServiceServer::ListenerHandler: info: accepted " << sock->GetPeerAddr());
			flag.IncreaseRunning();
			Thread::Start(THISBACK1(ClientHandler, sock.Detach()));
		}
	}
	
	flag.DecreaseRunning();
}

void SerialServiceServer::StopThread() {
	flag.Stop();
}

void SerialServiceServer::ClientHandler(TcpSocket* ptr) {
	One<TcpSocket> sock_owner = ptr;
	TcpSocket& sock = *ptr;
	
	LOG("SerialServiceServer::ClientHandler: starting handling client " << sock.GetPeerAddr());
	
	Vector<byte> in, out;
	StringStream ss;
	
	sock.Timeout(3000);
	int wait_count = 0;
	
	while (sock.IsOpen() && flag.IsRunning()) {
		int got = 0, sent = 0;
		
		uint32 magic = 0, in_sz = 0, out_sz = 0;
		
		#define RECV(x) \
			got = sock.Get(&x, sizeof(x));
		#define GET_ERROR(x) \
			if (got != sizeof(x)) { \
				LOG("SerialServiceServer::ClientHandler: error: expected " << (int)sizeof(x) << ", but got " << got); break;}
		#define GET(x) \
			RECV(x) \
			GET_ERROR(x)
		#define SEND(x) \
			sent = sock.Put(&x, sizeof(x)); \
			if (sent != sizeof(x)) { \
				LOG("SerialServiceServer::ClientHandler: error: expected to send " << (int)sizeof(x) << ", but sent " << sent); break;}
		
		RECV(magic);
		if (!magic) {
			if (++wait_count >= keepalive_limit)
				break;
			continue;
		}
		GET_ERROR(magic);
		
		wait_count = 0;
		
		// Keepalive magic
		if (magic == 1)
			continue;
		
		int i = handlers.Find(magic);
		if (i < 0) {
			LOG("SerialServiceServer::ClientHandler: error: could not find magic " << magic);
			magic = 0;
			SEND(magic);
			continue;
		}
		SEND(magic);
		
		//LOG("SerialServiceServer::ClientHandler: info: magic " << magic << ", i " << i);
		
		HandlerBase& hb = handlers[i];
		
		if (hb.socket_handler) {
			//LOG("SerialServiceServer::ClientHandler: info: socket handler enter");
			hb.Call(sock);
			//LOG("SerialServiceServer::ClientHandler: info: socket handler leave");
		}
		else if (hb.serialized) {
			GET(in_sz);
			if (in_sz > 10000000) {
				LOG("SerialServiceServer::ClientHandler: error: too large input packet: " << in_sz);
				break;
			}
			
			GET(out_sz);
			if (out_sz != 0) {
				LOG("SerialServiceServer::ClientHandler: error: unexpected output size: " << out_sz);
				break;
			}
			
			in.SetCount(in_sz);
			got = sock.Get(in.Begin(), in.GetCount());
			if (got != in_sz) {
				LOG("SerialServiceServer::ClientHandler: error: expected " << in_sz << ", but got " << got);
				break;
			}
			
			MemReadStream ms(in.Begin(), in.GetCount());
			//ms.SetLoading();
			ss.SetSize(0);
			ss.SetStoring();
			
			hb.Call(ms, ss);
			
			String result = ss.GetResult();
			out_sz = result.GetCount();
			SEND(out_sz);
			
			sent = sock.Put(result.Begin(), result.GetCount());
			if (sent != out_sz) {
				LOG("SerialServiceServer::ClientHandler: error: couldn't send full structure (" << sent << " < " << hb.out_sz << ")");
				break;
			}
		}
		else {
			GET(in_sz);
			if (in_sz != hb.in_sz) {
				LOG("SerialServiceServer::ClientHandler: error: input structure size mismatch (" << in_sz << " != " << hb.in_sz << ")");
				break;
			}
			
			GET(out_sz);
			if (out_sz != hb.out_sz) {
				LOG("SerialServiceServer::ClientHandler: error: output structure size mismatch (" << out_sz << " != " << hb.out_sz << ")");
				break;
			}
			
			in.SetCount(in_sz);
			got = sock.Get(in.Begin(), in_sz);
			if (got != in_sz) {
				LOG("SerialServiceServer::ClientHandler: error: couldn't receive full structure (" << got << " < " << hb.in_sz << ")");
				break;
			}
			
			out.SetCount(out_sz);
			memset(out.Begin(), 0, out_sz);
			hb.Call(in, out);
			
			sent = sock.Put(out.Begin(), out_sz);
			if (sent != out_sz) {
				LOG("SerialServiceServer::ClientHandler: error: couldn't send full structure (" << sent << " < " << hb.out_sz << ")");
				break;
			}
		}
	}
	#undef RECV
	#undef GET_ERROR
	#undef GET
	#undef SEND
	
	flag.DecreaseRunning();
	
	LOG("SerialServiceServer::ClientHandler: stopped handling client " << sock.GetPeerAddr());
}

bool SerialServiceServer::Init(String name) {
	
	if (!ListenTcp(7776)) {
		LOG("SerialServiceServer::Init: Could not listen port 7776");
		return false;
	}
	
	StartThread();
	
	return true;
}

void SerialServiceServer::Update() {
	
}

void SerialServiceServer::Deinit() {
	tcp.Shutdown();
	tcp.Close();
	StopThread();
}





SerialServiceClient::SerialServiceClient() {
	
}

SerialServiceClient::~SerialServiceClient() {
	CloseTcp();
}

bool SerialServiceClient::ConnectTcp(String addr, uint16 port) {
	CloseTcp();

	return tcp.Connect(addr, port);
}

void SerialServiceClient::CloseTcp() {
	tcp.Close();
}

#define RECV(x) \
	got = sock.Get(&x, sizeof(x));
#define GET_ERROR(x) \
	if (got != sizeof(x)) { \
		LOG("SerialServiceClient::CallMem: error: expected " << (int)sizeof(x) << ", but got " << got); sock.Close(); return false;}
#define GET(x) \
	RECV(x) \
	GET_ERROR(x)
#define SEND(x) \
	sent = sock.Put(&x, sizeof(x)); \
	if (sent != sizeof(x)) { \
		LOG("SerialServiceClient::CallMem: error: expected to send " << (int)sizeof(x) << ", but sent " << sent); sock.Close(); return false;}


bool SerialServiceClient::CallMem(uint32 magic, const void* out, int out_sz, void* in, int in_sz) {
	if (!tcp.IsOpen())
		return false;
	
	auto& sock = tcp;
	uint32 sent = 0, got = 0, got_magic = 0;
	
	SEND(magic);
	GET(got_magic);
	if (!got_magic) {
		LOG("SerialServiceClient::CallMem: error: magic not found on server");
		return false;
	}
	SEND(out_sz);
	SEND(in_sz);
	
	sent = sock.Put(out, out_sz);
	if (sent != out_sz) {
		LOG("SerialServiceClient::CallMem: error: expected to send " << out_sz << ", but sent " << sent);
		return false;
	}
	
	got = sock.Get(in, in_sz);
	if (got != in_sz) {
		LOG("SerialServiceClient::CallMem: error: expected to get " << in_sz << ", but got " << got);
		return false;
	}
	
	return true;
}

bool SerialServiceClient::CallMem(uint32 magic, const void* out, int out_sz, Vector<byte>& in) {
	if (!tcp.IsOpen())
		return false;
	
	auto& sock = tcp;
	int in_sz = 0;
	uint32 sent = 0, got = 0, got_magic = 0;
	
	SEND(magic);
	GET(got_magic);
	if (!got_magic) {
		LOG("SerialServiceClient::CallMem: error: magic not found on server");
		return false;
	}
	SEND(out_sz);
	SEND(in_sz); // == 0
	
	sent = sock.Put(out, out_sz);
	if (sent != out_sz) {
		LOG("SerialServiceClient::CallMem: error: expected to send " << out_sz << ", but sent " << sent);
		return false;
	}
	
	GET(in_sz);
	in.SetCount(in_sz);
	got = sock.Get(in.Begin(), in_sz);
	if (got != in_sz) {
		LOG("SerialServiceClient::CallMem: error: expected to get " << in_sz << ", but got " << got);
		return false;
	}
	
	return true;
}

bool SerialServiceClient::CallSocket(uint32 magic, Callback1<TcpSocket&> cb) {
	if (!tcp.IsOpen())
		return false;
	
	auto& sock = tcp;
	int in_sz = 0;
	uint32 sent = 0, got = 0, got_magic = 0;
	
	SEND(magic);
	GET(got_magic);
	if (!got_magic) {
		LOG("SerialServiceClient::CallMem: error: magic not found on server");
		return false;
	}
	
	cb(tcp);
	
	return true;
}

bool SerialServiceClient::Init(String name) {
	
	TODO
	
}

void SerialServiceClient::Update() {
	
	TODO
	
}

void SerialServiceClient::Deinit() {
	
	TODO
	
}

	
#undef RECV
#undef GET_ERROR
#undef GET
#undef SEND

NAMESPACE_TOPSIDE_END
