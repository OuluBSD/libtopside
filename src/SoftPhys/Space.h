#ifndef _SoftPhys_Space_h_
#define _SoftPhys_Space_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Space : Object {
	RTTI_DECL1(Space, Object)
	using Object::Object;
	
	
	Space* owner = 0;
	World* world = 0;
	Vector<Geometry*> geoms;
	
public:
	Space();
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
	void SetWorld(World& w);
	void Collide(void* data, NearCallback cb);
	void Add(Geometry& g);
	void Remove(Geometry& g);
	void Clear();
	
	Space& SetOwner(Space* s) {owner = s; return *this;}
	
};


int Collide(Geometry& g0, Geometry& g1, int count, Contact* c, int ptr_pitch);


}
NAMESPACE_TOPSIDE_END

#endif
