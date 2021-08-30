#ifndef _AtomLocal_Customer_h_
#define _AtomLocal_Customer_h_

NAMESPACE_SERIAL_BEGIN


class CustomerAtom :
	public Atom<CustomerAtom>
{
	
protected:
	friend class Loop;
	
	struct CustomerData {
		RealtimeSourceConfig	cfg;
		off32_gen				gen;
		Array<Script::Plan>		plans;
		Index<dword>			unfulfilled_offsets;
		int						max_unfulfilled = 5;
		
		CustomerData() : cfg(gen) {}
	};
	One<CustomerData>		customer;
	
	
public:
	using AtomT = Atom<CustomerAtom>;
	RTTI_DECL1(CustomerAtom, AtomT);
	COPY_PANIC(CustomerAtom)
	using Atom = CustomerAtom;
	
	
	static AtomTypeCls GetAtomType() {return ATOM0(CENTER_CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);}
	
	void AddPlan(Script::Plan& sp);
	void UpdateConfig(double dt);
	RealtimeSourceConfig& GetConfig() {ASSERT(customer); return customer->cfg;}
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	AtomTypeCls GetType() const override {return GetAtomType();}
	void CopyTo(AtomBase* atom) const override {TODO}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	void ClearSinkSource() override {TODO}
	void Forward(FwdScope& fwd) override {}
	void ForwardAtom(FwdScope& fwd) override;
	void ForwardExchange(FwdScope& fwd) override;
	
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("customer.test.single")
	ATOM_MAKE_ACTION_END
	
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::CUSTOMER_ATOM;}
	
};

using CustomerAtomRef = Ref<CustomerAtom, RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
