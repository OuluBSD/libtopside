#ifndef _SoftPhys_Common_h_
#define _SoftPhys_Common_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct World;
struct Space;
struct Body;
struct Joint;
struct Mass;
struct Feedback;
struct JointGroup;
struct Threading;
struct ThreadPool;
struct Contact;
struct Geometry;


struct Object : RTTIBase {
	RTTI_DECL0(Object)
	
	bool inited = false;
	
	
	Object() {}
	Object(const Nuller& n) {}
	virtual void Visit(RuntimeVisitor& vis) {}
	void Create() {ASSERT(!inited); inited = true;}
	void Clear() {ASSERT(inited); inited = false;}
	operator bool() const {return inited;}
	void operator=(const Nuller& n) {inited = false;}
};


typedef void (*NearCallback)(void*, Geometry& o1, Geometry& o2);

}
NAMESPACE_TOPSIDE_END

#endif
