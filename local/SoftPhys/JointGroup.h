#ifndef _SoftPhys_JointGroup_h_
#define _SoftPhys_JointGroup_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct JointGroup : Object {
	using Object::Object;
	
	
	
	JointGroup();
	
	void Detach();
	
};


}
NAMESPACE_TOPSIDE_END

#endif
