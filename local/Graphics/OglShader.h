#ifndef _Graphics_OglShader_h_
#define _Graphics_OglShader_h_

NAMESPACE_TOPSIDE_BEGIN


struct OglFramebufferState;


struct OglFramebufferObject : FramebufferObject {
	RTTI_DECL1(OglFramebufferObject, FramebufferObject)
	
	OglFramebufferState& state;
	VectorMap<int,GLint> tex;
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    GLuint element_count = 0;
    mat4 view;
    mat4 proj;
    mat4 scale;
    mat4 model;
    bool is_global_proj = false;
    bool is_global_view = false;
    int id = -1;
    
    OglFramebufferObject(OglFramebufferState& state) : state(state) {}
    ~OglFramebufferObject() {FreeOgl();}
    void FreeOgl();
    void Paint() override;
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override;
    
    void Set(const mat4& model, const mat4& scale, const mat4* proj, const mat4* view) override;
    void SetModel(const mat4& m) override;
    void SetScale(const mat4& m) override;
    void SetProjection(const mat4& m) override;
    void SetView(const mat4& m) override;
    
	/*void SetBool(const String &name, bool value) const override;
	void SetInt(const String &name, int value) const override;
	void SetFloat(const String &name, float value) const override;
	void SetVec2(const String &name, const vec2 &value) const override;
	void SetVec3(const String &name, const vec3 &value) const override;
	void SetVec4(const String &name, const vec4 &value) const override;
	void SetMat2(const String &name, const mat2 &mat) const override;
	void SetMat3(const String &name, const mat3 &mat) const override;
	void SetMat4(const String &name, const mat4 &mat) const override;*/
	
};

struct OglInputState : FramebufferInputState {
	RTTI_DECL1(OglInputState, FramebufferInputState)
	
	const OglBuffer* in_buf = 0;
	
	
	/*void Free() {FramebufferInputState::Free();}
	void Reset() {memset(this, 0, sizeof(OglInputState));}
	void Default() {FramebufferInputState::Default(); id = -1;}
	void Clear() {Free(); Reset(); Default();}*/
};

struct OglShaderState : ShaderState {
	RTTI_DECL1(OglShaderState, ShaderState)
	
	GLuint	shader = -1;
	
	
	
	
	/*void Free() {ShaderState::Free();}
	void Reset() {memset(this, 0, sizeof(OglShaderState));}
	void Default() {ShaderState::Default(); prog = -1;}
	void Clear() {Free(); Reset(); Default();}*/
};

struct OglFramebufferState : FramebufferState {
	RTTI_DECL1(OglFramebufferState, FramebufferState)
	
	GLuint	color_buf[2] = {0,0};
	GLuint	depth_buf[2] = {0,0};
	GLuint	frame_buf[2] = {0,0};
	GLint	prog = -1;
	GLuint	pipeline = 0;
	bool	is_searched_vars = 0;
	GLint	var_idx[ShaderVar::VAR_COUNT];
	
	OglShaderState shaders[ShaderVar::PROG_COUNT];
	OglInputState inputs[ShaderVar::INPUT_COUNT];
	
	// objects
	Array<OglFramebufferObject>	objects;
	Vector<String> user_vars;
	
	
	OglFramebufferState() {memset(&var_idx, 0, sizeof(var_idx));}
	void SetCode(ShaderVar::Type t, const String& s) {shaders[t].code = s;}
	GLuint GetReadFramebuffer() const {return frame_buf[buf_i];}
	GLint GetGlType() const;
	GLint GetGlFormat() const;
	int GetGlSize() const;
	int GetGlSampleSize() const;
	
	/*void Free() {
		FramebufferState::Free();
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++) shaders[i].Free();
		for(int i = 0; i < ShaderVar::INPUT_COUNT; i++) inputs[i].Free();
		objects.Clear();
	}
	void Reset() {memset(this, 0, sizeof(OglFramebufferState));}
	void Default() {
		FramebufferState::Default();
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++) shaders[i].Default();
		for(int i = 0; i < ShaderVar::INPUT_COUNT; i++) inputs[i].Default();
	}
	void Clear() {Free(); Reset(); Default();}*/
};

class OglShader :
	public Shader,
	public ErrorReporter
{
	#if 0
	bool is_loaded = false;
	
	
    void BasicMeshRefresh(ModelMesh& model, Mesh& mesh);
    #endif
    
    OglFramebufferState& state;
    
    
public:
	OglShader(OglFramebufferState& s) : state(s) {}
	
	#if 0
	bool Load(String vertex_path, String fragment_path, String geometry_path = "") override;
	void SetLoaded(bool b=true) {is_loaded = true;}
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
	void SetVec2(const String &name, float x, float y) const override;
	void SetVec3(const String &name, float x, float y, float z) const override;
	void SetVec4(const String &name, float x, float y, float z, float w) const override;
	#endif
	
	FramebufferObject* CreateObject() override;
	
private:
	
	
	bool CheckCompileErrors(GLuint shader, String type);
	
};


NAMESPACE_TOPSIDE_END

#endif
