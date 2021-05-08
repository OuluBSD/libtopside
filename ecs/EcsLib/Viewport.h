#ifndef _System_Camera_h_
#define _System_Camera_h_

NAMESPACE_OULU_BEGIN


struct Viewport : public Component<Viewport> {
	VIS_COMP_0_0
	
	vec3 target = zero<vec3>();
	
	void Visit(RuntimeVisitor& vis) override {}
	void operator=(const Viewport& vp) {
		target = vp.target;
	}
	
};


NAMESPACE_OULU_END

#endif
