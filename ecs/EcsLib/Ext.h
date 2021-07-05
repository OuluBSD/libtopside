#ifndef _EcsLib_Ext_h_
#define _EcsLib_Ext_h_


NAMESPACE_ECS_BEGIN


class ExtSystem;
using ExtSystemRef = RefT_Machine<ExtSystem>;



class ExtComponent :
	public Component<ExtComponent>,
	public ValSink,
	public ValSource
{
	
public:
	RTTI_DECL3(ExtComponent, Component<ExtComponent>, ValSink, ValSource)
	void Visit(RuntimeVisitor& vis) override {
		vis.VisitThis<ValSink>(this);
		vis.VisitThis<ValSource>(this);
		if (ext) vis % *ext;
		vis & cust_sys;
		vis & side_in_conn & side_out_conn;
	}
	COPY_PANIC(ExtComponent)
	IFACE_GENERIC
	COMP_MAKE_ACTION_BEGIN {
		if (cls.side.vd.val == ValCls::ORDER) {
			COMP_MAKE_ACTION_FALSE_TO_TRUE("loop.connected")
		}
		else if (cls.sub == SubCompCls::INPUT) {
			COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.src.GetActionName() + ".src")
		}
		else if (cls.sub == SubCompCls::OUTPUT) {
			COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.sink.GetActionName() + ".sink")
		}
		else if (cls.sub == SubCompCls::SIDE_INPUT) {
			COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.src.GetActionName() + ".side.in")
		}
		else if (cls.sub == SubCompCls::SIDE_OUTPUT) {
			COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.sink.GetActionName() + ".side.out")
		}
		else if (cls.sub == SubCompCls::CONVERTER) {
			COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.sink.GetActionName() + ".convert")
		}
		else {
			//COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.side.GetActionName() + ".side")
		}
	} COMP_MAKE_ACTION_END
	
	
	TypeCompCls GetType() const override {return type;}
	void SetType(const TypeCompCls& cls) override;
	
	void VisitSource(RuntimeVisitor& vis) override {vis.VisitThis<ValSource>(this);}
	void VisitSink(RuntimeVisitor& vis) override {vis.VisitThis<ValSink>(this);}
	
	void OnLink(ExchangeSourceProviderRef src, CookieRef src_c, CookieRef sink_c) override;
	
private:
	struct LocalBufferedValue : public SimpleBufferedValue {
		ExtComponent& par;
		
		LocalBufferedValue(ExtComponent* par) : par(*par) {}
	};
	
	struct LocalValue : public SimpleValue {
		ExtComponent& par;
		
		LocalValue(ExtComponent* par) : par(*par) {}
	};
	
	struct LocalBufferedStream : public SimpleBufferedStream {
		ExtComponent& par;
		
		RTTI_DECL1(LocalBufferedStream, SimpleBufferedStream)
		LocalBufferedStream(ExtComponent* par, SimpleBufferedValue& value) :
			par(*par),
			SimpleBufferedStream(value) {}
		
		bool	IsOpen() const override {TODO}
		bool	Open(int fmt_idx) override {TODO}
		void	Close() override {TODO}
		bool	IsEof() override {TODO}
		bool	ReadFrame() override {TODO}
		bool	ProcessFrame() override {TODO}
		bool	ProcessOtherFrame() override {TODO}
		void	ClearPacketData() override {TODO}
	};
	
	struct LocalStream : public SimpleStream {
		ExtComponent& par;
		
		RTTI_DECL1(LocalStream, SimpleStream)
		LocalStream(ExtComponent* par, SimpleValue& value) :
			par(*par),
			SimpleStream(value) {}
		
	};
	
	struct BufferedInput {
		LocalBufferedValue value;
		BufferedInput(ExtComponent* par) : value(par) {}
		~BufferedInput() {value.ClearBuffer();}
	};
	struct Input {
		LocalValue value;
		Input(ExtComponent* par) : value(par) {}
	};
	struct BufferedOutput {
		LocalBufferedValue value;
		LocalBufferedStream stream;
		BufferedOutput(ExtComponent* par) : value(par), stream(par, value) {}
		~BufferedOutput() {value.ClearBuffer();}
	};
	struct Output {
		LocalValue value;
		LocalStream stream;
		Output(ExtComponent* par) : value(par), stream(par, value) {}
	};
	
	void ClearSinkSource() override {
		ValSink::ClearSink();
		ValSource::ClearSource();
	}
protected:
	friend class ExtSystem;
	
	One<ComponentExtBase>	ext;
	TypeCompCls				type;
	
	One<Input>				sink;
	One<BufferedInput>		sink_buf;
	One<Output>				src;
	One<BufferedOutput>		src_buf;
	
	int						side_in = -1, side_out = -1;
	ExtComponentRef			side_in_conn, side_out_conn;
	One<Input>				side_sink;
	One<BufferedInput>		side_sink_buf;
	
	Mutex					lock;
	LinkedList<Packet>		consumed_packets;
	PacketConsumer			consumer;
	ExtSystemRef			cust_sys;
	
	RealtimeSourceConfig*	cfg = 0;
	int						packets_forwarded = 0;
	
	struct CustomerData {
		RealtimeSourceConfig	cfg;
		off32_gen				gen;
		Vector<Eon::Plan>		plans;
		Index<dword>			unfulfilled_offsets;
		int						max_unfulfilled = 5;
		
		CustomerData() : cfg(gen) {}
	};
	One<CustomerData>		customer;
	
	
	void					ForwardCustomer(FwdScope& fwd);
	void					ForwardInput(FwdScope& fwd);
	void					ForwardOutput(FwdScope& fwd);
	void					ForwardSideInput(FwdScope& fwd);
	void					ForwardSideOutput(FwdScope& fwd);
	void					ForwardConsumed(FwdScope& fwd);
	void					ForwardInputBuffer(FwdScope& fwd, PacketBuffer& sink_buf);
	
	int GetSideIn() override {return side_in;}
	int GetSideOut() override {return side_out;}
	void SetSideIn(int i) override {ASSERT(side_in < 0); side_in = i;}
	void SetSideOut(int i) override {ASSERT(side_out < 0); side_out = i;}
	bool LinkSideIn(ComponentBaseRef in) override;
	bool LinkSideOut(ComponentBaseRef out) override;
	
public:
	ExtComponent();
	~ExtComponent();
	
	void					UpdateConfig(double dt);
	bool					SetExtension(ComponentExtBase* c) override;
	void					ClearExtension() override;
	ComponentExtBaseRef		GetExtension() override;
	InterfaceSourceRef		GetSource() override;
	InterfaceSinkRef		GetSink() override;
	void					AddPlan(Eon::Plan& ep);
	RealtimeSourceConfig&	GetConfig() {ASSERT(cfg); return *cfg;}
	bool					ForwardMem(void* mem, size_t mem_size);
	
	// ComponentBase
	void					Initialize() override;
	void					Uninitialize() override;
	void					Forward(FwdScope& fwd) override;
	void					ForwardExchange(FwdScope& fwd) override;
	
	// ValSink
	Value&					GetValue() override  {return sink.IsEmpty() ? (Value&)sink_buf->value : (Value&)sink->value;}
	Value&					GetSinkValue()       {return sink.IsEmpty() ? (Value&)sink_buf->value : (Value&)sink->value;}
	
	// ReceiptSource
	Stream&					GetStream() override {return src.IsEmpty() ? (Stream&)src_buf->stream : (Stream&)src->stream;}
	Value&					GetSourceValue()     {return src.IsEmpty() ? (Value&)src_buf->value : (Value&)src->value;}
	
	// Side-connection
	Value&					GetSideSinkValue()		{return side_sink.IsEmpty() ? (Value&)side_sink_buf->value : (Value&)side_sink->value;}
	
	
	
	Callback2<ComponentExtBase&, Packet&>	WhenEnterStorePacket;
	Callback1<Packet&>						WhenEnterCreatedEmptyPacket;
	
	Callback1<Packet&>						WhenLeaveStorePacket;
	Callback								WhenLeaveCreatedEmptyPacket;
	
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_EXT;}
	
};



class ExtSystem :
	public System<ExtSystem>
{
	struct Once {
		PacketForwarder*		fwd;
		RealtimeSourceConfig*	cfg;
	};
	LinkedList<Once> once_cbs;
	LinkedList<ExtComponentRef> customers;
	Mutex lock;
	
public:
	SYS_RTTI(ExtSystem)
	SYS_CTOR(ExtSystem);
	SYS_DEF_VISIT_(vis && customers)
	
	void AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg);
	
	
	Callback1<PacketForwarder*>				WhenEnterOnceForward;
	Callback1<ExtComponent*>				WhenEnterExtComponentForward;
	Callback1<FwdScope&>					WhenEnterFwdScopeForward;
	
	Callback								WhenLeaveOnceForward;
	Callback								WhenLeaveExtComponentForward;
	Callback								WhenLeaveFwdScopeForward;
	
	
	static inline Callback& WhenUninit() {static Callback cb; return cb;}
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::SYS_EXT;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
protected:
	friend class ExtComponent;
	
    void Add(ExtComponentRef p);
    void Remove(ExtComponentRef p);
	
	
};


NAMESPACE_ECS_END

#endif
