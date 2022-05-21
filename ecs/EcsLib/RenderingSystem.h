#ifndef _EcsLocal_RenderingSystem_h_
#define _EcsLocal_RenderingSystem_h_

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


class VirtualGui;



class RenderingSystem :
	public System<RenderingSystem>
{
	
protected:
	friend class Ecs::VirtualGui;
	
	#ifdef flagSDL2
	Parallel::BufferT<SdlSwGfx>* sdl_sw_buf = 0;
	#ifdef flagOGL
	Parallel::BufferT<SdlOglGfx>* sdl_ogl_buf = 0;
	#endif
	#endif
	Array<RenderableRef> rends;
	Array<ViewableRef> views;
	Array<ModelComponentRef> models;
	Vector<CameraBase*> cams;
	
	//One<GfxDataState> state;
	GfxDataState* state = 0;
	
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
	void AddModel(ModelComponentRef m);
	void AddCamera(CameraBase& c);
	
	void RemoveViewable(ViewableRef v);
	void RemoveRenderable(RenderableRef b);
	void RemoveModel(ModelComponentRef m);
	void RemoveCamera(CameraBase& c);
	
	
	
	#ifdef flagSDL2
	void Attach(String key, Parallel::BufferT<SdlSwGfx>* b);
	#ifdef flagOGL
	void Attach(String key, Parallel::BufferT<SdlOglGfx>* b);
	#endif
	#endif
	
};

using RenderingSystemRef = Ref<RenderingSystem>;


NAMESPACE_ECS_END

#endif
