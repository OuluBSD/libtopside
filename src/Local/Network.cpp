#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN



SerialServiceBase::SerialServiceBase() {
	
}

/*bool SerialServiceBase::AddTcpSocket(uint32 magic, Callback1<TcpSocket&> cb) {
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
*/


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
		
		GET(in_sz);
		if (in_sz > 10000000) {
			LOG("SerialServiceServer::ClientHandler: error: too large input packet: " << in_sz);
			break;
		}
		
		GET(out_sz);
		
		
		in.SetCount(in_sz);
		got = sock.Get(in.Begin(), in.GetCount());
		if (got != in_sz) {
			LOG("SerialServiceServer::ClientHandler: error: expected " << in_sz << ", but got " << got);
			break;
		}
		
		switch (hb.fn_type) {
			case FN_FIXED: {
				if (out_sz != hb.out_sz) {
					LOG("SerialServiceServer::ClientHandler: error: unexpected output size: " << out_sz << " (expected " << hb.out_sz << ")");
					break;
				}
				out.SetCount(hb.out_sz);
				hb.Call(in, out);
				sent = sock.Put(out.Begin(), out.GetCount());
				
				if (sent != out_sz) {
					LOG("SerialServiceServer::ClientHandler: error: couldn't send full structure (" << sent << " < " << hb.out_sz << ")");
					break;
				}
			}
			
			case FN_SERIALIZED:
			case FN_STREAMED: {
				if (out_sz != 0) {
					LOG("SerialServiceServer::ClientHandler: error: unexpected output size: " << out_sz);
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
				
				if (sent != result.GetCount()) {
					LOG("SerialServiceServer::ClientHandler: error: couldn't send full memory (" << sent << " < " << result.GetCount() << ")");
					break;
				}
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

bool SerialServiceClient::CallStream(uint32 magic, Callback2<Stream&, Stream&> cb) {
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
	
	TODO //cb(tcp);
	
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






void  TcpSocketReadStream::_Put(int w) {
	ASSERT_(0, "This stream is for reading only");
}

int   TcpSocketReadStream::_Term() {
	return 0;
}

int   TcpSocketReadStream::_Get() {
	byte b;
	sock->Get(&b, 1);
	return b;
}

void  TcpSocketReadStream::_Put(const void *data, dword size) {
	ASSERT_(0, "This stream is for reading only");
}

dword TcpSocketReadStream::_Get(void *data, dword size) {
	return sock->Get(data, size);
}

void  TcpSocketReadStream::Seek(int64 pos) {
	
}

int64 TcpSocketReadStream::GetSize() const {
	return 0;
}

void  TcpSocketReadStream::SetSize(int64 size) {
	ASSERT_(0, "This stream is for reading only");
}

void  TcpSocketReadStream::Flush() {
	ASSERT_(0, "This stream is for reading only");
}

void  TcpSocketReadStream::Close() {
	//sock->Close();
}

bool  TcpSocketReadStream::IsOpen() const {
	return sock->IsOpen();
}




void  TcpSocketWriteStream::_Put(int w) {
	char c = w;
	sock->Put(&c, 1);
}

int   TcpSocketWriteStream::_Term() {
	ASSERT_(0, "This stream is for writing only");
	return 0;
}

int   TcpSocketWriteStream::_Get() {
	ASSERT_(0, "This stream is for writing only");
	return 0;
}

void  TcpSocketWriteStream::_Put(const void *data, dword size) {
	sock->Put(data, size);
}

dword TcpSocketWriteStream::_Get(void *data, dword size) {
	ASSERT_(0, "This stream is for writing only");
	return 0;
}

void  TcpSocketWriteStream::Seek(int64 pos) {
	ASSERT_(0, "This stream is for writing only");
}

int64 TcpSocketWriteStream::GetSize() const {
	ASSERT_(0, "This stream is for writing only");
	return 0;
}

void  TcpSocketWriteStream::SetSize(int64 size) {
	
}

void  TcpSocketWriteStream::Flush() {
	
}

void  TcpSocketWriteStream::Close() {
	//sock->Close();
}

bool  TcpSocketWriteStream::IsOpen() const {
	return sock->IsOpen();
}

	
NAMESPACE_TOPSIDE_END
