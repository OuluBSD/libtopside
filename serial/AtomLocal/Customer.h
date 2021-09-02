#ifndef _AtomLocal_Customer_h_
#define _AtomLocal_Customer_h_

#if HAVE_MANUAL_DBG_CLASSES

NAMESPACE_SERIAL_BEGIN


class CustomerAtom :
	public AtomReceiptSink<CustomerAtom>
{
	
public:
	RTTI_DECL1(CustomerAtom, BaseT);
	COPY_PANIC(CustomerAtom)
	static AtomTypeCls GetAtomType() {return ATOM0(CENTER_CUSTOMER, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BaseT>(this);}
	AtomTypeCls GetType() const override {return GetAtomType();}
	
	
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("customer.test.single")
	ATOM_MAKE_ACTION_END
	
	
	
};

using CustomerAtomRef = Ref<CustomerAtom, RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
#endif
