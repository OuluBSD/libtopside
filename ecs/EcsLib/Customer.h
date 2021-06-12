#ifndef _EcsLib_Customer_h_
#define _EcsLib_Customer_h_

NAMESPACE_TOPSIDE_BEGIN



class CustomerComponent :
	public Component<CustomerComponent>,
	public ReceiptSink,
	public OrderSource,
	public GeneratorComponentBase
{
	Vector<EonPlan> plans;
	
protected:
	friend struct LocalStream;
	
	struct LocalSinkValue : public SimpleBufferedReceipt {
		
	};
	
	struct LocalSourceValue : public SimpleBufferedOrder {
		
	};
	
	struct LocalSourceStream : public SimpleBufferedOrderStream {
		RTTI_DECL1(LocalSourceStream, SimpleBufferedOrderStream)
		CustomerComponent& par;
		LocalSourceStream(CustomerComponent* par) :
			par(*par),
			SimpleBufferedOrderStream(par->src_value) {}
		bool			IsOpen() const override {TODO}
		bool			Open(int fmt_idx) override {TODO}
		void			Close() override {par.src_value.ClearBuffer();}
		bool			IsEof() override {return false;}
		bool			ReadFrame() override {return par.ReadFrame();}
		bool			ProcessFrame() override {return par.ProcessDeviceFrame();}
		bool			ProcessOtherFrame() override {return false;}
		void			ClearPacketData() override {}
		bool			LoadFileAny(String path) override {TODO}
	};
	
	LocalSinkValue			sink_value;
	LocalSourceValue		src_value;
	LocalSourceStream		src_stream;
	
public:
	VIS_COMP_1_1(Order, Receipt)
	RTTI_COMP3(CustomerComponent, ReceiptSink, OrderSource, GeneratorComponentBase)
	COPY_PANIC(CustomerComponent)
	IFACE_GENERIC
	IFACE_CB(OrderSource)
	IFACE_CB(ReceiptSink)
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("loop.connected")
	COMP_MAKE_ACTION_END
	
	
	CustomerComponent();
	virtual void Initialize() override;
	virtual void Uninitialize() override;
	void CreateOrder(double dt);
	void AddPlan(EonPlan& ep);
	
	
	// ReceiptSink
	ReceiptFormat		GetFormat(RcpCtx) override {TODO}
	Receipt&			GetValue(RcpCtx) override {return sink_value;}
	void				Forward(FwdScope& fwd) override;
	void				ForwardExchange(FwdScope& fwd) override;
	bool				ReadFrame() {TODO}
	bool				ProcessDeviceFrame() {TODO}
	
	// OrderSource
	OrderStream&		GetStream(OrdCtx) override {return src_stream;}
	void				BeginStream(OrdCtx) override {}
	void				EndStream(OrdCtx) override {}
	
};

using CustomerComponentRef = RefT_Entity<CustomerComponent>;



class CustomerSystem :
	public System<CustomerSystem>
{
	LinkedList<CustomerComponentRef> customers;
	
	void Visit(RuntimeVisitor& vis) override {
		vis && customers;
	}
	
public:
	SYS_RTTI(CustomerSystem)
	SYS_CTOR(CustomerSystem);
	
	
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
protected:
	friend class CustomerComponent;
	
    void Add(CustomerComponentRef p);
    void Remove(CustomerComponentRef p);
	
};

using CustomerSystemRef = RefT_Machine<CustomerSystem>;




PREFAB_BEGIN(Customer)
	CustomerComponent
PREFAB_END


NAMESPACE_TOPSIDE_END

#endif
