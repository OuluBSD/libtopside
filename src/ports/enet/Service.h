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
	ENetPeer* peer = 0;
	uint16 port;
	uint32 last_seen = 0;
	SerialServiceBase::HandlerBase* handler = 0;
	
	// Temp vars
	WriteEther sout;
	
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
	static bool verbose;
	
	Array<EnetServerClient> clients;
	
	void ClientHandler(ENetEvent& e);
	void ReceiveHandler(ENetEvent& e);
	
	EnetServerClient& RealizeClient(const ENetAddress& addr);
	void RemoveClient(EnetServerClient& c);
	EnetServerClient* FindClientByPeer(ENetPeer* peer);
	
public:
	RTTI_DECL1(EnetServiceServer, SerialServiceBase)
	typedef EnetServiceServer CLASSNAME;
	EnetServiceServer();
	~EnetServiceServer();
	
	void SetPort(int i) {port = i;}
	void SetMaxConnections(int i) {max_conns = i;}
	void SetChannels(int i) {channels = i;}
	void SetTimeout(int i) {timeout = i;}
	
	bool Listen(uint16 port);
	void StartThread();
	void ListenerHandler();
	
	void Close();
	void StopThread();
	
	
	// DaemonService
	bool Init(String name) override;
	void Update() override;
	void Deinit() override;
	
	
	static void SetVerbose(bool b=true) {verbose = b;}
	static uint16 port_arg;
};


class EnetServiceClient : public SerialServiceBase {
	ENetHost* client = 0;
	ENetPeer* server = 0;
	ENetAddress addr;
	
	double timeout = 3.000;
	double dconn_timeout = 1.0;
	bool wait_dconn = false;
	int port = 0;
	String addrname;
	
	TimeStop ts;
	bool connected = false;
	
public:
	struct CallBase {
		virtual ~CallBase() {}
		dword id;
		dword time;
		virtual void Execute(const void* data, int data_len) = 0;
	};
	
	template <class T>
	struct CallT : CallBase {
		T* out = 0;
		Event<> cb;
		void Execute(const void* data, int data_len) override {
			*out = *(const T*)data;
			cb();
		}
	};
	
	template <class T>
	struct CallSerializedT : CallBase {
		T* out = 0;
		Event<> cb;
		void Execute(const void* data, int data_len) override {
			ReadEther s(data, data_len);
			Etherize(s, *out);
			cb();
		}
	};
	
	template <class T>
	struct CallEventT : CallBase {
		Event<const T&> cb;
		void Execute(const void* data, int data_len) override {
			cb(*(const T*)data);
		}
	};
	
	template <class T>
	struct CallEventSerializedT : CallBase {
		Event<const T&> cb;
		void Execute(const void* data, int data_len) override {
			ReadEther s(data, data_len);
			T o;
			s % o;
			cb(o);
		}
	};
	
	LinkedMap<dword, One<CallBase>> calls;
	dword call_counter = 0;
	RWMutex lock;
	
public:
	RTTI_DECL1(EnetServiceClient, SerialServiceBase)
	typedef EnetServiceClient CLASSNAME;
	EnetServiceClient();
	~EnetServiceClient();
	
	void SetAddress(String s) {addrname = s;}
	void SetPort(int i) {port = i;}
	void SetTimeout(double sec) {timeout = sec;}
	void SetDisconnectionTimeout(double sec) {dconn_timeout = sec;}
	
	bool Connect(String addr, uint16 port);
	void Close();
	bool CallMem(uint32 magic, const void* out, int out_sz, int in_sz, CallBase* call);
	bool CallStream(uint32 magic, Callback1<Stream&> cb);
	bool IsConnected() const {return connected;}
	
	template <class Out, class In>
	bool CallEvent(uint32 magic, const In& in, Event<const Out&> out) {
		CallEventT<Out>* cb = new CallEventT<Out>;
		cb->cb = out;
		return CallMem(magic, (const void*)&in, sizeof(In), sizeof(Out), cb);
	}
	
	template <class Out, class In>
	bool CallEventSerialized(uint32 magic, const In& in, Event<const Out&> out) {
		CallEventSerializedT<Out>* cb = new CallEventSerializedT<Out>;
		cb->cb = out;
		WriteEther ss;
		ss % const_cast<In&>(in);
		String data = ss.GetResult();
		return CallMem(magic, data.Begin(), data.GetCount(), 0, cb);
	}
	
	template <class Out, class In>
	bool Call(uint32 magic, const In& in, Out& out, Event<> user_cb) {
		CallT<Out>* cb = new CallT<Out>;
		cb->cb = user_cb;
		cb->out = &out;
		return CallMem(magic, (const void*)&in, sizeof(In), sizeof(Out), cb);
	}
	
	template <class Out, class In>
	bool CallSerialized(uint32 magic, In& in, Out& out, Event<> user_cb) {
		CallSerializedT<Out>* cb = new CallSerializedT<Out>;
		cb->cb = user_cb;
		cb->out = &out;
		WriteEther ss;
		ss.SetStoring();
		ss % in;
		String in_data = ss.GetResult();
		return CallMem(magic, (const void*)in_data.Begin(), in_data.GetCount(), 0, cb);
	}
	
	bool IsOpen() const {return server != 0;}
	
	
	// DaemonService
	bool Init(String name) override;
	void Update() override;
	void Deinit() override;
	
	void PeerHandler();
	void ServerHandler(ENetEvent& e);
	void ReceiveHandler(ENetEvent& e);
	
	static void SetVerbose(bool b=true) {verbose = b;}
	static String addr_arg;
	static uint16 port_arg;
	static bool verbose;
	static bool close_daemon_on_fail;
	
};



NAMESPACE_TOPSIDE_END


#endif
