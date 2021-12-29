#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Body::Body() {
	
}


vec3 Body::GetPosition() const {
	TODO
}

mat43 Body::GetRotationAxisAngle() const {
	TODO
}


Body& Body::SetPosition(const vec3& v) {
	TODO
}

Body& Body::SetMass(const Mass& m) {
	TODO
}

Body& Body::SetQuaternion(const quat& q) {
	TODO
}

Body& Body::SetLinearVelocity(const vec3& v) {
	TODO
}

Body& Body::SetAngularVelocity(const vec3& v) {
	TODO
}



}
NAMESPACE_TOPSIDE_END
