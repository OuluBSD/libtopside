#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Mass::Mass() {
	Reset();
}

void Mass::Reset() {
	mass = 0;
	inertia.Clear();
}

bool Mass::Check() {
	TODO
	#if 0
    if (mass <= 0) {
        LOG("mass must be > 0");
        return false;
    }
    if (!dIsPositiveDefinite (I,3,NULL)) {
        LOG("inertia must be positive definite");
        return false;
    }
    
    mat3 I2, chat;
    dSetZero (chat,12);
    dSetCrossMatrixPlus (chat, c, 4);
    dMultiply0_333 (I2,chat,chat);
    
    for (int i=0; i<3; i++) I2[i] = I[i] + mass*I2[i];
    for (int i=4; i<7; i++) I2[i] = I[i] + mass*I2[i];
    for (int i=8; i<11; i++) I2[i] = I[i] + mass*I2[i];
    
    if (!dIsPositiveDefinite (I2,3,NULL)) {
        LOG("center of mass inconsistent with mass parameters");
        return false;
    }
    return true;
    #endif
}

Mass& Mass::SetMass(float kg) {
	TODO
}

Mass& Mass::SetFunctionSphere(float density, float radius) {
	float total_mass =
		(4.0f/3.0f) * M_PI *
		radius*radius*radius *
		density;
    
    Reset();
    mass = total_mass;
    float II = 0.4f * total_mass * radius*radius;
    inertia[0][0] = II;
    inertia[1][1] = II;
    inertia[2][2] = II;
	
	ASSERT(Check());
	return *this;
}

Mass& Mass::SetFunctionBox(const vec3& dim, float density) {
	SetFunctionBoxTotal(dim, dim[0] * dim[1] * dim[2] * density);
	return *this;
}

Mass& Mass::SetFunctionBoxTotal(const vec3& dim, float total_mass) {
	float lx = dim[0];
	float ly = dim[1];
	float lz = dim[2];
	
    Reset();
    mass = total_mass;
    inertia[0][0] = total_mass/12.0f * (ly*ly + lz*lz);
    inertia[1][1] = total_mass/12.0f * (lx*lx + lz*lz);
    inertia[2][2] = total_mass/12.0f * (lx*lx + ly*ly);
	
	ASSERT(Check());
	return *this;
}


}
NAMESPACE_TOPSIDE_END
