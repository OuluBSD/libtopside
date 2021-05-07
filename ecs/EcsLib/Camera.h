#ifndef _EcsLib_Camera_h_
#define _EcsLib_Camera_h_

NAMESPACE_OULU_BEGIN


class Camerable : public Component<Camerable>, public CameraSink {
public:
	IFACE_CB(CameraSink);
	IFACE_GENERIC;
	
	vec3 target = zero<vec3>();
	
	void operator=(const Camerable& c) {target = c.target;}
	
	CamerableRef GetCamerable() override {return ComponentBase::AsRef<Camerable>();}
	TransformRef GetTransform() override;
	
};


NAMESPACE_OULU_END

#endif
