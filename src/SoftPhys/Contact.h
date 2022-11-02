#ifndef _SoftPhys_Contact_h_
#define _SoftPhys_Contact_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Contact : Object {
	RTTI_DECL1(Contact, Object)
	using Object::Object;
	
	
	
	Contact() {}
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
};


}
NAMESPACE_TOPSIDE_END

#endif
