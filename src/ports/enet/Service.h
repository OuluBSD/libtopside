#ifndef _ports_enet_Service_h_
#define _ports_enet_Service_h_

NAMESPACE_TOPSIDE_BEGIN


class GlobalEnet {
	bool initialized = false;
	
	
public:
	~GlobalEnet();
	void Initialize();
	void Uninitialize();
	
	static GlobalEnet& Single() {static GlobalEnet e; return e;}
	
};


struct EnetServerClient {
	ENetAddress addr;
	uint16 port;
	uint32 last_seen = 0;
	SerialServiceBase::HandlerBase* handler = 0;
	
	// Temp vars
	StringStream sout;
	
	String GetHostAddress() const;
	
};


class EnetServiceServer : public SerialServiceBase {
    ENetAddress address;
    ENetHost* server = 0;
	RunningFlag flag;
	int keepalive_limit = 10;
	
	int port = 0;
	int max_conns = 32;
	int channels = 2;
	int timeout = 10; // milliseconds to wait for a event
	bool verbose = false;
	
	Array<EnetServerClient> clients;
	
	void ClientHandler(ENetEvent& e);
	void ReceiveHandler(ENetEvent& e);
	
	EnetServerClient& RealizeClient(const ENetAddress& addr);
	void RemoveClient(EnetServerClient& c);
	
public:
	RTTI_DECL1(EnetServiceServer, SerialServiceBase)
	typedef EnetServiceServer CLASSNAME;
	EnetServiceServer();
	~EnetServiceServer();
	
	void SetPort(int i) {port = i;}
	void SetMaxConnections(int i) {max_conns = i;}
	void SetChannels(int i) {channels = i;}
	void SetTimeout(int i) {timeout = i;}
	void SetVerbose(bool b=true) {verbose = b;}
	
	bool Listen(uint16 port);
	void StartThread();
	void ListenerHandler();
	
	void Close();
	void StopThread();
	
	
	// DaemonService
	bool Init(String name) override;
	void Update() override;
	void Deinit() override;
	
	
	static uint16 port_arg;
};


class EnetServiceClient : public SerialServiceBase {
	ENetHost* client = 0;
	ENetPeer* server = 0;
	ENetAddress addr;
	
	double timeout = 3.000;
	int port = 0;
	String addrname;
	bool verbose = false;
	
	TimeStop ts;
	bool connected = false;
	
public:
	RTTI_DECL1(EnetServiceClient, SerialServiceBase)
	typedef EnetServiceClient CLASSNAME;
	EnetServiceClient();
	~EnetServiceClient();
	
	void SetAddress(String s) {addrname = s;}
	void SetPort(int i) {port = i;}
	void SetTimeout(int i) {timeout = i;}
	void SetVerbose(bool b=true) {verbose = b;}
	
	bool Connect(String addr, uint16 port);
	void Close();
	bool CallMem(uint32 magic, const void* out, int out_sz, void* in, int in_sz);
	bool CallMem(uint32 magic, const void* out, int out_sz, Vector<byte>& in);
	bool CallStream(uint32 magic, Callback1<Stream&> cb);
	
	template <class In, class Out>
	bool Call(uint32 magic, const In& in, Out& out) {
		return CallMem(magic, (const void*)&in, sizeof(In), (void*)&out, sizeof(Out));
	}
	
	template <class In, class Out>
	bool CallSerialized(uint32 magic, In& in, Out& out) {
		StringStream ss;
		ss.SetStoring();
		ss % in;
		String in_data = ss.GetResult();
		thread_local static Vector<byte> out_data;
		out_data.SetCount(0);
		if (!CallMem(magic, (const void*)in_data.Begin(), in_data.GetCount(), out_data))
			return false;
		MemReadStream ms(out_data.Begin(), out_data.GetCount());
		//ms.SetLoading();
		ms % out;
		return true;
	}
	
	bool IsOpen() const {return server != 0;}
	
	
	// DaemonService
	bool Init(String name) override;
	void Update() override;
	void Deinit() override;
	
	void PeerHandler();
	void ServerHandler(ENetEvent& e);
	void ReceiveHandler(ENetEvent& e);
	
	static String addr_arg;
	static uint16 port_arg;
	
};



NAMESPACE_TOPSIDE_END


#endif
