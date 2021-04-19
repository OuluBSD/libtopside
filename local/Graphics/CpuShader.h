#ifndef _GL_CpuShader_h_
#define _GL_CpuShader_h_

NAMESPACE_OULU_BEGIN

class CpuShader : public Shader {
	bool is_loaded = false;
	
    void BasicMeshPaint(Model& model, Mesh& mesh);
    
public:
	CpuShader() {}
	
	
	bool Load(String vertex_path, String fragment_path, String geometry_path = "") override;
	bool IsLoaded() const override {return is_loaded;}
	void Paint(Model& model) override;
    void Paint(Model& model, Mesh& mesh) override;
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
	
	
private:
	
};

NAMESPACE_OULU_END

#endif
