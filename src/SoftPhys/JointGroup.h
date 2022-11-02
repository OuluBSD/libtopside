#ifndef _SoftPhys_JointGroup_h_
#define _SoftPhys_JointGroup_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct JointGroup : Object {
	RTTI_DECL1(JointGroup, Object)
	using Object::Object;
	
	World* world = 0;
	Vector<Joint*> joints;
	
	
	JointGroup();
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
	void Detach();
	
};


}
NAMESPACE_TOPSIDE_END

#endif
