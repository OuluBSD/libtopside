#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


void DistanceJoint::Initialize(Particle* _p1, Particle* _p2, float len) {
	p1 = _p1;
	p2 = _p2;
	length = len;
}

void DistanceJoint::SolveConstraints(const Vector<OBB_>& constraints) {
	vec3 delta = p2->GetPosition() - p1->GetPosition();
	float distance = Magnitude(delta);
	float correction = (distance - length) / distance;
	
	p1->SetPosition(p1->GetPosition() + delta * 0.5f * correction);
	p2->SetPosition(p2->GetPosition() - delta * 0.5f * correction);

	p1->SolveConstraints(constraints);
	p2->SolveConstraints(constraints);
}


NAMESPACE_SOFTPHYS_END
