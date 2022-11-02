#ifndef _SoftPhys_System_
#define _SoftPhys_System_


NAMESPACE_SOFTPHYS_BEGIN


struct Geometry;


class PhysicsSystem : RTTIBase {
	RTTI_DECL0(PhysicsSystem)
	
protected:
	Vector<Space*> spaces;
	//Vector<Geometry*> bodies;
	Vector<Cloth*> cloths;
	Vector<OBB_> constraints;
	Vector<Spring> springs;

	Vector<Geometry*> colliders1;
	Vector<Geometry*> colliders2;
	Vector<CollisionManifold> results;
	
public:
	float lin_proj_perc; // [0.2 to 0.8], Smaller = less jitter / more penetration
	float penet_slack; // [0.01 to 0.1],  Smaller = more accurate
	int impulse_iter;

	// Not in book, just for debug purposes
	bool do_lin_proj;
	bool rend_rand_clr;

	PhysicsSystem();

	virtual void Visit(RuntimeVisitor& vis) {}
	void Collide(Space& space, void* data, NearCallback cb);
	void Update(float dt);
	
	SOFTPHYS_RENDER_COMMON
	
	void AddSpace(Space& space);
	//void AddRigidbody(Geometry* body);
	void AddCloth(Cloth* cloth);
	void AddSpring(const Spring& spring);
	void AddConstraint(const OBB_& constraint);

	//void ClearRigidbodys();
	void ClearConstraints();
	void ClearSprings();
	void ClearCloths();
	
	
};


NAMESPACE_SOFTPHYS_END

#endif
