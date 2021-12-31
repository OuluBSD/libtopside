#ifndef _SoftPhys_System_
#define _SoftPhys_System_


NAMESPACE_SOFTPHYS_BEGIN



class PhysicsSystem {
	
protected:
	Vector<Rigidbody*> bodies;
	Vector<Cloth*> cloths;
	Vector<OBB> constraints;
	Vector<Spring> springs;

	Vector<Rigidbody*> colliders1;
	Vector<Rigidbody*> colliders2;
	Vector<CollisionManifold> results;
	
public:
	float lin_proj_perc; // [0.2 to 0.8], Smaller = less jitter / more penetration
	float penet_slack; // [0.01 to 0.1],  Smaller = more accurate
	int impulse_iter;

	// Not in book, just for debug purposes
	bool dbg_render;
	bool do_lin_proj;
	bool rend_rand_clr;

	PhysicsSystem();

	void Update(float dt);
	void Render();
	
	void AddRigidbody(Rigidbody* body);
	void AddCloth(Cloth* cloth);
	void AddSpring(const Spring& spring);
	void AddConstraint(const OBB& constraint);

	void ClearRigidbodys();
	void ClearConstraints();
	void ClearSprings();
	void ClearCloths();
	
	
};


NAMESPACE_SOFTPHYS_END

#endif
