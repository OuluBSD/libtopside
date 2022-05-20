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


struct Viewport : public Component<Viewport> {
	RTTI_COMP0(Viewport)
	COMP_DEF_VISIT
	
	
	vec3 target = zero<vec3>();
	double fov = 90;
	double angle = 0;
	
	
	vec3 GetTarget() const {return target;}
	void SetTraget(const vec3& v) {target = v;}
	
	void operator=(const Viewport& vp) {
		target = vp.target;
	}
	
};


class ChaseCam :
	public Component<ChaseCam>
{
	TransformRef trans;
	TransformRef target;
	ViewableRef viewable;
	ViewportRef vport;
	
	mat4 look;
	mat4 view;
	mat4 projection;
	vec2 viewport_sz;
	
	bool test_log = false;
	
public:
	typedef ChaseCam CLASSNAME;
	RTTI_COMP0(ChaseCam)
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ComponentT>(this); vis & target & viewable & vport;}
	void Initialize() override;
	void Uninitialize() override;
	void Update(double dt) override;
	bool Arg(String key, Object value) override;
	void Refresh(GfxDataState& s);
	
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
		t->position[2] = 10.0;
		t->position[1] = 3.0;
		
        return components;
    }
};


NAMESPACE_ECS_END

#endif
