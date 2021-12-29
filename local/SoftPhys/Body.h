#ifndef _SoftPhys_Body_h_
#define _SoftPhys_Body_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Body : Object {
	using Object::Object;
	
	
	vec3 position;
	Mass mass;
	vec3 linear_vel;
	vec3 angular_vel;
	vec3 axis;
	float angle = 0;
	
	Body();
	
	vec3 GetPosition() const;
	mat43 GetRotationAxisAngle() const;
	
	Body& SetPosition(const vec3& v);
	Body& SetMass(const Mass& m);
	Body& SetQuaternion(const quat& q);
	Body& SetLinearVelocity(const vec3& v);
	Body& SetAngularVelocity(const vec3& v);
	Body& SetRotation(const vec3& axis, float angle);
	
};


}
NAMESPACE_TOPSIDE_END

#endif
