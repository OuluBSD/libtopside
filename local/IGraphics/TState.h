#ifndef _IGraphics_TState_h_
#define _IGraphics_TState_h_

NAMESPACE_TOPSIDE_BEGIN

template <class Gfx> struct DataStateT;


template <class Gfx>
struct DataObjectT : GfxDataObject {
	using Base = DataObjectT<Gfx>;
	RTTI_DECL1(DataObjectT, GfxDataObject)
	
	using DataState = typename Gfx::DataState;
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

template <class Gfx>
struct DataStateT : GfxDataState {
	RTTI_DECL1(DataStateT, GfxDataState)
	using Base = DataStateT<Gfx>;
	using NativeColorBuffer = typename Gfx::NativeColorBuffer;
	using NatDepthBuf = typename Gfx::NativeDepthBuffer;
	using NatFrameBuf = typename Gfx::NativeFrameBuffer;
	using NatProgram  = typename Gfx::NativeProgram;
	using NatPipeline = typename Gfx::NativePipeline;
	using NatShader   = typename Gfx::NativeShader;
	using ShaderState = typename Gfx::ShaderState;
	using InputState  = typename Gfx::InputState;
	using DataObject  = typename Gfx::DataObject;
	using Framebuffer = typename Gfx::Framebuffer;
	
	
	Array<DataObject> objects;
	Array<NativeColorBuffer> textures;
	
	DataStateT();
	~DataStateT();
	DataObject& AddObject();
	GfxDataObject& CreateObject() override {return AddObject();}
	
	void Free();
	void Refresh(ModelMesh& m) override {TODO}
	bool LoadModel(ModelLoader& l, GfxDataObject& o) override;
	bool LoadModel(ModelLoader& l, DataObject& o, String path);
	bool LoadModelTextures(ModelLoader& l, GfxDataObject& o) override;
	
protected:
	
	void ProcessNode(GfxDataObject& o, ModelMesh& model);
	void ProcessMesh(GfxDataObject& o, ModelMesh& mout, Mesh& out);
	
	#ifdef flagASSIMP
	bool LoadModelAssimp(ModelLoader& l, DataObject& o, String path);
    void RefreshTexture(GfxDataObject& o, ModelMesh& model);
    void RefreshTexture(GfxDataObject& o, ModelMesh& model, Mesh& out);
    void ProcessNode(GfxDataObject& o, ModelMesh& model, aiNode *node, const aiScene *scene);
    void ProcessMesh(GfxDataObject& o, ModelMesh& mout, Mesh& out, aiMesh *mesh, const aiScene *scene);
    void LoadMaterialTextures(ModelMesh& mout, Mesh& out, aiMaterial *mat, int type);
	#endif
	
};





NAMESPACE_TOPSIDE_END

#endif
