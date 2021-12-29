#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Geometry::Geometry() {
	
}


vec3 Geometry::GetPosition() const {
	TODO
}

quat Geometry::GetQuaternion() const {
	TODO
}


Geometry& Geometry::SetModelPlane(Space& s, const vec4& plane) {
	TODO
}

Geometry& Geometry::SetModelSphere(float radius) {
	TODO
}

Geometry& Geometry::SetModelBox(const vec3& v) {
	TODO
}

Geometry& Geometry::SetPosition(const vec3& v) {
	TODO
}

Geometry& Geometry::SetGeomBody(const Body& b) {
	TODO
}

Geometry& Geometry::SetRotation(const vec3& axis, float angle) {
	TODO
}

Geometry& Geometry::ResetRotation() {
	TODO
}



}
NAMESPACE_TOPSIDE_END
