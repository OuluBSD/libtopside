#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Geometry::Geometry() {
	
}


vec3 Geometry::GetPosition() const {
	return position;
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
	position = v;
}

Geometry& Geometry::SetGeomBody(Body& b) {
	ASSERT(!body);
	body = &b;
	return *this;
}

Geometry& Geometry::ResetRotation() {
	TODO
}

Geometry& Geometry::SetRotation(const vec3& axis, float angle) {
	this->axis = axis;
	this->angle = angle;
	return *this;
}



}
NAMESPACE_TOPSIDE_END
