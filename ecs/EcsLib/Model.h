#ifndef _EcsLib_Model_h_
#define _EcsLib_Model_h_

NAMESPACE_OULU_BEGIN


void ModelDispatch(ComponentBase& b);


struct PrimitiveShape : public Component<PrimitiveShape>, public ModelSink {
	
	IFACE_CB(ModelSink);
	IFACE_GENERIC;
	
    void operator=(const PrimitiveShape& src) {}
    
	void SetShape(ShapeId type, const vec2& ax_vec);
	void Dispatch() {ModelDispatch(*this);}
	
protected:
	Shape2DWrapper shape;
	One<Model> model;
	
	void Signal() override;
	
	
};


struct ModelComponent : public Component<ModelComponent>, public ModelSink {
	
	IFACE_CB(ModelSink);
	IFACE_GENERIC;
	
	
    void operator=(const ModelComponent& src) {}
    
    bool LoadModel(String path);
    //void Paint(Shader& shader);
    bool AddTextureFile(int mesh_i, TexType type, String path);
    void Dispatch() {ModelDispatch(*this);}
	Ref<Model> GetModel() {return loader.GetModel();}
    
	void GetModels(VectorRendModel& models) override;
	
protected:
	ModelLoader loader;
	
	
	//void Signal() override;
	
	
};




NAMESPACE_OULU_END

#endif
