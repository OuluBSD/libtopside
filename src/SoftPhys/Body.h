#ifndef _SoftPhys_Body_h_
#define _SoftPhys_Body_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Body : Object {
	RTTI_DECL1(Body, Object)
	using Object::Object;
	
	
	World* world = 0;
	Vector<Geometry*> geoms;
	vec3 position;
	Mass mass;
	vec3 linear_vel;
	vec3 angular_vel;
	vec3 axis;
	float angle = 0;
	
	// possibly unused
	// JointGroup* jgroup = 0;
	PosRot posr;
	quat q;
	mat3 inv_inertia;
	float inv_mass = 0;
	
public:
	Body();
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
	const vec3& GetPosition() const {return position;}
	mat43 GetRotationAxisAngle() const;
	
	Body& SetWorld(World& w);
	Body& SetPosition(const vec3& v);
	Body& SetMass(const Mass& m);
	Body& SetQuaternion(const quat& q);
	Body& SetLinearVelocity(const vec3& v);
	Body& SetAngularVelocity(const vec3& v);
	Body& SetRotation(const vec3& axis, float angle);
	Body& SetMass(float kg);
	
};


}
NAMESPACE_TOPSIDE_END

#endif
