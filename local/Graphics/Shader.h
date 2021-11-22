#ifndef _GRAPHICS_Shader_h_
#define _GRAPHICS_Shader_h_

NAMESPACE_TOPSIDE_BEGIN


class Shader {
	Vector<mat4> stack;
	
	
public:
	
	virtual ~Shader() {}
	
	void PushMultiplyMat4(String key, const mat4& mat);
	void PopMat4();
	void SetStackMat4(const mat4& mat);
	
	/*
	virtual bool Load(String vertex_path, String fragment_path, String geometry_path = "") = 0;
	virtual bool IsLoaded() const = 0;
	virtual void Refresh(ModelMesh& model) = 0;
    virtual void Refresh(ModelMesh& model, Mesh& mesh) = 0;
	virtual void Use() = 0;
	
	virtual void SetBool(const String &name, bool value) const = 0;
	virtual void SetInt(const String &name, int value) const = 0;
	virtual void SetFloat(const String &name, float value) const = 0;
	virtual void SetVec2(const String &name, const vec2 &value) const = 0;
	virtual void SetVec3(const String &name, const vec3 &value) const = 0;
	virtual void SetVec4(const String &name, const vec4 &value) const = 0;
	virtual void SetMat2(const String &name, const mat2 &mat) const = 0;
	virtual void SetMat3(const String &name, const mat3 &mat) const = 0;
	virtual void SetMat4(const String &name, const mat4 &mat) const = 0;
	
	virtual void SetVec2(const String &name, float x, float y) const {SetVec2(name, vec2(x,y));}
	virtual void SetVec3(const String &name, float x, float y, float z) const {SetVec3(name, vec3(x,y,z));}
	virtual void SetVec4(const String &name, float x, float y, float z, float w) const {SetVec4(name, vec4(x,y,z,w));}
	*/
	
	virtual FramebufferObject* CreateObject() = 0;
	
};




NAMESPACE_TOPSIDE_END

#endif
