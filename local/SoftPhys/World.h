#ifndef _SoftPhys_World_h_
#define _SoftPhys_World_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct World : Object {
	using Object::Object;
	
	
	
	World();
	
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
	
};


}
NAMESPACE_TOPSIDE_END

#endif
