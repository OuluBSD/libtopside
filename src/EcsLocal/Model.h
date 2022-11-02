#ifndef _EcsLocal_Model_h_
#define _EcsLocal_Model_h_

NAMESPACE_ECS_BEGIN


typedef RTuple<Ref<ModelMesh>, TransformRef, RenderableRef> RendModel;
typedef Vector<RendModel> VectorRendModel;



class ModelComponent :
	public Component<ModelComponent>
{
public:
	RTTI_COMP0(ModelComponent);
	COMP_DEF_VISIT
	
	
    void operator=(const ModelComponent& src) {}
    
    bool LoadModel(String path);
    bool AddTextureFile(int mesh_i, TexType type, String path);
    void Dispatch() {TODO}
	Ref<ModelMesh> GetModel() {return loader.GetModel();}
    
	void GetModels(VectorRendModel& models);
	void Attach(ModelMesh* m) {loader.model = m;}
	void LoadModel(CpuDataState& state);
	void LoadModel(OglDataState& state);
	void RefreshModel(CpuDataState& state);
	void RefreshModel(OglDataState& state);
	
protected:
	ModelLoader loader;
	CpuDataObject* cpu_obj = 0;
	OglDataObject* ogl_obj = 0;
	
	
	
};


NAMESPACE_ECS_END

#endif
