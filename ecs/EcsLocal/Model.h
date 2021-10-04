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
	COMP_DEF_VISIT
	
	
    void operator=(const ModelComponent& src) {}
    
    bool LoadModel(String path);
    //void Paint(Shader& shader);
    bool AddTextureFile(int mesh_i, TexType type, String path);
    void Dispatch() {TODO}
	Ref<ModelMesh> GetModel() {return loader.GetModel();}
    
	void GetModels(VectorRendModel& models);
	
	
protected:
	ModelLoader loader;
	
	
	
	
};


NAMESPACE_ECS_END

#endif
