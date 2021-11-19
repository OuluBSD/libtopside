#ifndef _EcsLib_RenderingSystem_h_
#define _EcsLib_RenderingSystem_h_

NAMESPACE_ECS_BEGIN


class RenderingSystem :
	public System<RenderingSystem>,
	public BinderIfaceOgl
{
	OglBuffer* buf = 0;
	Array<ComponentBaseRef> rends;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
	using Base = System<RenderingSystem>;
	RTTI_DECL2(RenderingSystem, Base, BinderIfaceOgl)
    ECS_SYS_CTOR(RenderingSystem)
	SYS_DEF_VISIT
	
	void AddRenderable(ComponentBaseRef b);
	void RemoveRenderable(ComponentBaseRef b);
	void Attach(String key, OglBuffer* b);
	
};

using RenderingSystemRef = Ref<RenderingSystem>;


NAMESPACE_ECS_END

#endif
