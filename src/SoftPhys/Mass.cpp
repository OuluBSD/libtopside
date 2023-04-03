#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Mass::Mass() {
	Reset();
}

void Mass::Reset() {
	mass = 0;
	center.Clear();
	inertia.Clear();
}

bool Mass::Check() {
    if (mass <= 0) {
        LOG("mass must be > 0");
        return false;
    }
    if (!IsPositiveDefinite(inertia)) {
        LOG("inertia must be positive definite");
        return false;
    }
    
    mat3 I2, chat;
    chat.Clear();
    SetCrossMatrixPlus(chat, center);
    Multiply(I2, chat, chat);
    
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            I2[i][j] = inertia[i][j] + mass * I2[i][j];
    
    if (!IsPositiveDefinite(I2)) {
        LOG("center of mass inconsistent with mass parameters");
        return false;
    }
    return true;
}

Mass& Mass::Translate(const vec3& v) {
	// counterparts: ode=dMassTranslate
	float x = v[0];
	float y = v[1];
	float z = v[2];
	mat3 ahat, chat, t1, t2;
	vec3 a;
	
	ASSERT(mass > 0);
	
	chat.Clear();
	SetCrossMatrixPlus (chat, center);
	a[0] = x + center[0];
	a[1] = y + center[1];
	a[2] = z + center[2];
	ahat.Clear();
	SetCrossMatrixPlus(ahat, a);
	Multiply(t1, ahat, ahat);
	Multiply(t2, chat, chat);
	
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			inertia[i][j] +=
				mass *
				(t2[i][j] - t1[i][j]);
	
	inertia[1][0] = inertia[0][1];
	inertia[2][0] = inertia[0][2];
	inertia[2][1] = inertia[1][2];
	
	center[0] += x;
	center[1] += y;
	center[2] += z;
	
	ASSERT(Check());
	return *this;
}

Mass& Mass::MoveMassCenter() {
	Translate( center * -1 );
	return *this;
}

Mass& Mass::SetMass(float kg) {
	ASSERT(kg > 0 && mass > 0);
	float scale = kg / mass;
	mass = kg;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			inertia[i][j] *= scale;
	
	ASSERT(Check());
	return *this;
}

Mass& Mass::SetFunctionSphere(float density, float radius) {
	float total_mass =
		(4.0f/3.0f) * M_PIf *
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
