#ifndef _Physics_TJoint_h_
#define _Physics_TJoint_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Fys>
struct JointT : NodeT<Fys> {
	using Node = NodeT<Fys>;
	using Object = ObjectT<Fys>;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	using NativeGeom = typename Fys::NativeGeom;
	using NativeBody = typename Fys::NativeBody;
	using NativeMass = typename Fys::NativeMass;
	using NativeQuat = typename Fys::NativeQuat;
	using NativeJoint = typename Fys::NativeJoint;
	using NativeFeedback = typename Fys::NativeFeedback;
	
protected:
	NativeJoint joint;
	NativeFeedback feedback;
	int stress = 0;
	
public:
	RTTI_DECL1(JointT, Node)
	JointT() {}
	
	void OnAttach() override {
		joint = Fys::CreateJointHinge2(this->GetNativeWorld());
		Fys::SetJointFeedback(joint, feedback);
	}
	
	void AttachHinge(Object& owner, Object& face) {
		Fys::AttachJoint(joint, owner.body, face.body);
		vec3 pos = Fys::GetBodyPosition(face.body);
		Fys::SetJointHingeAnchor(joint, pos);
		vec3 xunit(1, 0, 0);
		vec3 yunit(0, 1, 0);
		vec3 zunit(0, 0, 1);
		Fys::SetJointHingeAxes(joint, yunit, xunit);
	}
	
	void SetHingeSuspension(float erp, float cfm) {
		Fys::SetSuspensionERP(joint, erp);
		Fys::SetSuspensionCFM(joint, cfm);
	}
	
	void SetHingeLock() {SetHingeRange(0, 0);}
	void SetHingeRange (float lo, float hi) {Fys::SetHingeRange(joint, lo, hi, 0);}
	void SetHingeRange1(float lo, float hi) {Fys::SetHingeRange(joint, lo, hi, 1);}
	void SetHingeRange2(float lo, float hi) {Fys::SetHingeRange(joint, lo, hi, 2);}
	void SetHingeRange3(float lo, float hi) {Fys::SetHingeRange(joint, lo, hi, 3);}
	void SetVelocity (float d) {Fys::SetHingeVelocity(joint, d, 0);}
	void SetVelocity1(float d) {Fys::SetHingeVelocity(joint, d, 1);}
	void SetVelocity2(float d) {Fys::SetHingeVelocity(joint, d, 2);}
	void SetVelocity3(float d) {Fys::SetHingeVelocity(joint, d, 3);}
	void SetMaxForce (float d) {Fys::SetMaxForce(joint, d, 0);}
	void SetMaxForce1(float d) {Fys::SetMaxForce(joint, d, 1);}
	void SetMaxForce2(float d) {Fys::SetMaxForce(joint, d, 2);}
	void SetMaxForce3(float d) {Fys::SetMaxForce(joint, d, 3);}
	void SetFudgeFactor(float d) {Fys::SetFudgeFactor(joint, d);}
	void SetAnchor(const vec3& v) {Fys::SetHingeAnchor(joint, v);}
	void SetAxis(const vec3& v) {Fys::SetAxis(joint, v);}
	
	float GetAngle() {return Fys::GetAngle(joint);}
	
	
};


NAMESPACE_TOPSIDE_END

#endif
