#ifndef _SoftPhys_Particle_
#define _SoftPhys_Particle_


NAMESPACE_SOFTPHYS_BEGIN


class Particle : public Geometry {
	vec3 position;
	vec3 old_position;
	vec3 forces;

	vec3 gravity;
	float friction;
	float bounce;

#ifdef EULER_INTEGRATION
	vec3 velocity;
#endif
	float mass;
public:
	Particle();

	void Update(float dt);
	void ApplyForces();
	void SolveConstraints(const Vector<OBB_>& constraints);
	void AddImpulse(const vec3& impulse);

	vec3 GetPosition();
	float GetBounce();
	float InvMass();
	vec3 GetVelocity();
	
	void SetPosition(const vec3& pos);
	void SetBounce(float b);
	void SetMass(float m);
	void SetFriction(float f);
	
public:
	#if SOFTPHYS_RENDER
	Wrap<Sphere> vis;
	SOFTPHYS_RENDER_COMMON
	#endif
	
};


NAMESPACE_SOFTPHYS_END

#endif
