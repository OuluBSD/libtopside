#ifndef _GRAPHICS_CpuShader_h_
#define _GRAPHICS_CpuShader_h_

NAMESPACE_TOPSIDE_BEGIN

struct CpuFramebufferState;

struct CpuFramebufferObject : FramebufferObject {
	RTTI_DECL1(CpuFramebufferObject, FramebufferObject)
	
	CpuFramebufferState& state;
    int id = -1;
	
	
	CpuFramebufferObject(CpuFramebufferState& s) : state(s) {type = SW;}
	
	
	
    void Paint() override;
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override;
    
    void Set(const mat4& model, const mat4& scale, const mat4* proj, const mat4* view) override;
    void SetModel(const mat4& m) override;
    void SetScale(const mat4& m) override;
    void SetProjection(const mat4& m) override;
    void SetView(const mat4& m) override;
};

struct CpuFramebufferState : FramebufferState {
	RTTI_DECL1(CpuFramebufferState, FramebufferState)
	
	// objects
	Array<CpuFramebufferObject>	objects;
	Vector<String> user_vars;
	
	
	FramebufferObject& NewObject() override;
	
};

class CpuShader :
	public Shader,
	public ErrorReporter
{
	bool is_loaded = false;
	
    void BasicMeshRefresh(ModelMesh& model, Mesh& mesh);
    
public:
	CpuShader(CpuFramebufferState& s) : state(s) {}
	
	CpuFramebufferState& state;
	
	
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
	
	FramebufferObject* CreateObject() override;
	
private:
	
};


NAMESPACE_TOPSIDE_END

#endif
