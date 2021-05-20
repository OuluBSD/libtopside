#ifndef _EcsLib_Camera_h_
#define _EcsLib_Camera_h_

NAMESPACE_TOPSIDE_BEGIN


class Camerable :
	public Component<Camerable>,
	public HumanSink
{
	vec3 target = zero<vec3>();
	
public:
	VIS_COMP_0_1(Human)
	IFACE_CB(HumanSink);
	IFACE_GENERIC;
	void Visit(RuntimeVisitor& vis) override {}
	
	vec3 GetTarget() const {return target;}
	void SetTraget(const vec3& v) {target = v;}
	
	void operator=(const Camerable& c) {target = c.target;}
	
	CamerableRef GetCamerable() override {return ComponentBase::AsRef<Camerable>();}
	//TransformRef GetTransform();
	
	HumanFormat		GetFormat(HumCtx) override;
	Human&			GetValue(HumCtx) override;
	
};


NAMESPACE_TOPSIDE_END

#endif
