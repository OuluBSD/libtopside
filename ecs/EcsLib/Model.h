#ifndef _EcsLocal_Model_h_
#define _EcsLocal_Model_h_

NAMESPACE_ECS_BEGIN


typedef RTuple<Ref<ModelMesh>, TransformRef, RenderableRef> RendModel;
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
	One<ModelMesh> model;
	
	
	
};*/


class ModelComponent :
	public Component<ModelComponent>
{
	
public:
	RTTI_COMP0(ModelComponent);
	COMP_DEF_VISIT
	
	
	void Initialize() override;
	void Uninitialize() override;
    void operator=(const ModelComponent& src) {}
    
    bool Load(GfxDataState& state);
    bool LoadModel(String path);
    //void Refresh(Shader& shader);
    bool AddTextureFile(int mesh_i, TexType type, String path);
    void Dispatch() {TODO}
	Ref<ModelMesh> GetModel() {return loader.GetModel();}
    
	void GetModels(VectorRendModel& models);
	void Attach(ModelMesh* m) {loader.model = m;}
	/*void LoadModel(CpuDataState& state);
	void LoadModel(OglDataState& state);
	void RefreshModel(CpuDataState& state);
	void RefreshModel(OglDataState& state);*/
	
protected:
	ModelLoader loader;
	//CpuDataObject* cpu_obj = 0;
	//OglDataObject* ogl_obj = 0;
	
	
	
};

using ModelComponentRef = Ref<ModelComponent>;



NAMESPACE_ECS_END

#endif
