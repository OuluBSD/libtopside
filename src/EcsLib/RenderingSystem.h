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
	
	
	void Initialize() override;
	void Uninitialize() override;
	
	void ResetModel(mat4 offset = zero<mat4>()) {
		color = RGBAZero();
		this->offset = offset;
		alpha_multiplier = 0;
	}
	
    void operator=(const Renderable& e) {
        color = e.color;
        offset = e.offset;
        alpha_multiplier = e.alpha_multiplier;
    }
    
	Callback cb;
	
	
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
	Array<RenderableRef>		rends;
	Array<ViewableRef>			views;
	Array<ModelComponentRef>	models;
	Vector<CameraBase*>			cams;
	
	GfxDataState*				state = 0;
	double						time = 0;
	bool						is_dummy = false;
	
	// calibration
	CalibrationData				calib;
	
	//ArrayMap<String, ModelLoader> model_cache;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    bool Arg(String key, Object value) override;
    
    void Render(GfxDataState& data);
    
    
public:
	using Base = System<RenderingSystem>;
	RTTI_DECL1(RenderingSystem, Base)
    ECS_SYS_CTOR(RenderingSystem)
	SYS_DEF_VISIT
	
	//ModelRef GetAddModelFile(String path);
	
	void AddViewable(ViewableRef v);
	void AddRenderable(RenderableRef b);
	void AddModel(ModelComponentRef m);
	void AddCamera(CameraBase& c);
	
	void RemoveViewable(ViewableRef v);
	void RemoveRenderable(RenderableRef b);
	void RemoveModel(ModelComponentRef m);
	void RemoveCamera(CameraBase& c);
	
	void CalibrationEvent(CtrlEvent& ev);
	
	
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
