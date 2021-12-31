#ifndef _SoftPhys_DistanceJoint_
#define _SoftPhys_DistanceJoint_


NAMESPACE_SOFTPHYS_BEGIN


class DistanceJoint : public Rigidbody {
	
protected:
	Particle* p1;
	Particle* p2;
	float length;
	
public:
	void Initialize(Particle* _p1, Particle* _p2, float len);
	void SolveConstraints(const Vector<OBB>& constraints);
	
};


NAMESPACE_SOFTPHYS_END

#endif
