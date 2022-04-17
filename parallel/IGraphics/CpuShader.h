#ifndef _IGraphics_CpuShader_h_
#define _IGraphics_CpuShader_h_

#if 0

NAMESPACE_PARALLEL_BEGIN

struct CpuFramebufferState;

struct CpuDataObject : GfxDataObject {
	RTTI_DECL1(CpuDataObject, GfxDataObject)
	
	CpuFramebufferState& state;
    int id = -1;
	
	
	CpuDataObject(CpuFramebufferState& s) : state(s) {type = SW;}
	
	
	
    void Paint() override;
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override;
    
    /*void Set(const mat4& model, const mat4& scale, const mat4* proj, const mat4* view) override;
    void SetModel(const mat4& m) override;
    void SetScale(const mat4& m) override;
    void SetProjection(const mat4& m) override;
    void SetView(const mat4& m) override;*/
};

struct CpuFramebufferState : FramebufferState {
	RTTI_DECL1(CpuFramebufferState, FramebufferState)
	
	// objects
	Array<CpuDataObject>	objects;
	Vector<String> user_vars;
	
	
	GfxDataObject& CreateObject() override;
	
};

struct CpuVertexShaderArgs {
	CpuFramebufferState& state;
	CpuDataObject& obj;
	const vec3& pos;
	const vec3& normal;
	const vec2& tex_coords;
	vec4& pos_out;
	vec2& tex_coord_out;
};

class CpuShader :
	public GfxShader,
	public ErrorReporter
{
	bool is_loaded = false;
	
    void BasicMeshRefresh(ModelMesh& model, Mesh& mesh);
    
public:
	RTTI_DECL1(CpuShader, Shader)
	CpuShader() {}
	CpuShader(CpuFramebufferState& s) : state(&s) {}
	
	CpuFramebufferState* state = 0;
	
	void SetState(CpuFramebufferState& s) {state = &s;}
	
	/*
	bool Load(String vertex_path, String fragment_path, String geometry_path = "") override;
	bool IsLoaded() const override {return is_loaded;}
	void Refresh(ModelMesh& model) override;
    void Refresh(ModelMesh& model, Mesh& mesh) override;
	void Use() override;
	
	void SetBool(const String &name, bool value) const override;
	void SetInt(const String &name, int value) const override;
	void SetFloat(const String &name, float value) const override;
	void SetVec2(const String &name, const vec2 &value) const override;
	void SetVec3(const String &name, const vec3 &value) const override;
	void SetVec4(const String &name, const vec4 &value) const override;
	void SetMat2(const String &name, const mat2 &mat) const override;
	void SetMat3(const String &name, const mat3 &mat) const override;
	void SetMat4(const String &name, const mat4 &mat) const override;
	*/
	
	GfxDataObject* CreateObject() override;
	
	virtual void Process(CpuVertexShaderArgs& args) {Panic("not implemented");}
	virtual void Process(CpuFramebufferState& state) {Panic("not implemented");}
	
private:
	
};

class CpuShaderPipeline :
	public ShaderPipeline
{
	
public:
	CpuFramebufferState* state = 0;
	CpuShader* stages[GVar::SHADERTYPE_COUNT];
	
public:
	RTTI_DECL1(CpuShaderPipeline, ShaderPipeline)
	
	CpuShaderPipeline();
	
	void Clear();
	void LoadState(CpuFramebufferState& state);
	void AppendState(CpuFramebufferState& state);
	void SetVertex(CpuShader& s) {stages[GVar::VERTEX_SHADER] = &s;}
	void SetFragment(CpuShader& s) {stages[GVar::FRAGMENT_SHADER] = &s;}
	
};

NAMESPACE_PARALLEL_END

#endif
#endif
