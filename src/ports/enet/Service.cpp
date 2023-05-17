#include "enet.h"


NAMESPACE_TOPSIDE_BEGIN



String GetHostAddress(const ENetAddress& addr) {
	char s[256];
	if (enet_address_get_host_ip(&addr, s, 256) == 0)
		return String(s) + ":" + IntStr(addr.port);
	return String("invalid");
}

String GetHostAddress(const ENetPeer* peer) {
	return peer ? GetHostAddress(peer->address) : String("invalid");
}




String EnetServerClient::GetHostAddress() const {
	return TS::GetHostAddress(addr);
}





GlobalEnet::~GlobalEnet() {
	Uninitialize();
}

void GlobalEnet::Initialize() {
	if (!initialized) {
		initialized = true;
		enet_initialize();
	}
}

void GlobalEnet::Uninitialize() {
	if (initialized) {
		enet_deinitialize();
		initialized = false;
	}
}





uint16 EnetServiceServer::port_arg;

EnetServiceServer::EnetServiceServer() {
	#ifdef flagVERBOSE
	SetVerbose();
	#endif
}

EnetServiceServer::~EnetServiceServer() {
	Close();
	StopThread();
}

bool EnetServiceServer::Listen(uint16 port) {
    address.host = ENET_HOST_ANY;
    // Bind the server to the given port
    address.port = port;
	
	if (server)
		Close();
	
	server = enet_host_create (&address  /* the address to bind the server host to */,
                              max_conns  /* allow up to X clients and/or outgoing connections */,
                               channels  /* allow up to X channels to be used */,
                                      0  /* assume any amount of incoming bandwidth */,
                                      0  /* assume any amount of outgoing bandwidth */);
	
	if (server == NULL)
		return false;
	
	return true;
}

void EnetServiceServer::Close() {
	if (server) {
		enet_host_destroy(server);
		server = 0;
	}
}

void EnetServiceServer::StartThread() {
	StopThread();
	
	ASSERT(server);
	if (!server) return;
	
	Thread::Start(THISBACK(ListenerHandler));
}

void EnetServiceServer::ListenerHandler() {
	flag.Start(1);
	
	ENetEvent event;
	while (server && flag.IsRunning()) {
		int timeout = this->timeout > 1 ? this->timeout : 10;
		
		int r = enet_host_service(
			server,
			&event,
			timeout);
		
		// error
		if (r < 0)
			break;
		
		if (r > 0)
			ClientHandler(event);
	}
	
	flag.DecreaseRunning();
}

void EnetServiceServer::StopThread() {
	flag.Stop();
}

EnetServerClient& EnetServiceServer::RealizeClient(const ENetAddress& addr) {
	for (EnetServerClient& c : clients) {
		if (memcmp(&c.addr, &addr, sizeof(ENetAddress)) == 0)
			return c;
	}
	
	EnetServerClient& c = clients.Add();
	c.addr = addr;
	return c;
}

void EnetServiceServer::RemoveClient(EnetServerClient& c) {
	for(int i = 0; i < clients.GetCount(); i++) {
		if (&clients[i] == &c) {
			clients.Remove(i);
			return;
		}
	}
}
	
void EnetServiceServer::ClientHandler(ENetEvent& e) {
	ENetPeer* peer = e.peer;
	
	if (verbose) {
		LOG("EnetServiceServer::ClientHandler: starting handling client " << GetHostAddress(peer));
	}
	
	if (!e.peer)
		return;
	
	
	switch (e.type) {
		case ENET_EVENT_TYPE_CONNECT: {
			EnetServerClient& c = RealizeClient(e.peer->address);
			if (verbose) {
				LOG("EnetServiceServer::ClientHandler: A new client connected from "
					<< GetHostAddress(e.peer -> address));
			}
			
			/* Store any relevant client information here. */
			e.peer->data = &c;
		}
        return;
		
    case ENET_EVENT_TYPE_RECEIVE: {
			if (e.packet->data) {
				EnetServerClient& c = *(EnetServerClient*)e.peer->data;
				
				if (verbose) {
					LOG("EnetServiceServer::ClientHandler: "
						"A packet of length " << (int)e.packet -> dataLength <<
						" containing " << HexString(e.packet -> data, e.packet -> dataLength) <<
						" was received from " << c.GetHostAddress() <<
						" on channel " << (int)e.channelID);
				}
				
				ReceiveHandler(e);
				
		        /* Clean up the packet now that we're done using it. */
		        enet_packet_destroy(e.packet);
			}
	    }
        return;
       
    case ENET_EVENT_TYPE_DISCONNECT:
        if (e.packet->data) {
			EnetServerClient& c = *(EnetServerClient*)e.peer->data;
            
			if (verbose) {
				LOG("EnetServiceServer::ClientHandler: "
					"disconnected " << c.GetHostAddress());
			}
			
	        /* Reset the peer's client information. */
	        e.peer->data = NULL;
            RemoveClient(c);
        }
		return;
        
	case ENET_EVENT_TYPE_NONE:
		return;
    }
	
}

void EnetServiceServer::ReceiveHandler(ENetEvent& e) {
	EnetServerClient& c = *(EnetServerClient*)e.peer->data;
	int got = 0, sent = 0;
	uint32 magic = 0, in_sz = 0, out_sz = 0;
	
	MemReadStream sin(e.packet->data, e.packet->dataLength);
	StringStream& sout = c.sout;
	sout.SetSize(0);
	
	#define RECV(x) \
		got = sin.Get(&x, sizeof(x));
	#define GET_ERROR(x) \
		if (got != sizeof(x)) { \
			LOG("EnetServiceServer::ClientHandler: error: expected " << (int)sizeof(x) << ", but got " << got); return;}
	#define GET(x) \
		RECV(x) \
		GET_ERROR(x)
	#define SEND(x) \
		sout.Put(&x, sizeof(x));
	
	RECV(magic);
	if (!magic) {
		return;
	}
	GET_ERROR(magic);
	
	
	// Keepalive magic
	c.last_seen = enet_time_get();
	if (magic == 1) {
		return;
	}
	
	// Find handler
	if (!c.handler || c.handler->magic != magic) {
		int i = handlers.Find(magic);
		if (i < 0) {
			LOG("EnetServiceServer::ClientHandler: error: could not find magic " << magic);
			magic = 0;
			SEND(magic);
			return;
		}
		c.handler = &handlers[i];
	}
	
	SEND(magic);
	
	if (verbose) {
		LOG("EnetServiceServer::ClientHandler: info: magic " << magic << ", h " << HexStr(&c));
	}
	
	HandlerBase& hb = *c.handler;
	String result;
	const void* data;
	int data_len;
	
	switch (hb.fn_type) {
		case FN_FIXED:
		case FN_SERIALIZED:
		case FN_STREAMED: {
			if (verbose) {LOG("EnetServiceServer::ClientHandler: info: stream enter");}
			hb.Call(sin, sout);
			if (verbose) {LOG("EnetServiceServer::ClientHandler: info: stream leave");}
			result = sout.GetResult();
			data = result.Begin();
			data_len = result.GetCount();
		}
	}
	
	
	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket* packet = enet_packet_create( data,
	                                         data_len,
	                                         ENET_PACKET_FLAG_RELIABLE);
	
	/* Send the packet to the peer over channel id 0. */
	enet_peer_send (e.peer, 0, packet);
	
	/* One could just use enet_host_service() instead. */
	enet_host_flush(server);
	
	#undef RECV
	#undef GET_ERROR
	#undef GET
	#undef SEND
}

bool EnetServiceServer::Init(String name) {
	GlobalEnet::Single().Initialize();
	
	if (!port && port_arg)
		port = port_arg;
	else
		port = 7776;
	
	if (!Listen(port)) {
		LOG("EnetServiceServer::Init: Could not listen port " << (int)EnetServiceServer::port_arg);
		return false;
	}
	
	StartThread();
	
	return true;
}

void EnetServiceServer::Update() {
	
}

void EnetServiceServer::Deinit() {
	Close();
	
	StopThread();
	
	GlobalEnet::Single().Uninitialize();
}





String EnetServiceClient::addr_arg;
uint16 EnetServiceClient::port_arg;


EnetServiceClient::EnetServiceClient() {
	#ifdef flagVERBOSE
	SetVerbose();
	#endif
}

EnetServiceClient::~EnetServiceClient() {
	Close();
}

bool EnetServiceClient::Connect(String addr, uint16 port) {
	Close();
	
	if (enet_address_set_host(&this->addr, addr.Begin()) < 0)
		return false;
	this->addr.port = port;
	
    uint32 channels = 2;
    
	client = enet_host_create (NULL /* create a client host */,
                1        /* only allow 1 outgoing connection */,
                channels /* allow up X channels to be used, 0 and 1 */,
                0        /* assume any amount of incoming bandwidth */,
                0        /* assume any amount of outgoing bandwidth */);

    if (client == NULL)
        return false;
    
    uint32 data = 0;
    server = enet_host_connect(client, &this->addr, channels, data);
    if (!server)
        return false;
    
    return true;
}

void EnetServiceClient::Close() {
	enet_host_destroy(client);
	client = 0;
}

#define RECV(x) \
	got = stream.Get(&x, sizeof(x));
#define GET_ERROR(x) \
	if (got != sizeof(x)) { \
		LOG("EnetServiceClient::CallMem: error: expected " << (int)sizeof(x) << ", but got " << got); stream.Close(); return false;}
#define GET(x) \
	RECV(x) \
	GET_ERROR(x)
#define SEND(x) \
	sent = stream.Put(&x, sizeof(x)); \
	if (sent != sizeof(x)) { \
		LOG("EnetServiceClient::CallMem: error: expected to send " << (int)sizeof(x) << ", but sent " << sent); stream.Close(); return false;}


bool EnetServiceClient::CallMem(uint32 magic, const void* out, int out_sz, void* in, int in_sz) {
	if (!server)
		return false;
	
	MemReadStream sin(in, in_sz);
	uint32 sent = 0, got = 0, got_magic = 0;
	
	SEND(magic);
	GET(got_magic);
	if (!got_magic) {
		LOG("EnetServiceClient::CallMem: error: magic not found on server");
		return false;
	}
	SEND(out_sz);
	SEND(in_sz);
	
	sent = stream.Put(out, out_sz);
	if (sent != out_sz) {
		LOG("EnetServiceClient::CallMem: error: expected to send " << out_sz << ", but sent " << sent);
		return false;
	}
	
	got = stream.Get(in, in_sz);
	if (got != in_sz) {
		LOG("EnetServiceClient::CallMem: error: expected to get " << in_sz << ", but got " << got);
		return false;
	}
	
	return true;
}

bool EnetServiceClient::CallMem(uint32 magic, const void* out, int out_sz, Vector<byte>& in) {
	
	TODO
	#if 0
	
	if (!tcp.IsOpen())
		return false;
	
	auto& stream = tcp;
	int in_sz = 0;
	uint32 sent = 0, got = 0, got_magic = 0;
	
	SEND(magic);
	GET(got_magic);
	if (!got_magic) {
		LOG("EnetServiceClient::CallMem: error: magic not found on server");
		return false;
	}
	SEND(out_sz);
	SEND(in_sz); // == 0
	
	sent = stream.Put(out, out_sz);
	if (sent != out_sz) {
		LOG("EnetServiceClient::CallMem: error: expected to send " << out_sz << ", but sent " << sent);
		return false;
	}
	
	GET(in_sz);
	in.SetCount(in_sz);
	got = stream.Get(in.Begin(), in_sz);
	if (got != in_sz) {
		LOG("EnetServiceClient::CallMem: error: expected to get " << in_sz << ", but got " << got);
		return false;
	}
	
	return true;
	#endif
}

bool EnetServiceClient::CallStream(uint32 magic, Callback1<Stream&> cb) {
	
	TODO
	#if 0
	
	if (!tcp.IsOpen())
		return false;
	
	auto& stream = tcp;
	int in_sz = 0;
	uint32 sent = 0, got = 0, got_magic = 0;
	
	SEND(magic);
	GET(got_magic);
	if (!got_magic) {
		LOG("EnetServiceClient::CallMem: error: magic not found on server");
		return false;
	}
	
	cb(tcp);
	
	return true;
	#endif
}

bool EnetServiceClient::Init(String name) {
	GlobalEnet::Single().Initialize();
	
	if (!port && port_arg)
		port = port_arg;
	else
		port = 7776;
	
	if (addrname.IsEmpty() && !addr_arg.IsEmpty())
		addrname = addr_arg;
	else
		addrname = "127.0.0.1";
	
	
	if (!Connect(addrname, port)) {
		LOG("EnetServiceClient::Init: error: could not connect to " << addrname << ":" << port);
		return false;
	}
	
	// Enet can't tell yet, if it has connected to the server
	if (verbose) {
		LOG("EnetServiceClient::Init: connecting to " << addrname << ":" << port);
	}
	
	ts.Reset();
	
	return true;
}

void EnetServiceClient::Update() {
	
	PeerHandler();
	
	if (!connected && ts.Seconds() >= timeout) {
		LOG("EnetServiceClient::Update: error: server did not respond");
		
		if (1) {
			LOG("EnetServiceClient::Update: closing daemon");
			base->SetNotRunning();
		}
	}
}

void EnetServiceClient::PeerHandler() {
	ENetEvent event;
	while (client) {
		int timeout = 0;
		
		int r = enet_host_service(
			client,
			&event,
			timeout);
		
		// error or no event
		if (r <= 0)
			break;
		
		if (r > 0)
			ServerHandler(event);
	}
	
}

void EnetServiceClient::Deinit() {
	Close();
	
	GlobalEnet::Single().Uninitialize();
}

void EnetServiceClient::ServerHandler(ENetEvent& e) {
	ENetPeer* peer = e.peer;
	
	if (verbose) {
		LOG("EnetServiceClient::ClientHandler: starting handling client " << GetHostAddress(peer));
	}
	
	if (!e.peer)
		return;
	
	
	switch (e.type) {
		case ENET_EVENT_TYPE_CONNECT:
			connected = true;
			break;
			
		case ENET_EVENT_TYPE_DISCONNECT:
			connected = false;
			ts.Reset();
			LOG("EnetServiceClient::ServerHandler: disconnected");
			base->SetNotRunning();
			break;
			
		default:
			TODO
	}
}

void EnetServiceClient::ReceiveHandler(ENetEvent& e) {
	
}



NAMESPACE_TOPSIDE_END
