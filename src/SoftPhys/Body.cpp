#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Body::Body() {
	
}


mat43 Body::GetRotationAxisAngle() const {
	TODO
}

Body& Body::SetWorld(World& w) {
	world = &w;
	return *this;
}


Body& Body::SetPosition(const vec3& v) {
	position = v;
	return *this;
}

Body& Body::SetMass(const Mass& m) {
	mass = m;
	return *this;
}

Body& Body::SetQuaternion(const quat& n) {
	ASSERT(inited);
    q[0] = n[0];
    q[1] = n[1];
    q[2] = n[2];
    q[3] = n[3];
    q.Normalize();
    QtoR(q, posr.rot);
	
    // notify all attached geoms that this body has moved
    for (Geometry *geom : geoms)
        geom->OnBodyMove();
    
	return *this;
}

Body& Body::SetLinearVelocity(const vec3& v) {
	linear_vel = v;
	return *this;
}

Body& Body::SetAngularVelocity(const vec3& v) {
	angular_vel = v;
	return *this;
}

Body& Body::SetRotation(const vec3& axis, float angle) {
	this->axis = axis;
	this->angle = angle;
	return *this;
}

Body& Body::SetMass(float kg) {
	ASSERT(kg > 0);
    TODO
    #if 0
    // Use MoveMassCenter() to correct.
    ASSERT_(fabs( mass.center[0] ) <= PHYS_EPSILON &&
			fabs( mass.center[1] ) <= PHYS_EPSILON &&
			fabs( mass.center[2] ) <= PHYS_EPSILON,
				"The centre of mass must be at the origin." );

    mass.mass = kg;
    
    if (dInvertPDMatrix(mass.I, inv_inertia, 3, NULL)==0) {
        LOG("warning: inertia must be positive definite!");
        inv_inertia.SetIdentity();
    }
    
    inv_mass = 1.0f / mass.mass;
    #endif
}



}
NAMESPACE_TOPSIDE_END
