#ifndef _EcsLocal_Model_h_
#define _EcsLocal_Model_h_

NAMESPACE_ECS_BEGIN


typedef RTuple<Ref<Model>, TransformRef, RenderableRef> RendModel;
typedef Vector<RendModel> VectorRendModel;


/*struct PrimitiveShape :
	public Component<PrimitiveShape>,
	public ModelSink
{
	RTTI_COMP1(PrimitiveShape, ModelSink)
	
	COMP_DEF_VISIT
    void operator=(const PrimitiveShape& src) {}
    
	void SetShape(ShapeId type, const vec2& ax_vec);
	void Dispatch() {TODO}
	
protected:
	Shape2DWrapper shape;
	One<Model> model;
	
	
	
};*/


class ModelComponent :
	public Component<ModelComponent>
{
	
public:
	RTTI_COMP0(ModelComponent);
	COMP_DEF_VISIT
	
	
	void Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
    void operator=(const ModelComponent& src) {}
    
    bool Load(GfxDataState& state);
    bool LoadModel(String path);
    //void Refresh(Shader& shader);
    bool AddTextureFile(int mesh_i, TexType type, String path);
    void Dispatch() {TODO}
	Ref<Model> GetModel() {return loader.GetModel();}
    ModelLoader& GetLoader() {return loader;}
    
	void GetModels(VectorRendModel& models);
	void Attach(Model* m) {loader.model = m;}
	/*void LoadModel(CpuDataState& state);
	void LoadModel(OglDataState& state);
	void RefreshModel(CpuDataState& state);
	void RefreshModel(OglDataState& state);*/
	
	void SetPrefabModel(String prefab); // ResetModel
	
public:
	vec4 color = one<vec4>();
	String prefab_name;
	
	void SetRotation(float pitch, float yaw, float roll);
	void SetTranslation(const vec3& v);
	void SetScale(const vec3& v);
	void SetModelChanged() {model_changed = true;}
	
	void MakeCylinder(const vec3& pos, float radius, float length);
	
protected:
	ModelLoader loader;
	bool loaded = false;
	
	vec3 offset = zero<vec3>();
	vec3 scale = one<vec3>();
	float pitch = 0, yaw = 0, roll = 0;
	mat4 ext_model;
	bool have_ext_model = false;
	bool model_changed = false;
	//CpuDataObject* cpu_obj = 0;
	//OglDataObject* ogl_obj = 0;
	
	void RefreshExtModel();
	
	
};

using ModelComponentRef = Ref<ModelComponent>;



NAMESPACE_ECS_END

#endif
