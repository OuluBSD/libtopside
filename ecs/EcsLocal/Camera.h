#ifndef _EcsLocal_Camera_h_
#define _EcsLocal_Camera_h_

NAMESPACE_ECS_BEGIN


class Viewable :
	public Component<Viewable>
{
	vec3 target = zero<vec3>();
	
public:
	RTTI_COMP0(Viewable)
	COMP_DEF_VISIT
	
	
	vec3 GetTarget() const {return target;}
	void SetTraget(const vec3& v) {target = v;}
	
	void operator=(const Viewable& c) {target = c.target;}
	
	//ViewableRef GetViewable() override {return ComponentBase::AsRef<Viewable>();}
	//TransformRef GetTransform();
	
};


NAMESPACE_ECS_END

#endif
