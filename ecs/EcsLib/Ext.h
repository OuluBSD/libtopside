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
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_TO_TRUE(cls.sink.GetActionName() + ".sink")
		COMP_MAKE_ACTION_TO_TRUE(cls.src.GetActionName() + ".src")
		COMP_MAKE_ACTION_TO_TRUE(cls.side.GetActionName() + ".side")
	COMP_MAKE_ACTION_END
	
	
	TypeCompCls GetType() const override {return type;}
	void SetType(const TypeCompCls& cls) override {type = cls; ValSink::iface = cls.sink; ValSource::iface = cls.src;}
	
	void VisitSource(RuntimeVisitor& vis) override {vis.VisitThis<ValSource>(this);}
	void VisitSink(RuntimeVisitor& vis) override {vis.VisitThis<ValSink>(this);}
	
private:
	struct LocalSinkValue : public SimpleBufferedValue {
		ExtComponent& par;
		
		LocalSinkValue(ExtComponent* par) : par(*par) {}
	};
	
	struct LocalSourceValue : public SimpleValue {
		void StorePacket(Packet& p) override {}
	};
	
	struct LocalSourceStream : public SimpleStream {
		ExtComponent& par;
		
		RTTI_DECL1(LocalSourceStream, SimpleStream)
		LocalSourceStream(ExtComponent* par) :
			par(*par),
			SimpleStream(par->src_value) {}
		
	};
	
	
	void ClearSinkSource() override {
		ValSink::ClearSink();
		ValSource::ClearSource();
	}
protected:
	friend class ExtSystem;
	
	One<ComponentExtBase>	ext;
	TypeCompCls				type;
	
	
	LocalSinkValue			sink_value;
	LocalSourceValue		src_value;
	LocalSourceStream		src_stream;
	
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
	
	// ComponentBase
	void					Initialize() override;
	void					Uninitialize() override;
	void					Forward(FwdScope& fwd) override;
	void					ForwardExchange(FwdScope& fwd) override;
	
	// ValSink
	Value&					GetValue() override {return sink_value;}
	
	// ReceiptSource
	Stream&					GetStream() override {return src_stream;}
	
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
