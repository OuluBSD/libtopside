#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Geometry::Geometry() {
	
}


vec3 Geometry::GetPosition() const {
	return position;
}

quat Geometry::GetQuaternion() const {
	return orient;
}

Geometry& Geometry::SetWorldMatrix(const mat4& m) {
	position = m.GetTranslation();
	orient = MatQuat(m);
	return *this;
}

void Geometry::OnBodyMove() {
	TODO
}

Geometry& Geometry::SetModelPlane(Space& s, const vec4& plane) {
	LOG("Geometry::SetModelPlane: warning: pass, for now");
	return *this;
}

Geometry& Geometry::SetModelSphere(float radius) {
	type = RIGIDBODY_TYPE_SPHERE;
	return *this;
}

Geometry& Geometry::SetModelBox(const vec3& v) {
	type = RIGIDBODY_TYPE_BOX;
	return *this;
}

Geometry& Geometry::SetPosition(const vec3& v) {
	position = v;
	return *this;
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
	orient = AxisAngleQuat(axis, angle);
	return *this;
}



}
NAMESPACE_TOPSIDE_END
