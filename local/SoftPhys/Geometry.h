#ifndef _SoftPhys_Geometry_h_
#define _SoftPhys_Geometry_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Geometry : Object {
	RTTI_DECL1(Geometry, Object)
	using Object::Object;
	
	
	
	Body* body = 0;
	vec3 position;
	vec3 axis;
	float angle = 0;
	
	int type = 0;
	
	Geometry();
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
	vec3 GetPosition() const;
	quat GetQuaternion() const;
	
	Geometry& SetModelPlane(Space& s, const vec4& plane);
	Geometry& SetModelSphere(float radius);
	Geometry& SetModelBox(const vec3& v);
	Geometry& SetPosition(const vec3& v);
	Geometry& SetGeomBody(Body& b);
	Geometry& SetRotation(const vec3& axis, float angle);
	Geometry& ResetRotation();
	
	virtual inline void Update(float dt) {}
	virtual inline void Render() {}
	virtual inline void ApplyForces() {}
	virtual inline void SolveConstraints(const Vector<OBB>& constraints) {}
	
	bool HasVolume() {return type == RIGIDBODY_TYPE_SPHERE || type == RIGIDBODY_TYPE_BOX;}
	
};


}
NAMESPACE_TOPSIDE_END

#endif
