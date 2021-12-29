#ifndef _SoftPhys_Mass_h_
#define _SoftPhys_Mass_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Mass : Object {
	using Object::Object;
	
	float mass;
	mat3 inertia;
	
	
	Mass();
	
	void Reset();
	bool Check();
	
	Mass& SetMass(float kg);
	Mass& SetFunctionSphere(float density, float radius);
	Mass& SetFunctionBox(const vec3& dim, float density=1);
	Mass& SetFunctionBoxTotal(const vec3& dim, float total_mass);
	
};


}
NAMESPACE_TOPSIDE_END

#endif
