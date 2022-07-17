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
	//VectorMap<int,NatTex> tex;
	uint32 element_count = 0;
	NatVertexArray vao;
	NatVertexBuffer vbo;
	NatElementBuffer ebo;
	
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
	int tex_filter[TEXTYPE_COUNT];
	
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
	int env_material = -1; // own material
	int env_material_model = -1; // other model in same DataState
	int prog = -1;
	
	ModelStateT();
	~ModelStateT();
	
	void Free();
	void Clear();
	
	DataObject& AddObject();
	GfxDataObject& CreateObject() override {return AddObject();}
	int GetObjectCount() const override {return objects.GetCount();}
	GfxDataObject& GetObject(int i) override {return objects[i];}
	Material& GetAddMaterial(int material_id);
	Material& AddMaterial();
	bool SetProgram(String name);
	
	void Refresh(Model& m) override;
	bool LoadModel(ModelLoader& l) override;
	bool LoadModel(ModelLoader& l, String path) override;
	bool LoadModelTextures(ModelLoader& l) override;
	
protected:
	
	void ProcessNode(Model& model);
	void ProcessMaterials(Model& model);
	void ProcessMesh( Mesh& out);
	
	#ifdef flagASSIMP
	bool LoadModelAssimp(ModelLoader& l, String path);
    void RefreshTexture(Model& model);
    void RefreshTexture(Mesh& out);
    void ProcessMaterials(Model& model, const aiScene *scene);
    void ProcessNode(Model& model, aiNode *node, const aiScene *scene);
    void ProcessMesh(Model& mout, Mesh& out, aiMesh *mesh, const aiScene *scene);
    void ProcessMaterial(Model& mout, TS::Material& m, const aiMaterial *mat);
	#endif
	
	
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
	
	
	ArrayMap<int, ModelState> models;
	ArrayMap<int, PipelineState> pipelines;
	Index<String> dictionary;
	
	DataStateT();
	~DataStateT();
	
	ModelState& AddModelT();
	GfxModelState& AddModel() override {return AddModelT();}
	GfxModelState& GetModel(int i) override;
	PipelineState& GetAddPipeline(String name);
	
	int GetModelCount() const {return models.GetCount();}
	void Clear();
	
};





NAMESPACE_PARALLEL_END

#endif
