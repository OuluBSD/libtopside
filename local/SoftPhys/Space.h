#ifndef _SoftPhys_Space_h_
#define _SoftPhys_Space_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Space : Object {
	using Object::Object;
	
	typedef void (*NearCallback)(void*, Geometry& o1, Geometry& o2);
	
	Space* owner = 0;
	
	
	
	Space();
	void Collide(void* data, NearCallback cb);
	void Add(Geometry& g);
	void Remove(Geometry& g);
	
	Space& SetOwner(Space* s) {owner = s; return *this;}
	
};


int Collide(Geometry& g0, Geometry& g1, int count, Contact* c, int ptr_pitch);


}
NAMESPACE_TOPSIDE_END

#endif
