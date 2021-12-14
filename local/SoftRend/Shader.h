#ifndef _SoftRend_Shader_h_
#define _SoftRend_Shader_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftProgram;


struct SoftShaderLibrary {
	typedef void (*FragmentShader)(vec4&, const vec2&);
	
	static VectorMap<String, FragmentShader> frag_shaders;
	
};

class SoftShader {
	bool inited = false;
	GVar::ShaderType type;
	String src;
	String err;
	SoftShaderLibrary::FragmentShader fs = 0;
	
protected:
	friend class SoftProgram;
	SoftProgram* prog = 0;
	
public:
	typedef SoftShader CLASSNAME;
	SoftShader();
	
	void Clear();
	bool Create(GVar::ShaderType t);
	
	void SetSource(String s);
	void SetTestShader(SoftShaderLibrary::FragmentShader fs);
	GVar::ShaderType GetType() const {return type;}
	SoftShaderLibrary::FragmentShader GetFragment() const {return fs;}
	
	void operator=(SoftShaderLibrary::FragmentShader fs) {SetTestShader(fs);}
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	String GetLastError() const {return err;}
	
};


NAMESPACE_TOPSIDE_END

#endif
