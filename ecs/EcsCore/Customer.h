#ifndef _EcsLib_Customer_h_
#define _EcsLib_Customer_h_

NAMESPACE_TOPSIDE_BEGIN


class CustomerComponent;


/*class GeneratorComponentBase : RTTIBase {
	
protected:
	RealtimeSourceConfig cfg;
	off32_gen gen;
	
public:
	RTTI_DECL0(GeneratorComponentBase)
	GeneratorComponentBase() : cfg(gen) {}
	
	
};*/


class CustomerExt : public ComponentExtBase {
	
public:
	RTTI_DECL1(CustomerExt, ComponentExtBase);
	using Ext = CustomerExt;
	using Component = CustomerComponent;
	
};

class CustomerComponent :
	public Component<CustomerComponent, ReceiptSink, OrderSource, CustomerExt>,
	RTTIBase
{
	Vector<Eon::Plan>		plans;
	Index<dword>			unfulfilled_offsets;
	int						max_unfulfilled = 5;
	
	
	
protected:
	friend class CustomerSystem;
	RealtimeSourceConfig cfg;
	off32_gen gen;
	
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
	using ComponentT = Component<CustomerComponent, ReceiptSink, OrderSource, CustomerExt>;
	RTTI_COMP1(CustomerComponent, ComponentT)
	COPY_PANIC(CustomerComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("loop.connected")
	COMP_MAKE_ACTION_END
	
	
	CustomerComponent();
	virtual void		Initialize() override;
	virtual void		Uninitialize() override;
	void				UpdateConfig(double dt);
	void				AddPlan(Eon::Plan& ep);
	void				Forward(FwdScope& fwd) override;
	void				ForwardExchange(FwdScope& fwd) override;
	
	
	// ReceiptSink
	Receipt&			GetValue(RcpCtx) override {return sink_value;}
	bool				ReadFrame() {TODO}
	bool				ProcessDeviceFrame() {TODO}
	
	// OrderSource
	OrderStream&		GetStream(OrdCtx) override {return src_stream;}
	
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
	
public:
	SYS_RTTI(CustomerSystem)
	SYS_CTOR(CustomerSystem);
	SYS_DEF_VISIT_(vis && customers)
	
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
