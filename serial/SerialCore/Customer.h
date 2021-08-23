#ifndef _SerialCore_Customer_h_
#define _SerialCore_Customer_h_

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
	InterfaceSourceRef GetSource() override {TODO}
	InterfaceSinkRef GetSink() override {TODO}
	void Forward(FwdScope& fwd) override {TODO}
	
};


NAMESPACE_SERIAL_END

#endif
