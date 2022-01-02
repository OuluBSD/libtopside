#ifndef _SoftPhys_Joint_h_
#define _SoftPhys_Joint_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Joint : Object {
	RTTI_DECL1(Joint, Object)
	using Object::Object;
	
	struct Hinge {
		float lo = 0;
		float hi = 0;
		float vel = 0;
		float max_force = 0;
		
	};
	
	static const int HINGE_COUNT = 4;
	
	JointGroup* group = 0;
	Body* b0 = 0;
	Body* b1 = 0;
	Hinge hinges[HINGE_COUNT];
	Feedback fb;
	vec3 hinge_anchor;
	vec3 hinge_axis1;
	vec3 hinge_axis2;
	vec3 axis;
	float erp = 0;
	float cfm = 0;
	float fudge_factor = 0;
	float angle = 0;
	
	
public:
	Joint();
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
	void Attach(Body& b0, Body& b1);
	
	Joint& SetFeedback(Feedback& f);
	Joint& SetHingeAnchor(const vec3& pos);
	Joint& SetHingeAxes(const vec3& axis1, const vec3& axis2);
	Joint& SetSuspensionERP(float erp);
	Joint& SetSuspensionCFM(float cfm);
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
