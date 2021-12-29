#ifndef _SoftPhys_Joint_h_
#define _SoftPhys_Joint_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Joint : Object {
	using Object::Object;
	
	
	
	Joint();
	
	void Attach(Body& b0, Body& b1);
	
	Joint& SetFeedback(Feedback& f);
	Joint& SetHingeAnchor(const vec3& pos);
	Joint& SetHingeAxes(const vec3& axis1, const vec3& axis2);
	Joint& SetSuspensionERP(float erp);
	Joint& SetSuspensionCFM(float erp);
	Joint& SetHingeRange(float lo, float hi, int idx);
	Joint& SetHingeVelocity(float v, int idx);
	Joint& SetMaxForce(float v, int idx);
	Joint& SetFudgeFactor(float v);
	Joint& SetAxis(const vec3& v);
	
	float GetAngle() const;
	
};


}
NAMESPACE_TOPSIDE_END

#endif
