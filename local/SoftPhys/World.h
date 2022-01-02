#ifndef _SoftPhys_World_h_
#define _SoftPhys_World_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct World : Object {
	RTTI_DECL1(World, Object)
	
	using Object::Object;
	
	Threading* threading = 0;
	
	vec3 gravity;
	float correcting_velocity = 0;
	float surface_layer = 0;
	int iters = 64;
	int auto_disable_samples = 0;
	bool auto_disable = 0;
	
	PhysicsSystem phys_sys;
	JointGroup jgroup;
	
public:
	
	
	World();
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object); vis % phys_sys;}
	void Collide(Space& space, void* data, NearCallback cb);
	void Step(float seconds);
	void AttachThreading(Threading& t);
	void DetachThreading();
	void CreateBody(Body& b);
	void CreateJoint(Joint& j);
	
	World& SetGravity(const vec3& v);
	World& SetMaxCorrectingVelocity(float f);
	World& SetContactSurfaceLayer(float f);
	World& SetAutoDisable(bool b);
	World& SetStepIterations(int i);
	World& SetAutoDisableSamples(int i);
	
	PhysicsSystem& GetSystem() {return phys_sys;}
	const PhysicsSystem& GetSystem() const {return phys_sys;}
	
};


}
NAMESPACE_TOPSIDE_END

#endif
