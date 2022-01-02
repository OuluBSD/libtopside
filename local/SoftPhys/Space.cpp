#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Space::Space() {
	
}

void Space::SetWorld(World& w) {
	ASSERT(!world);
	world = &w;
	w.GetSystem().AddSpace(*this);
}

void Space::Collide(void* data, NearCallback cb) {
	ASSERT(world);
	world->Collide(*this, data, cb);
}

void Space::Add(Geometry& g) {
	VectorFindAdd(geoms, &g);
}

void Space::Remove(Geometry& g) {
	VectorRemoveKey(geoms, &g);
}

void Space::Clear() {
	//for (Geometry* g : geoms)
		//g->
	geoms.Clear();
}



int Collide(Geometry& g0, Geometry& g1, int count, Contact* c, int ptr_pitch) {
	TODO
}


}
NAMESPACE_TOPSIDE_END
