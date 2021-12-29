#ifndef _SoftPhys_Geometry_h_
#define _SoftPhys_Geometry_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Geometry : Object {
	using Object::Object;
	
	
	
	Geometry();
	
	vec3 GetPosition() const;
	quat GetQuaternion() const;
	
	Geometry& SetModelPlane(Space& s, const vec4& plane);
	Geometry& SetModelSphere(float radius);
	Geometry& SetModelBox(const vec3& v);
	Geometry& SetPosition(const vec3& v);
	Geometry& SetGeomBody(const Body& b);
	Geometry& SetRotation(const vec3& axis, float angle);
	Geometry& ResetRotation();
	
};


}
NAMESPACE_TOPSIDE_END

#endif
