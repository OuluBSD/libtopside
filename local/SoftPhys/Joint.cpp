#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Joint::Joint() {
	
}


void Joint::Attach(Body& b0, Body& b1) {
	TODO
}


Joint& Joint::SetFeedback(Feedback& f) {
	TODO
}

Joint& Joint::SetHingeAnchor(const vec3& pos) {
	TODO
}

Joint& Joint::SetHingeAxes(const vec3& axis1, const vec3& axis2) {
	TODO
}

Joint& Joint::SetSuspensionERP(float erp) {
	TODO
}

Joint& Joint::SetSuspensionCFM(float erp) {
	TODO
}

Joint& Joint::SetHingeRange(float lo, float hi, int idx) {
	TODO
}

Joint& Joint::SetHingeVelocity(float v, int idx) {
	TODO
}

Joint& Joint::SetMaxForce(float v, int idx) {
	TODO
}

Joint& Joint::SetFudgeFactor(float v) {
	TODO
}

Joint& Joint::SetAxis(const vec3& v) {
	TODO
}


float Joint::GetAngle() const {
	TODO
}



}
NAMESPACE_TOPSIDE_END
