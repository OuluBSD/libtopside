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
		else {
			COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.side.GetActionName() + ".side")
		}
	} COMP_MAKE_ACTION_END
	
	
	TypeCompCls GetType() const override {return type;}
	void SetType(const TypeCompCls& cls) override;
	
	void VisitSource(RuntimeVisitor& vis) override {vis.VisitThis<ValSource>(this);}
	void VisitSink(RuntimeVisitor& vis) override {vis.VisitThis<ValSink>(this);}
	
private:
	struct LocalBufferedValue : public SimpleBufferedValue {
		ExtComponent& par;
		
		LocalBufferedValue(ExtComponent* par) : par(*par) {}
	};
	
	struct LocalValue : public SimpleValue {
		ExtComponent& par;
		
		LocalValue(ExtComponent* par) : par(*par) {}
		void StorePacket(Packet& p) override {}
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
	};
	struct Input {
		LocalValue value;
		Input(ExtComponent* par) : value(par) {}
	};
	struct BufferedOutput {
		LocalBufferedValue value;
		LocalBufferedStream stream;
		BufferedOutput(ExtComponent* par) : value(par), stream(par, value) {}
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
	
	Mutex					lock;
	LinkedList<Packet>		consumed_packets;
	PacketConsumer			consumer;
	ExtSystemRef			cust_sys;
	
	
	struct CustomerData {
		RealtimeSourceConfig	cfg;
		off32_gen				gen;
		Vector<Eon::Plan>		plans;
		Index<dword>			unfulfilled_offsets;
		int						max_unfulfilled = 5;
		
		CustomerData() : cfg(gen) {}
	};
	One<CustomerData>		customer;
	
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
	
	// ComponentBase
	void					Initialize() override;
	void					Uninitialize() override;
	void					Forward(FwdScope& fwd) override;
	void					ForwardExchange(FwdScope& fwd) override;
	
	// ValSink
	Value&					GetValue() override {return sink.IsEmpty() ? (Value&)sink_buf->value : (Value&)sink->value;}
	
	// ReceiptSource
	Stream&					GetStream() override {return src.IsEmpty() ? (Stream&)src_buf->stream : (Stream&)src->stream;}
	Value&					GetSourceValue() {return src.IsEmpty() ? (Value&)src_buf->value : (Value&)src->value;}
	
	static EcsTypeCls::Type GetEcsType() {return EcsTypeCls::COMP_EXT;}
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
