#ifndef _EcsLib_Camera_h_
#define _EcsLib_Camera_h_

NAMESPACE_TOPSIDE_BEGIN


class Viewable :
	public Component<Viewable>,
	public HumanSink
{
	vec3 target = zero<vec3>();
	
public:
	RTTI_COMP1(Viewable, HumanSink)
	VIS_COMP_0_1(Human)
	IFACE_CB(HumanSink);
	IFACE_GENERIC;
	void Visit(RuntimeVisitor& vis) override {}
	
	vec3 GetTarget() const {return target;}
	void SetTraget(const vec3& v) {target = v;}
	
	void operator=(const Viewable& c) {target = c.target;}
	
	//ViewableRef GetViewable() override {return ComponentBase::AsRef<Viewable>();}
	//TransformRef GetTransform();
	
	HumanFormat		GetFormat(HumCtx) override {TODO}
	Human&			GetValue(HumCtx) override {TODO}
	
};


NAMESPACE_TOPSIDE_END

#endif
