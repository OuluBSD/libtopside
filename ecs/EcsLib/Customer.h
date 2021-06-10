#ifndef _EcsLib_Customer_h_
#define _EcsLib_Customer_h_

NAMESPACE_TOPSIDE_BEGIN



class CustomerComponent :
	public Component<CustomerComponent>,
	public ReceiptSink,
	public OrderSource
{
	
public:
	VIS_COMP_1_1(Order, Receipt)
	RTTI_COMP2(CustomerComponent, ReceiptSink, OrderSource)
	COPY_PANIC(CustomerComponent)
	IFACE_GENERIC
	IFACE_CB(OrderSource)
	IFACE_CB(ReceiptSink)
	COMP_DEF_VISIT
	
	virtual void Initialize() override;
	virtual void Uninitialize() override;
	
	// Receipt
	ReceiptFormat		GetFormat(RcpCtx) override {TODO}
	Receipt&			GetValue(RcpCtx) override {TODO}
	
	// Order
	OrderStream&	GetStream(OrdCtx) override {TODO}
	void			BeginStream(OrdCtx) override {TODO}
	void			EndStream(OrdCtx) override {TODO}
	
};




PREFAB_BEGIN(Customer)
	CustomerComponent
PREFAB_END


NAMESPACE_TOPSIDE_END

#endif
