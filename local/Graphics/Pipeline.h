#ifndef _GL_Pipeline_h_
#define _GL_Pipeline_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


#define GFX_MESH_CULLING		"graphics.mesh.culling"

typedef enum {
	PIPELINE_INVALID,
	PIPELINE_CPU,
	PIPELINE_GPU,
	PIPELINE_GPGPU,
	RENDERER_FB,
} PipelineType;


NAMESPACE_TOPSIDE_END




NAMESPACE_TOPSIDE_BEGIN


struct Pipeline;
struct CpuPipelineData;




struct CpuPipelineThreadData {
	CpuPipelineData* data = NULL;
	CpuFramebuffer* fb = NULL;
	vec3 pos;
	RGBA frag_color;
	int thrd_i = -1;
	int model_i = -1, mesh_i = -1;
	uint32 vtx_offset = 0;
	uint32 tri_offset = 0;
	uint32 ctx_offset = 0;
	
	
	void Clear() {
		data = NULL;
		fb = NULL;
		ClearTemp();
	}
	void ClearTemp() {
		pos.Clear();
		model_i = -1, mesh_i = -1;
		vtx_offset = 0;
		tri_offset = 0;
		ctx_offset = 0;
	}
	
	void TestSetDepth(DepthValue& buf_value, float depth);
	
};




enum ShaderMode {
	SHDRMODE_COMPUTE,
	SHDRMODE_MESH_VERTEX,
	SHDRMODE_VERTEX,
	SHDRMODE_TRIANGLE,
	SHDRMODE_FRAGMENT
};

struct IShader {
	
	virtual ~IShader() = default;
	
	virtual ShaderMode GetMode() = 0;
	virtual String ToString() = 0;
	
	virtual void NativeShaderProcess(CpuPipelineThreadData& data) {Panic("Not implemented");}
	
};





template <class T> class PipelineView {

protected:
	Pipeline* pline = NULL;
	
public:
	
	
};


class MeshView : public PipelineView<MeshView> {
	
	
public:
	
	void SetSize(int triangles, bool has_texcoords, bool has_normals);
	
	void SetIndices(ivec3* data);
	void SetVertices(vec3* data);
	void SetTexCoords(vec2* data);
	void SetVertexNormals(vec3* data);
	
	
	int GetTriangles() const;
	bool HasTexCoords() const;
	bool HasNormals() const;
	
	void GetIndices(ivec3* data) const;
	void GetVertices(vec3* data) const;
	void GetTexCoords(vec2* data) const;
	void GetVertexNormals(vec3* data) const;
	
};

class ObjectView : public PipelineView<ObjectView> {
	
public:
	
	MeshView& CreateMesh();
	
};



struct PipelineData {
	
	virtual ~PipelineData() {}
	virtual PipelineType GetType() = 0;
	virtual int PutModel(One<Model>& model, bool can_pick) = 0;
	
};

struct PipelineNode {
	PipelineNode* down = NULL;
	ArrayMap<String, PipelineNode> branch;
	Array<IShader> shaders;
	
	void Clear();
	void SetStructure(Value v);
	PipelineNode& Add(String key);
	
	template<class T> T& AddShader() {T* o = new T(); shaders.Add(o); return *o;}
	
};



struct Pipeline {
	PipelineNode root;
	
	virtual ~Pipeline() = default;
	
	void Process();
	void SetOutput(Size sz);
	
	virtual ObjectView& CreateObject() = 0;
	virtual PipelineType GetType() = 0;
	virtual bool SetData(Shared<PipelineData> d) = 0;
	virtual bool SetFramebuffer(CpuFramebuffer& fb) {return false;}
	
	template <class T> T& Create(String path) {
		static_assert(std::is_base_of<IShader, T>(), "Shader is not the base class of T");
		PipelineNode* n = FindNode(path);
		if (!n) throw Exc("Couldn't find node in pipeline structure: " + path);
		shaders_changed = true;
		return n->AddShader<T>();
	}
	
	PipelineNode* FindNode(String path);
	
protected:
	friend class ObjectView;
	
	
	virtual MeshView& CreateMesh(ObjectView& o) = 0;
	
protected:
	Pipeline();
	
	void ParseStructureJson(String json);
	void SetStructure(Value v);
	
	virtual bool Begin() = 0;
	virtual void ProcessShaders() = 0;
	
	
	bool shaders_changed = false;
	
};





struct CpuStage : Moveable<CpuStage> {
	enum {
		FLAG_NEXT_CTX,
	};
	
	struct Triangle : Moveable<Triangle> {
		uint32 idx[3];
		mat23 tex;
		vec3 normal;
		int16 ctx_id;
		byte flags;
		
		void SetNextContext() {flags |= 1 << FLAG_NEXT_CTX;}
		bool IsNextContext() const {return flags & (1 << FLAG_NEXT_CTX);}
	};
	
	struct Context : Moveable<Context> {
		Material material;
		int model_i, mesh_i;
		int tex_id[TEXTYPE_COUNT];
	};
	
	
	Vector<Triangle> tri;
	Vector<Vertex> vert;
	Vector<Context> ctx;
	
	mat4 vport;
	mat4 lookat;
	mat4 persp;
	mat4 view;
	mat4 M, MIT;
	vec3 light_dir;
	
	vec3 M_light_dir, MIT_light_dir;
	
	void Reset();
	void operator=(const CpuStage& src);
	
	void SetViewport(const mat4& m) {vport = m;}
	void SetLookAt(const mat4& m) {lookat = m;}
	void SetPerspective(const mat4& m) {persp = m;}
	void SetLightDirection(const vec3& v) {light_dir = v;}
	void UpdateView();
	
	const mat4& GetViewport() const {return vport;}
	const mat4& GetLookAt() const {return lookat;}
	const mat4& GetPerspective() const {return persp;}
	const mat4& GetView() const {return view;}
	const Vertex& GetVertexSource(CpuPipelineThreadData& thrd) {return vert[thrd.vtx_offset];}
	Vertex& GetVertexDestination(CpuPipelineThreadData& thrd) {return vert[thrd.vtx_offset];}
	const Triangle& GetTriangleSource(CpuPipelineThreadData& thrd) {return tri[thrd.tri_offset];}
	Triangle& GetTriangleDestination(CpuPipelineThreadData& thrd) {return tri[thrd.tri_offset];}
	const Vertex& GetTriangleVertex(const Triangle& tri, int vert_i) {return vert[tri.idx[vert_i]];}
	
	
};



//struct CpuThreadPipelineData {};


struct CpuPipelineData : public PipelineData {
	ArrayMap<int, Model> models;
	int model_counter = 0;
	
	//Array<CpuThreadPipelineData> thrds;
	
	
	
	PipelineType GetType() override {return PIPELINE_CPU;}
	int PutModel(One<Model>& model, bool can_pick) override;
	
	void ResetThreads(int count) {}
	
	Array<CpuStage> stages;
	Array<CpuStage> prev_stages;
	Array<CpuStage> recyclable_stages;
	DepthBuffer depth_buf;
	
	
	
	void Begin();
	void BeginStage();
	CpuStage& GetCurrentStage() {return stages.Top();}
	DepthBuffer& GetDepthBuffer() {return depth_buf;}
	
};

struct CpuPipeline : public Pipeline {
	
	CpuPipeline();
	
	
	PipelineType GetType() override {return PIPELINE_CPU;}
	bool SetData(Shared<PipelineData> d) override;
	
protected:
	
	ObjectView& CreateObject() override;
	MeshView& CreateMesh(ObjectView& o) override;
	bool Begin() override;
	void ProcessShaders() override;
	bool SetFramebuffer(CpuFramebuffer& fb) override {this->fb = &fb; return true;}
	
	void UpdateShaders();
	void UpdateShaderVector(const Vector<String>& paths, Vector<IShader*>& out);
	
	void ProcessShaders(Vector<IShader*>& v);
	
	Vector<IShader*> compute, coarse, fine, geom, frag;
	Shared<CpuPipelineData> pdata;
	CpuPipelineThreadData thrd;
	CpuFramebuffer* fb = NULL;
	
};



/*struct GpuPipeline : public Pipeline {
	
	
	
};*/



NAMESPACE_TOPSIDE_END

#endif
#endif
