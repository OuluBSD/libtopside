#ifndef _SoftPhys_RigidBody_
#define _SoftPhys_RigidBody_

#if 0

NAMESPACE_SOFTPHYS_BEGIN


class Rigidbody {
	
public:
	int type;
	
public:
	inline Rigidbody() {
		type = RIGIDBODY_TYPE_BASE;
	}
	virtual inline ~Rigidbody() { }

	virtual inline void Update(float dt) { }
	virtual inline void Refresh(GfxDataState& s) { }
	virtual inline void ApplyForces() { }
	virtual inline void SolveConstraints(const Vector<OBB_>& constraints) { }

	inline bool HasVolume() {
		return type == RIGIDBODY_TYPE_SPHERE || type == RIGIDBODY_TYPE_BOX;
	}
};


NAMESPACE_SOFTPHYS_END

#endif
#endif
