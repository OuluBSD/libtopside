#ifndef _System_Camera_h_
#define _System_Camera_h_

NAMESPACE_ECS_BEGIN


struct Viewport : public Component<Viewport> {
	RTTI_COMP0(Viewport)
	COMP_DEF_VISIT
	
	
	vec3 target = zero<vec3>();
	
	void operator=(const Viewport& vp) {
		target = vp.target;
	}
	
};


NAMESPACE_ECS_END

#endif
