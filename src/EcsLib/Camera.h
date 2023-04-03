#ifndef _EcsLib_Camera_h_
#define _EcsLib_Camera_h_

NAMESPACE_ECS_BEGIN
using namespace Parallel;


class Viewable :
	public Component<Viewable>
{
	
public:
	RTTI_COMP0(Viewable)
	COMP_DEF_VISIT
	
	void Initialize() override;
	void Uninitialize() override;
	
	void operator=(const Viewable& c) {}
	
	
	Callback1<GfxShader&> cb;
	
};


class Viewport : public Component<Viewport> {
public:
	RTTI_COMP0(Viewport)
	COMP_DEF_VISIT
	
	
	vec3 target = zero<vec3>();
	double fov = M_PI/2;
	double angle = 0;
	
	
	vec3 GetTarget() const {return target;}
	void SetTraget(const vec3& v) {target = v;}
	
	bool Arg(String key, Object value) override;
	
	void operator=(const Viewport& vp) {
		target = vp.target;
	}
	
};


struct CameraBase :
	WeakRefScopeEnabler<CameraBase, Entity>,
	RTTIBase
{
	RTTI_DECL0(CameraBase)
	
	bool use_stereo = false;
	mat4 view_stereo[2];
	mat4 proj_stereo[2];
	mat4 mvp_stereo[2];
	
	CalibrationData calib;
	
	virtual bool Load(GfxDataState& state) = 0;
	virtual void UpdateCalibration() = 0;
	
};

class ChaseCam :
	public Component<ChaseCam>,
	public CameraBase
{
	TransformRef trans;
	TransformRef target;
	ViewableRef viewable;
	ViewportRef vport;
	
	mat4 view;
	mat4 projection;
	mat4 port;
	mat4 port_stereo;
	vec2 viewport_sz;
	
	bool test_log = false;
	double time = 0;
	double phase_time = 1.5;
	float fov = 110;
	float used_fov = 0;
	
	
	float GetUsedFov();
	
public:
	typedef ChaseCam CLASSNAME;
	RTTI_COMP1(ChaseCam, CameraBase)
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ComponentT>(this); vis & target & viewable & vport;}
	void Initialize() override;
	void Uninitialize() override;
	void Update(double dt) override;
	bool Arg(String key, Object value) override;
	bool Load(GfxDataState& state) override;
	void UpdateCalibration() override;
	
	void CheckUpdateProjection();
	void UpdateProjection();
	void UpdateView();
	void SetViewportSize(Size sz);
	void SetTarget(TransformRef tgt) {target = tgt;}
	
	void operator=(const ChaseCam& vp) {
		target = vp.target;
	}
};


struct CameraPrefab : EntityPrefab<Transform, Viewport, Viewable>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		TransformRef t = components.Get<TransformRef>();
		t->data.mode = TransformMatrix::MODE_POSITION;
		t->data.position[2] = 10.0;
		t->data.position[1] = 3.0;
		t->data.position[0] = 0.0;
		
        return components;
    }
};


NAMESPACE_ECS_END

#endif
