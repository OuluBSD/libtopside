#ifndef _AtomLocal_Customer_h_
#define _AtomLocal_Customer_h_

#if HAVE_MANUAL_DBG_CLASSES

NAMESPACE_SERIAL_BEGIN


class CenterCustomer :
	public CustomerBaseT<CenterCustomer>
{
	
public:
	RTTI_DECL1(CenterCustomer, BaseT);
	COPY_PANIC(CenterCustomer)
	static AtomTypeCls GetAtomType() {return ATOM0(CENTER_CUSTOMER, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BaseT>(this);}
	AtomTypeCls GetType() const override {return GetAtomType();}
	
	
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.customer")
	ATOM_MAKE_ACTION_END
	
	
	
};

using CenterCustomerRef = Ref<CenterCustomer, RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
#endif
