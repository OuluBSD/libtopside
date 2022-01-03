#ifndef _SoftPhys_RigidbodyVolume_
#define _SoftPhys_RigidbodyVolume_


NAMESPACE_SOFTPHYS_BEGIN



class RigidbodyVolume : public Geometry {
public:
	vec3 position;
	vec3 velocity;

#ifndef LINEAR_ONLY
	vec3 orientation;
	vec3 ang_vel;
#endif

	vec3 forces; // sumForces
#ifndef LINEAR_ONLY
	vec3 torques; // Sum torques
#endif

				  //vec3 inertia;
	float mass;
	float cor; // Coefficient of restitution
#ifdef DYNAMIC_FRICTION
	float static_friction;
	float dynamic_friction;
#else
	float friction;
#endif

	OBB_ box;
	Sphere_ sphere;
public:

	inline RigidbodyVolume() :
		cor(0.5f), mass(1.0f),
#ifdef DYNAMIC_FRICTION
		static_friction(0.5f),
		dynamic_friction(0.3f)
#else
		friction(0.6f)
#endif
		{
		type = RIGIDBODY_TYPE_BASE;
	}

	inline RigidbodyVolume(int body_type) :
		cor(0.5f), mass(1.0f),
#ifdef DYNAMIC_FRICTION
		static_friction(0.5f),
		dynamic_friction(0.3f)
#else
		friction(0.6f)
#endif
		{
			type = body_type;
	}

	virtual ~RigidbodyVolume() { }

	void Update(float dt) override; // Update Position
	
	float InvMass();
#ifndef LINEAR_ONLY
	mat4 InvTensor();
#endif

	void ApplyForces() override;
	void SynchCollisionVolumes();

	virtual void AddLinearImpulse(const vec3& impulse);
#ifndef LINEAR_ONLY
	virtual void AddRotationalImpulse(const vec3& point, const vec3& impulse);
#endif


public:
	#if SOFTPHYS_RENDER
	Vector<Line> edges;
	
	void Refresh(GfxDataState& s) override;
	void RefreshEdges(GfxDataState& s);
	#endif
	
	
};

CollisionManifold FindCollisionFeatures(RigidbodyVolume& ra, RigidbodyVolume& rb);
void ApplyImpulse(RigidbodyVolume& A, RigidbodyVolume& B, const CollisionManifold& M, int c);


NAMESPACE_SOFTPHYS_END

#endif