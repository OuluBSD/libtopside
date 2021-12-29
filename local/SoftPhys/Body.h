#ifndef _SoftPhys_Body_h_
#define _SoftPhys_Body_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Body : Object {
	using Object::Object;
	
	
	
	Body();
	
	vec3 GetPosition() const;
	mat43 GetRotationAxisAngle() const;
	
	Body& SetPosition(const vec3& v);
	Body& SetMass(const Mass& m);
	Body& SetQuaternion(const quat& q);
	Body& SetLinearVelocity(const vec3& v);
	Body& SetAngularVelocity(const vec3& v);
	
};


}
NAMESPACE_TOPSIDE_END

#endif
