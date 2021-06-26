#ifndef _EcsLib_Customer_h_
#define _EcsLib_Customer_h_

NAMESPACE_ECS_BEGIN


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



#if 0
class CustomerComponent :
	public Component<CustomerComponent, CustomerExt>,
	RTTIBase
{
	Vector<Eon::Plan>		plans;
	Index<dword>			unfulfilled_offsets;
	int						max_unfulfilled = 5;
	
	
	
protected:
	friend class ExtSystem;
	RealtimeSourceConfig cfg;
	off32_gen gen;
	
protected:
	struct LocalSinkValue : public SimpleValue {
		
	};
	
	struct LocalSourceValue : public SimpleValue {
		void StorePacket(Packet& p) override {TODO}
		
	};
	
	struct LocalSourceStream : public SimpleStream {
		RTTI_DECL1(LocalSourceStream, SimpleStream)
		CustomerComponent& par;
		LocalSourceStream(CustomerComponent* par) :
			par(*par),
			SimpleStream(par->src_value) {}
	};
	
	LocalSinkValue			sink_value;
	LocalSourceValue		src_value;
	LocalSourceStream		src_stream;
	
public:
	using ComponentT = Component<CustomerComponent, CustomerExt>;
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
	Value&				GetValue() override {return sink_value;}
	bool				ReadFrame() {TODO}
	bool				ProcessDeviceFrame() {TODO}
	
	// OrderSource
	Stream&				GetStream() override {return src_stream;}
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_CUSTOMER;}
	static CompCls				GetDefaultCompCls() {
		CompCls c;
		c.sink = VD(CENTER,RECEIPT);
		c.side = VD(CENTER,ORDER);
		c.src = VD(CENTER,ORDER);
		return c;
	}
	
};

using CustomerComponentRef = RefT_Entity<CustomerComponent>;

#endif














NAMESPACE_ECS_END

#endif
