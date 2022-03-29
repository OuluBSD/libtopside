#include "IfaceLib.h"

//... going with the "fys" instead of "phys", becase of ... reasons

NAMESPACE_PLAN_BEGIN

PKG(Physics, Fys, F) {
	IfaceLib::Add(this);
	
	
	COLOR(113, 42, 150)
	MAINFLAG(Screen)
	DEPENDENCY(SoftPhys)
	
	PKG_IFACE {
		NATIVE_CLASS(Geom)
		NATIVE_CLASS(Body)
		NATIVE_CLASS(World)
		NATIVE_CLASS(Space)
		NATIVE_CLASS(Joint)
		NATIVE_CLASS(Mass)
		NATIVE_CLASS(Quat)
		NATIVE_CLASS(Feedback)
		NATIVE_CLASS(JointGroup)
		NATIVE_CLASS(Threading)
		NATIVE_CLASS(ThreadPool)
		NATIVE_CLASS(Contact)
		
		/*FUNCTION0V(InitializeLibrary)
		FUNCTION0V(UninitializeLibrary)
		
		FUNCTION1V(CreateWorld, NativeWorld& world);
		FUNCTION1V(ClearWorld, NativeWorld& world);
		FUNCTION2V(SetGravity, NativeWorld& world, const vec3& v);
		FUNCTION2V(SetWorldCFM, NativeWorld& world, float f);
		FUNCTION2V(SetMaxCorrectingVelocity, NativeWorld& world, float f);
		FUNCTION2V(SetContactSurfaceLayer, NativeWorld& world, float f);
		FUNCTION2V(SetAutoDisable, NativeWorld& world, bool b);
		FUNCTION2V(SetStepIterations, NativeWorld& world, int i);
		FUNCTION2V(SetAutoDisableSamples, NativeWorld& world, int i);
		
		FUNCTION4V(CreateSpace, NativeWorld& world, NativeSpace& space, NativeSpace* owner, bool is_root);
		FUNCTION1V(ClearSpace, NativeSpace& space);
		FUNCTION2V(Collide, NativeSpace& space, void* data);
		FUNCTION5R(CollideContacts, int, NativeGeom& o1, NativeGeom& o2, int count, NativeContact* c, int ptr_pitch);
		FUNCTION2V(Step, NativeWorld& world, float seconds);
		FUNCTION7V(AttachContact, NativeWorld& w, NativeJointGroup& cg, NativeContact& c, float slip1, float slip2, float erp, float cfm);
		FUNCTION2V(AddGeomToSpace, NativeSpace& space, NativeGeom& geom);
		FUNCTION2V(RemoveGeomFromSpace, NativeSpace& space, NativeGeom& geom);
		
		FUNCTION1V(CreateJointGroup, NativeJointGroup& g);
		FUNCTION1V(ClearJointGroup, NativeJointGroup& g);
		FUNCTION1V(DetachJointGroup, NativeJointGroup& g);
		
		FUNCTION1V(CreateThreading, NativeThreading& t);
		FUNCTION1V(CreateThreadPool, NativeThreadPool& p);
		FUNCTION2V(AttachThreadPool, NativeThreading& t, NativeThreadPool& p);
		FUNCTION2V(AttachThreading, NativeWorld& w, NativeThreading& t);
		FUNCTION1V(DetachWorldThreading, NativeWorld& w);
		FUNCTION1V(DetachThreading, NativeThreading& t);
		FUNCTION1V(ClearThreadPool, NativeThreadPool& p);
		FUNCTION1V(ClearThreading, NativeThreading& t);
		
		FUNCTION2V(CreateBody, NativeWorld& w, NativeBody& b);
		FUNCTION1V(ClearBody, NativeBody& b);
		FUNCTION1R(GetBodyPosition, vec3, NativeBody& b);
		FUNCTION5V(SetBodyRotationAxisAngle, NativeBody& b, float ax, float ay, float az, float angle);
		FUNCTION2V(SetBodyMass, NativeBody& b, NativeMass& m);
		FUNCTION4V(SetBodyPosition, NativeBody& b, float x, float y, float z);
		FUNCTION2V(SetBodyQuaternion, NativeBody& b, const quat& q);
		FUNCTION2V(SetBodyLinearVelocity, NativeBody& b, const vec3& v);
		FUNCTION2V(SetBodyAngularVelocity, NativeBody& b, const vec3& v);
		
		FUNCTION1V(ClearGeom, NativeGeom& g);
		FUNCTION3V(SetGeomModelPlane, NativeGeom& g, NativeSpace& s, const vec4& plane=vec4(0,1,0,0));
		FUNCTION2V(SetGeomModelSphere, NativeGeom& g, float radius);
		FUNCTION4V(SetGeomModelBox, NativeGeom& g, float w, float h, float l);
		FUNCTION4V(SetGeomPosition, NativeGeom& g, float x, float y, float z);
		FUNCTION5V(SetGeomRotationAxisAngle, NativeGeom& g, float ax, float ay, float az, float angle);
		FUNCTION2V(SetGeomBody, NativeGeom& g, NativeBody& b);
		FUNCTION1V(ResetGeomRotation, NativeGeom& geom);
		FUNCTION1R(GetGeomPosition, vec3, NativeGeom& geom);
		FUNCTION1R(GetGeomQuaternion, quat, NativeGeom& geom);
		FUNCTION1R(GetGeomRotationAxisAngle, mat43, NativeBody& body);
		
		FUNCTION2V(CreateJointHinge2, NativeWorld& w, NativeJoint& j);
		FUNCTION3V(AttachJoint, NativeJoint& j, NativeBody& b0, NativeBody& b1);
		FUNCTION1V(GetDefaultOrientation, NativeQuat& q)
		FUNCTION2V(SetJointFeedback, NativeJoint& j, NativeFeedback& fb);
		FUNCTION2V(SetJointHingeAnchor, NativeJoint& j, const vec3& pos);
		FUNCTION3V(SetJointHingeAxes, NativeJoint& j, const vec3& axis1, const vec3& axis2);
		FUNCTION2V(SetSuspensionERP, NativeJoint& j, float erp);
		FUNCTION2V(SetSuspensionCFM, NativeJoint& j, float cfm);
		FUNCTION4V(SetHingeRange, NativeJoint& j, float lo, float hi, int idx=0);
		FUNCTION3V(SetHingeVelocity, NativeJoint& j, float v, int idx=0);
		FUNCTION3V(SetMaxForce, NativeJoint& j, float v, int idx=0);
		FUNCTION2V(SetFudgeFactor, NativeJoint& j, float v);
		FUNCTION2V(SetHingeAnchor, NativeJoint& j, const vec3& v);
		FUNCTION2V(SetAxis, NativeJoint& j, const vec3& v);
		FUNCTION1R(GetAngle, float, NativeJoint& j);
		
		
		// utility functions
		FUNCTION3V(SetQuatFromAxisAngle, NativeQuat& q, const vec3& axis, float angle);
		FUNCTION3V(SetMassFunctionSphere, NativeMass& mass, float density, float radius);
		FUNCTION4V(SetMassFunctionBoxDefault, NativeMass& mass, float w, float h, float l);
		FUNCTION5V(SetMassFunctionBox, NativeMass& mass, float density, float w, float h, float l);
		FUNCTION2V(SetMass, NativeMass& mass, float kg);
		*/
	}
	
	NAMESPACE {
		CLASS(Node) {
			
		}
		CLASS(Object) {
			
		}
		CLASS(Joint) {
			
		}
		CLASS(Space) {
			
		}
		CLASS(System) {
			
		}
		
		/*PREFAB() {
			
		}*/
	}
	
	
	// libtopside
	VENDOR(Tos) {
		
		
		
	}
	
	// Open Dynamics Engine
	VENDOR(Ode) {
		
		
		
	}
	
}

NAMESPACE_PLAN_END
