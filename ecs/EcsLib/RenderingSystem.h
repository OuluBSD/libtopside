#ifndef _EcsLib_RenderingSystem_h_
#define _EcsLib_RenderingSystem_h_

NAMESPACE_ECS_BEGIN


class Renderable : public Component<Renderable> {
	
public:
	RTTI_COMP0(Renderable)
	COMP_DEF_VISIT
	
	
	RGBA color;
	mat4 offset;
	float alpha_multiplier;
	//String model_name;
	//Ref<ModelComponent> model;
	
	
	void Initialize() override;
	void Uninitialize() override;
	
	void ResetModel(mat4 offset = zero<mat4>()) {
		color = RGBAZero();
		this->offset = offset;
		alpha_multiplier = 0;
		//model_name = name;
		//model.Clear();
	}
	
    void operator=(const Renderable& e) {
        color = e.color;
        offset = e.offset;
        alpha_multiplier = e.alpha_multiplier;
    }
    
	Callback cb;
	//Model* GetModel() {return model ? model->GetModel() : 0;}
	
	
};

using RenderableRef = Ref<Renderable>;



class RenderingSystem :
	public System<RenderingSystem>
{
	OglBufferT* buf = 0;
	Array<RenderableRef> rends;
	Array<ViewableRef> views;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    void Render(GfxDataState& data);
    
    
public:
	using Base = System<RenderingSystem>;
	RTTI_DECL1(RenderingSystem, Base)
    ECS_SYS_CTOR(RenderingSystem)
	SYS_DEF_VISIT
	
	void AddViewable(ViewableRef v);
	void AddRenderable(RenderableRef b);
	void RemoveViewable(ViewableRef v);
	void RemoveRenderable(RenderableRef b);
	void Attach(String key, OglBufferT* b);
	
};

using RenderingSystemRef = Ref<RenderingSystem>;


NAMESPACE_ECS_END

#endif
