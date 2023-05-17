#ifndef _Local_Network_h_
#define _Local_Network_h_

NAMESPACE_TOPSIDE_BEGIN


enum {
	NET_LATEST_BRIGHT_FRAME = 10100,
	NET_LATEST_DARK_FRAME,
	
	NET_SEND_FUSION_DATA = 10200
	
};

class SerialServiceBase : public DaemonService {
	
public:
	RTTI_DECL1(SerialServiceBase, DaemonService)
	
	typedef enum {
		FN_FIXED,
		FN_SERIALIZED,
		FN_STREAMED,
	} FnType;
	
	struct HandlerBase : RTTIBase {
		RTTI_DECL0(HandlerBase);
		virtual ~HandlerBase() {}
		
		uint32 magic = 0;
		int in_sz = 0;
		int out_sz = 0;
		FnType fn_type;
		
		virtual void Call(const Vector<byte>& in, Vector<byte>& out) {Panic("not implemented");}
		virtual void Call(Stream& in, Stream& out) {Panic("not implemented");}
	};
	
	template <class In, class Out> struct FixedHandlerT : HandlerBase {
		RTTI_DECL1(FixedHandlerT, HandlerBase);
		byte b_in[sizeof(In)];
		byte b_out[sizeof(Out)];
		
		Callback2<const In&, Out&> cb;
		
		void Call(const Vector<byte>& in, Vector<byte>& out) override {
			out.SetCount(sizeof(Out));
			const In* o_in = (const In*)(const byte*)in.Begin();
			Out* o_out = (Out*)(byte*)out.Begin();
			cb(*o_in, *o_out);
		}
		
		void Call(Stream& in, Stream& out) override {
			in.Get(b_in, sizeof(In));
			const In* o_in = (const In*)b_in;
			Out* o_out = (Out*)b_out;
			cb(*o_in, *o_out);
			out.Put(b_out, sizeof(Out));
		}
	};
	
	template <class In, class Out> struct SerializerHandlerT : HandlerBase {
		RTTI_DECL1(SerializerHandlerT, HandlerBase);
		
		Callback2<const In&, Out&> cb;
		One<In> tmp_in;
		One<Out> tmp_out;
		
		void Call(Stream& in, Stream& out) override {
			if (tmp_in.IsEmpty()) {
				tmp_in.Create();
				tmp_out.Create();
			}
			
			in % *tmp_in;
			cb(*tmp_in, *tmp_out);
			out % *tmp_out;
		}
	};
	
	struct StreamHandler : HandlerBase {
		RTTI_DECL1(StreamHandler, HandlerBase);
		
		Callback2<Stream&, Stream&> cb;
		
		void Call(Stream& in, Stream& out) override {
			cb(in, out);
		}
	};
	
	/*struct TcpSocketHandler : HandlerBase {
		RTTI_DECL1(TcpSocketHandler, HandlerBase);
		
		Callback1<TcpSocket&> cb;
		
		void Call(TcpSocket& out) override {
			cb(out);
		}
	};*/
	
protected:
	ArrayMap<uint32, HandlerBase> handlers;
	
	
	template <class Handler, class In, class Out, class Cb=Callback2<const In&, Out&>>
	bool AddReceiverT(uint32 magic, Cb cb, FnType fn_type) {
		int i = handlers.Find(magic);
		if (i >= 0) {
			Handler* h = CastPtr<Handler>(&handlers[i]);
			if (!h)
				return false;
			h->cb << cb;
			return true;
		}
		Handler* h = new Handler();
		h->cb = cb;
		h->magic = magic;
		h->in_sz = sizeof(In);
		h->out_sz = sizeof(Out);
		h->fn_type = fn_type;
		//ASSERT(h->in_sz && h->out_sz);
		handlers.Add(magic, h);
		return true;
	}
	
public:
	typedef SerialServiceBase CLASSNAME;
	SerialServiceBase();
	
	
	template <class In, class Out>
	bool AddFixed(uint32 magic, Callback2<const In&, Out&> cb) {
		return AddReceiverT<FixedHandlerT<In,Out>,In,Out>(magic, cb, FN_FIXED);
	}
	
	template <class In, class Out>
	bool AddSerializer(uint32 magic, Callback2<const In&, Out&> cb) {
		return AddReceiverT<SerializerHandlerT<In,Out>,In,Out>(magic, cb, FN_SERIALIZED);
	}
	
	bool AddStream(uint32 magic, Callback2<Stream&, Stream&> cb) {
		return AddReceiverT<StreamHandler,dword,dword,Callback2<Stream&,Stream&>>(magic, cb, FN_STREAMED);
	}
	
};


class SerialServiceServer : public SerialServiceBase {
	TcpSocket tcp;
	RunningFlag flag;
	int keepalive_limit = 10;
	
	void ClientHandler(TcpSocket* sock);
public:
	RTTI_DECL1(SerialServiceServer, SerialServiceBase)
	typedef SerialServiceServer CLASSNAME;
	SerialServiceServer();
	~SerialServiceServer();
	
	
	bool ListenTcp(uint16 port);
	void StartThread();
	void ListenerHandler();
	
	void CloseTcp();
	void StopThread();
	
	
	// DaemonService
	bool Init(String name) override;
	void Update() override;
	void Deinit() override;
	
};


class SerialServiceClient : public SerialServiceBase {
	TcpSocket tcp;
	
	
public:
	RTTI_DECL1(SerialServiceClient, SerialServiceBase)
	typedef SerialServiceClient CLASSNAME;
	SerialServiceClient();
	~SerialServiceClient();
	
	bool ConnectTcp(String addr, uint16 port);
	void CloseTcp();
	bool CallMem(uint32 magic, const void* out, int out_sz, void* in, int in_sz);
	bool CallMem(uint32 magic, const void* out, int out_sz, Vector<byte>& in);
	bool CallStream(uint32 magic, Callback2<Stream&, Stream&> cb);
	//bool CallSocket(uint32 magic, Callback1<TcpSocket&> cb);
	
	template <class In, class Out>
	bool Call(uint32 magic, const In& in, Event<const Out&> fn) {
		return CallMem(magic, (const void*)&in, sizeof(In), fn);
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
	
	bool IsOpen() const {return tcp.IsOpen();}
	
	
	// DaemonService
	bool Init(String name) override;
	void Update() override;
	void Deinit() override;
	
};






class TcpSocketReadStream : public Stream {
	TcpSocket* sock = 0;
	
	void  _Put(int w) override;
	int   _Term() override;
	int   _Get() override;
	void  _Put(const void *data, dword size) override;
	dword _Get(void *data, dword size) override;
	
	void  Seek(int64 pos) override;
	int64 GetSize() const override;
	void  SetSize(int64 size) override;
	void  Flush() override;
	void  Close() override;
	bool  IsOpen() const override;
	
public:
	TcpSocketReadStream(TcpSocket& s) : sock(&s) {}
	
};

class TcpSocketWriteStream : public Stream {
	TcpSocket* sock = 0;
	
	void  _Put(int w) override;
	int   _Term() override;
	int   _Get() override;
	void  _Put(const void *data, dword size) override;
	dword _Get(void *data, dword size) override;
	
	void  Seek(int64 pos) override;
	int64 GetSize() const override;
	void  SetSize(int64 size) override;
	void  Flush() override;
	void  Close() override;
	bool  IsOpen() const override;
	
public:
	TcpSocketWriteStream(TcpSocket& s) : sock(&s) {}
	
};




NAMESPACE_TOPSIDE_END

#endif
