#ifndef _SoftPhys_Feedback_h_
#define _SoftPhys_Feedback_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Feedback : Object {
	RTTI_DECL1(Feedback, Object)
	using Object::Object;
	
	
	Feedback() {}
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
};


}
NAMESPACE_TOPSIDE_END

#endif
