#ifndef _SoftPhys_Mass_h_
#define _SoftPhys_Mass_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Mass : Object {
	RTTI_DECL1(Mass, Object)
	using Object::Object;
	
	float mass;
	vec3 center;
	mat3 inertia;
	
	
public:
	Mass();
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
	void Reset();
	bool Check();
	
	Mass& Translate(const vec3& v);
	Mass& MoveMassCenter();
	Mass& SetMass(float kg);
	Mass& SetFunctionSphere(float density, float radius);
	Mass& SetFunctionBox(const vec3& dim, float density=1);
	Mass& SetFunctionBoxTotal(const vec3& dim, float total_mass);
	
};


}
NAMESPACE_TOPSIDE_END

#endif
