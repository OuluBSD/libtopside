#ifndef _SoftPhys_Spring_
#define _SoftPhys_Spring_


NAMESPACE_SOFTPHYS_BEGIN


// F = -kx-bv
// k - spring "tightness" constant [negative to 0] rigid at 0
// x - displacement of spring from equalibrium
// b - constant (coefficient) dampening
// v - realtive velocity of points of spring

class Spring : Moveable<Spring> {
public:
	Particle* p1;
	Particle* p2;

	float k; // [-x to 0] higher = stiff sprint, lower = loose spring
	float rest_length;
	float b;
public:
	Spring(float _k, float _b, float len);
	void SetParticles(Particle* _p1, Particle* _p2);
	Particle* GetP1();
	Particle* GetP2();
	void SetConstants(float _k, float _b);
	void ApplyForce(float dt);
	
	#if SOFTPHYS_RENDER
	Line_ l;
	SOFTPHYS_RENDER_COMMON
	#endif
	
};


NAMESPACE_SOFTPHYS_END

#endif