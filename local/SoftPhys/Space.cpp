#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Space::Space() {
	
}

void Space::Collide(void* data, NearCallback cb) {
	TODO
}

void Space::Add(Geometry& g) {
	VectorFindAdd(geoms, &g);
}

void Space::Remove(Geometry& g) {
	VectorRemoveKey(geoms, &g);
}



int Collide(Geometry& g0, Geometry& g1, int count, Contact* c, int ptr_pitch) {
	TODO
}


}
NAMESPACE_TOPSIDE_END