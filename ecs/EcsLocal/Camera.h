#ifndef _EcsLocal_Camera_h_
#define _EcsLocal_Camera_h_

NAMESPACE_ECS_BEGIN

#if 0
class Viewable :
	public Component<Viewable>,
	public HumanSink
{
	vec3 target = zero<vec3>();
	
public:
	RTTI_COMP1(Viewable, HumanSink)
	VIS_COMP_0_1(Human)
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
	vec3 GetTarget() const {return target;}
	void SetTraget(const vec3& v) {target = v;}
	
	void operator=(const Viewable& c) {target = c.target;}
	
	//ViewableRef GetViewable() override {return ComponentBase::AsRef<Viewable>();}
	//TransformRef GetTransform();
	
	HumanFormat		GetFormat(HumCtx) override {TODO}
	Human&			GetValue(HumCtx) override {TODO}
	
};
#endif

NAMESPACE_ECS_END

#endif
