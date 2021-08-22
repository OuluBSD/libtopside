#ifndef _SerialCore_Customer_h_
#define _SerialCore_Customer_h_

NAMESPACE_SERIAL_BEGIN


class CustomerAtom : public AtomBase {
	
public:
	RTTI_DECL1(CustomerAtom, AtomBase);
	using Atom = CustomerAtom;
	
};


NAMESPACE_SERIAL_END

#endif
