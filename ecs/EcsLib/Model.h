#ifndef _EcsLib_Model_h_
#define _EcsLib_Model_h_

NAMESPACE_TOPSIDE_BEGIN




struct PrimitiveShape :
	public Component<PrimitiveShape>,
	public ModelSink
{
	VIS_COMP_0_1(Model)
	IFACE_CB(ModelSink);
	IFACE_GENERIC;
	
	void Visit(RuntimeVisitor& vis) override {}
    void operator=(const PrimitiveShape& src) {}
    
	void SetShape(ShapeId type, const vec2& ax_vec);
	void Dispatch() {TODO}
	
protected:
	Shape2DWrapper shape;
	One<Model> model;
	
	
	
};


struct ModelComponent :
	public Component<ModelComponent>,
	public ModelSink
{
	VIS_COMP_0_1(Model)
	IFACE_CB(ModelSink);
	IFACE_GENERIC;
	
	
	void Visit(RuntimeVisitor& vis) override {}
    void operator=(const ModelComponent& src) {}
    
    bool LoadModel(String path);
    //void Paint(Shader& shader);
    bool AddTextureFile(int mesh_i, TexType type, String path);
    void Dispatch() {TODO}
	Ref<Model> GetModel() {return loader.GetModel();}
    
	void GetModels(VectorRendModel& models) override;
	
protected:
	ModelLoader loader;
	
	
	
	
};




NAMESPACE_TOPSIDE_END

#endif
