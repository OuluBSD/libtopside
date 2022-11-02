#ifndef _SoftRend_Shader_h_
#define _SoftRend_Shader_h_

NAMESPACE_TOPSIDE_BEGIN


struct SoftProgram;


struct SoftShaderLibrary {
	typedef SoftShaderBase* (*ShaderFactory)();
	
	static VectorMap<String, ShaderFactory> shader_classes[GVar::SHADERTYPE_COUNT];
	
	template <class T>
	static void AddShaderClass(GVar::ShaderType type, String key) {
		ASSERT(shader_classes[type].Find(key) < 0);
		shader_classes[type].Add(key, &CreateShader<T>);
	}
	template <class T>
	static SoftShaderBase* CreateShader() {return new T();}
};

class SoftShader {
	bool inited = false;
	GVar::ShaderType type;
	String src;
	String err;
	SoftShaderBase* s = 0;
	
protected:
	friend struct SoftProgram;
	SoftProgram* prog = 0;
	
public:
	typedef SoftShader CLASSNAME;
	SoftShader();
	
	void Clear();
	bool Create(GVar::ShaderType t);
	
	void SetSource(String s);
	GVar::ShaderType GetType() const {return type;}
	SoftShaderBase& Get() {ASSERT(s); return *s;}
	
	void operator=(SoftShaderBase& s) {this->s = &s;}
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	String GetLastError() const {return err;}
	
	
};


NAMESPACE_TOPSIDE_END

#endif
