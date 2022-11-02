#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Joint::Joint() {
	
}


void Joint::Attach(Body& b0, Body& b1) {
	ASSERT(!this->b0 && !this->b1);
	this->b0 = &b0;
	this->b1 = &b1;
}


Joint& Joint::SetFeedback(Feedback& f) {
	fb = f;
	return *this;
}

Joint& Joint::SetHingeAnchor(const vec3& pos) {
	hinge_anchor = pos;
	return *this;
}

Joint& Joint::SetHingeAxes(const vec3& axis1, const vec3& axis2) {
	hinge_axis1 = axis1;
	hinge_axis2 = axis2;
	return *this;
}

Joint& Joint::SetSuspensionERP(float erp) {
	this->erp = erp;
	return *this;
}

Joint& Joint::SetSuspensionCFM(float cfm) {
	this->cfm = cfm;
	return *this;
}

Joint& Joint::SetHingeRange(float lo, float hi, int idx) {
	if (idx >= 0 && idx < HINGE_COUNT) {
		hinges[idx].lo = lo;
		hinges[idx].hi = hi;
	}
	return *this;
}

Joint& Joint::SetHingeVelocity(float v, int idx) {
	if (idx >= 0 && idx < HINGE_COUNT) {
		hinges[idx].vel = v;
	}
	return *this;
}

Joint& Joint::SetMaxForce(float v, int idx) {
	if (idx >= 0 && idx < HINGE_COUNT) {
		hinges[idx].max_force = v;
	}
	return *this;
}

Joint& Joint::SetFudgeFactor(float v) {
	fudge_factor = v;
	return *this;
}

Joint& Joint::SetAxis(const vec3& v) {
	axis = v;
	return *this;
}


float Joint::GetAngle() const {
	return angle;
}



}
NAMESPACE_TOPSIDE_END
