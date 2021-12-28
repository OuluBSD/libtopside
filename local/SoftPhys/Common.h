#ifndef _SoftPhys_Common_h_
#define _SoftPhys_Common_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Object {
	bool inited = false;
	
	
	Object() {}
	Object(const Nuller& n) {}
	void Create() {ASSERT(!inited); inited = true;}
	operator bool() const {return inited;}
	void operator=(const Nuller& n) {inited = false;}
};


}
NAMESPACE_TOPSIDE_END

#endif
