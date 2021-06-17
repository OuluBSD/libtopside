#ifndef _EcsLib_Customer_h_
#define _EcsLib_Customer_h_

NAMESPACE_TOPSIDE_BEGIN



class CustomerComponent :
	public Component<CustomerComponent, ReceiptSink, OrderSource>,
	public GeneratorComponentBase
{
	Vector<EonPlan>		plans;
	Index<dword>		unfulfilled_offsets;
	int					max_unfulfilled = 5;
	
protected:
	struct LocalSinkValue : public SimpleReceipt {
		void StorePacket(ReceiptPacket& p) override {TODO}
		
	};
	
	struct LocalSourceValue : public SimpleOrder {
		void StorePacket(OrderPacket& p) override {TODO}
		
	};
	
	struct LocalSourceStream : public SimpleOrderStream {
		RTTI_DECL1(LocalSourceStream, SimpleOrderStream)
		CustomerComponent& par;
		LocalSourceStream(CustomerComponent* par) :
			par(*par),
			SimpleOrderStream(par->src_value) {}
	};
	
	LocalSinkValue			sink_value;
	LocalSourceValue		src_value;
	LocalSourceStream		src_stream;
	
public:
	using ComponentT = Component<CustomerComponent, ReceiptSink, OrderSource>;
	RTTI_COMP1(CustomerComponent, GeneratorComponentBase)
	COPY_PANIC(CustomerComponent)
	IFACE_GENERIC
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
	struct Once {
		PacketForwarder*		fwd;
		RealtimeSourceConfig*	cfg;
	};
	LinkedList<Once> once_cbs;
	LinkedList<CustomerComponentRef> customers;
	Mutex lock;
	
	void Visit(RuntimeVisitor& vis) override {
		vis && customers;
	}
	
public:
	SYS_RTTI(CustomerSystem)
	SYS_CTOR(CustomerSystem);
	
	
	void AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg);
	
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
