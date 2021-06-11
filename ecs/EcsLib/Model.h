#ifndef _EcsLib_Model_h_
#define _EcsLib_Model_h_

NAMESPACE_TOPSIDE_BEGIN


typedef RTuple<Ref<ModelMesh>, TransformRef, RenderableRef> RendModel;
typedef Vector<RendModel> VectorRendModel;


/*struct PrimitiveShape :
	public Component<PrimitiveShape>,
	public ModelSink
{
	RTTI_COMP1(PrimitiveShape, ModelSink)
	VIS_COMP_0_1(Model)
	IFACE_CB(ModelSink);
	IFACE_GENERIC;
	
	COMP_DEF_VISIT
    void operator=(const PrimitiveShape& src) {}
    
	void SetShape(ShapeId type, const vec2& ax_vec);
	void Dispatch() {TODO}
	
protected:
	Shape2DWrapper shape;
	One<ModelMesh> model;
	
	
	
};*/


class ModelComponent :
	public Component<ModelComponent>,
	public ModelSink
{
public:
	RTTI_COMP1(ModelComponent, ModelSink)
	VIS_COMP_0_1(Model)
	IFACE_CB(ModelSink);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
    void operator=(const ModelComponent& src) {}
    
    bool LoadModel(String path);
    //void Paint(Shader& shader);
    bool AddTextureFile(int mesh_i, TexType type, String path);
    void Dispatch() {TODO}
	Ref<ModelMesh> GetModel() {return loader.GetModel();}
    
	void GetModels(VectorRendModel& models);
	
	ModelFormat		GetFormat(MdlCtx) override {TODO}
	Model&			GetValue(MdlCtx) override {TODO}
	
protected:
	ModelLoader loader;
	
	
	
	
};




NAMESPACE_TOPSIDE_END

#endif
