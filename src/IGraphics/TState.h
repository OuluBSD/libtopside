#ifndef _IGraphics_TState_h_
#define _IGraphics_TState_h_

NAMESPACE_PARALLEL_BEGIN

template <class Gfx> struct DataStateT;
template <class Gfx> struct ModelStateT;
template <class Gfx> struct PipelineStateT;


template <class Gfx>
struct DataObjectT : GfxDataObject {
	using Base = DataObjectT<Gfx>;
	RTTI_DECL1(DataObjectT, GfxDataObject)
	
	using DataState = DataStateT<Gfx>;
	using NatTex = typename Gfx::NativeTexture;
	using NatVertexArray = typename Gfx::NativeVertexArray;
	using NatVertexBuffer = typename Gfx::NativeVertexBuffer;
	using NatElementBuffer = typename Gfx::NativeElementBuffer;
	using ModelState = ModelStateT<Gfx>;
	
	ModelState* state = 0;
	uint32 element_count = 0;
	NatVertexArray vao;
	NatVertexBuffer vbo;
	NatElementBuffer ebo;
	Mesh* src = 0;
	
    int id = -1;
    int material = -1;
	
	DataObjectT();
	~DataObjectT();
	void SetState(ModelState* state) {this->state = state;}
	void Refresh(Mesh& m) override;
	void RefreshTexture(Mesh& m) override;
    void Free();
    void Paint(ModelState& state);
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override {TODO}
    
    GVar::GfxType GetGfxType() const override {return Gfx::Type;}
	
};

template <class Gfx> struct ShaderStateT;
template <class Gfx> struct InputStateT;
template <class Gfx> struct FramebufferT;

template <class Gfx>
struct MaterialT : GfxMaterial {
	RTTI_DECL1(MaterialT, GfxMaterial)
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	
	int id = -1;
	int tex_id[TEXTYPE_COUNT];
	GVar::Filter tex_filter[TEXTYPE_COUNT];
	
	MaterialT();
	
};

template <class Gfx>
struct ModelStateT : GfxModelState {
	RTTI_DECL1(ModelStateT, GfxModelState)
	using Base = ModelStateT<Gfx>;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	using NativeDepthBufferRef = typename Gfx::NativeDepthBufferRef;
	using NativeFrameBufferRef = typename Gfx::NativeFrameBufferRef;
	using DataObject  = typename Gfx::DataObject;
	using Material = MaterialT<Gfx>;
	using DataState = DataStateT<Gfx>;
	
	DataState* owner = 0;
	Array<DataObject> objects;
	ArrayMap<int, Material> materials;
	ArrayMap<int, NativeColorBufferRef> textures, cube_textures;
	int prog = -1;
	
	ModelStateT();
	~ModelStateT();
	
	void Free();
	
	DataObject& AddObject();
	GfxDataObject& CreateObject() override {return AddObject();}
	int GetObjectCount() const override {return objects.GetCount();}
	GfxDataObject& GetObject(int i) override {return objects[i];}
	Material& GetAddMaterial(int material_id);
	Material& AddMaterial();
	
	void Refresh(Model& m) override;
	bool LoadModel(ModelLoader& l) override;
	bool LoadModel(Model& m) override;
	bool LoadModelTextures(Model& m) override;
	void Clear() override;
	int GetMaterialKey(int i) const override;
	bool SetProgram(String name) override;
	
protected:
	
	void ProcessNode(Model& model);
	void ProcessMaterials(Model& model);
	void ProcessMesh( Mesh& out);
    void RefreshTexture(Model& model);
    void RefreshTexture(Mesh& out);
	
	
};

template <class Gfx>
struct DataStateT : GfxDataState {
	RTTI_DECL1(DataStateT, GfxDataState)
	using Base = DataStateT<Gfx>;
	using NativeProgram  = typename Gfx::NativeProgram;
	using NativePipeline = typename Gfx::NativePipeline;
	using NativeShaderRef   = typename Gfx::NativeShaderRef;
	using ShaderState = ShaderStateT<Gfx>;
	using InputState  = InputStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	using PipelineState = PipelineStateT<Gfx>;
	
	
	ArrayMap<hash_t, ModelState> models; // hash_t for "ptr hash"
	ArrayMap<int, PipelineState> pipelines;
	Index<String> dictionary;
	Vector<Base*> linked;
	int id_counter = 0;
	
	DataStateT();
	~DataStateT();
	
	ModelState& AddModelT();
	GfxModelState& RealizeModel(hash_t link) override;
	GfxModelState& AddModel() override {return AddModelT();}
	GfxModelState& GetModel(hash_t h) override;
	PipelineState& GetAddPipeline(String name);
	PipelineState* FindPipeline(String name);
	
	int GetModelCount() const override {return models.GetCount();}
	void Clear();
	
};





NAMESPACE_PARALLEL_END

#endif
