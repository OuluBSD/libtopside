#ifndef _SoftPhys_Cloth_
#define _SoftPhys_Cloth_


NAMESPACE_SOFTPHYS_BEGIN


class Cloth {
	
protected:
	Array<Particle> verts;
	Vector<Spring> structural;
	Vector<Spring> shear;
	Vector<Spring> bend;
	float clothSize;
	
public:
	void Initialize(int grid_sz, float distance, const vec3& position);

	void SetStructuralSprings(float k, float b);
	void SetShearSprings(float k, float b);
	void SetBendSprings(float k, float b);
	void SetParticleMass(float mass);

protected:
	friend class PhysicsSystem;
	
	void ApplyForces();
	void Update(float dt);
	void SolveConstraints(const Vector<OBB_>& constraints);
	void ApplySpringForces(float dt);
	
	SOFTPHYS_RENDER_COMMON
	
};


NAMESPACE_SOFTPHYS_END

#endif