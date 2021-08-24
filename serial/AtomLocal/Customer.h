#ifndef _AtomLocal_Customer_h_
#define _AtomLocal_Customer_h_

NAMESPACE_SERIAL_BEGIN


class CustomerAtom : public AtomBase {
	
public:
	RTTI_DECL1(CustomerAtom, AtomBase);
	using Atom = CustomerAtom;
	
	
	static AtomTypeCls GetAtomType() {return ATOM0(CENTER_CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);}
	
	AtomTypeCls GetType() const override {return GetAtomType();}
	
	void CopyTo(AtomBase* atom) const override {TODO}
	void Visit(RuntimeVisitor& vis) override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	void ClearSinkSource() override {TODO}
	void Forward(FwdScope& fwd) override {TODO}
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("customer.test.single")
	ATOM_MAKE_ACTION_END
	
};


NAMESPACE_SERIAL_END

#endif
