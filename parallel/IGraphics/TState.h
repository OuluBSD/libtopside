#ifndef _IGraphics_TState_h_
#define _IGraphics_TState_h_

NAMESPACE_PARALLEL_BEGIN

template <class Gfx> struct DataStateT;


template <class Gfx>
struct DataObjectT : GfxDataObject {
	using Base = DataObjectT<Gfx>;
	RTTI_DECL1(DataObjectT, GfxDataObject)
	
	using DataState = DataStateT<Gfx>;
	using NatTex = typename Gfx::NativeTexture;
	using NatVertexArray = typename Gfx::NativeVertexArray;
	using NatVertexBuffer = typename Gfx::NativeVertexBuffer;
	using NatElementBuffer = typename Gfx::NativeElementBuffer;
	using DataStateBase = DataStateT<Gfx>;
	
	DataStateBase* state = 0;
	//VectorMap<int,NatTex> tex;
	uint32 element_count = 0;
	NatVertexArray vao;
	NatVertexBuffer vbo;
	NatElementBuffer ebo;
	
    int id = -1;
	
	
	DataObjectT();
	~DataObjectT();
	void SetState(DataStateBase* state) {this->state = state;}
	void Refresh(Mesh& m) override;
	void RefreshTexture(Mesh& m) override;
    void Free();
    void Paint(DataState& state);
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override {TODO}
    
    GVar::GfxType GetGfxType() const override {return Gfx::Type;}
	
};

template <class Gfx> struct ShaderStateT;
template <class Gfx> struct InputStateT;
template <class Gfx> struct FramebufferT;

template <class Gfx>
struct DataStateT : GfxDataState {
	RTTI_DECL1(DataStateT, GfxDataState)
	using Base = DataStateT<Gfx>;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	using NativeDepthBufferRef = typename Gfx::NativeDepthBufferRef;
	using NativeFrameBufferRef = typename Gfx::NativeFrameBufferRef;
	using NativeProgram  = typename Gfx::NativeProgram;
	using NativePipeline = typename Gfx::NativePipeline;
	using NativeShaderRef   = typename Gfx::NativeShaderRef;
	//using ShaderState = typename Gfx::ShaderState;
	using ShaderState = ShaderStateT<Gfx>;
	//using InputState  = typename Gfx::InputState;
	using InputState  = InputStateT<Gfx>;
	using DataObject  = typename Gfx::DataObject;
	using Framebuffer = FramebufferT<Gfx>;
	
	
	Array<DataObject> objects;
	Array<NativeColorBufferRef> textures;
	
	DataStateT();
	~DataStateT();
	DataObject& AddObject();
	GfxDataObject& CreateObject() override {return AddObject();}
	int GetObjectCount() const override {return objects.GetCount();}
	GfxDataObject& GetObject(int i) override {return objects[i];}
	
	void Free();
	void Refresh(ModelMesh& m) override {TODO}
	bool LoadModel(ModelLoader& l) override;
	bool LoadModel(ModelLoader& l, String path) override;
	bool LoadModelTextures(ModelLoader& l) override;
	
protected:
	
	void ProcessNode(/*GfxDataObject& o,*/ ModelMesh& model);
	void ProcessMesh(/*GfxDataObject& o, ModelMesh& mout,*/ Mesh& out);
	
	#ifdef flagASSIMP
	bool LoadModelAssimp(ModelLoader& l, String path);
    void RefreshTexture(ModelMesh& model);
    void RefreshTexture(Mesh& out);
    void ProcessNode(ModelMesh& model, aiNode *node, const aiScene *scene);
    void ProcessMesh(ModelMesh& mout, Mesh& out, aiMesh *mesh, const aiScene *scene);
    void LoadMaterialTextures(ModelMesh& mout, Mesh& out, aiMaterial *mat, int type);
	#endif
	
};





NAMESPACE_PARALLEL_END

#endif
