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
	position = v;
}

Body& Body::SetMass(const Mass& m) {
	mass = m;
}

Body& Body::SetQuaternion(const quat& q) {
	TODO
}

Body& Body::SetLinearVelocity(const vec3& v) {
	linear_vel = v;
}

Body& Body::SetAngularVelocity(const vec3& v) {
	angular_vel = v;
}



}
NAMESPACE_TOPSIDE_END
