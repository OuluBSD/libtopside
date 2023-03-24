#ifndef _SoftRend_Shader_h_
#define _SoftRend_Shader_h_

NAMESPACE_TOPSIDE_BEGIN



struct SoftProgram;



struct DummySoftShaderLibrary {
	typedef SoftShaderBase* (*ShaderFactory)();
	
	static VectorMap<String, ShaderFactory>& GetMap(int i) {ASSERT(i >= 0 && i < GVar::SHADERTYPE_COUNT); static VectorMap<String, ShaderFactory> m[GVar::SHADERTYPE_COUNT]; return m[i];}
	
};


struct SoftShaderLibrary {
	typedef SoftShaderBase* (*ShaderFactory)();
	
	static VectorMap<String, ShaderFactory>& GetMap(int i);// {ASSERT(i>=0&&i<GL::SHADERTYPE_COUNT); static VectorMap<String, ShaderFactory> m[GL::SHADERTYPE_COUNT]; return m[i];}
	
	template <class T>
	static void AddShaderClass(GVar::ShaderType type, String key) {
		ASSERT(GetMap(type).Find(key) < 0);
		GetMap(type).Add(key, &CreateShader<T>);
	}
	
	template <class T> static SoftShaderBase* CreateShader() {return new T();}
	
	
};


struct GfxProgramLibrary {
	typedef BinderIfaceVideo* (*VideoBinderFactory)();
	static VectorMap<String, VideoBinderFactory>& GetBinders() {static VectorMap<String, VideoBinderFactory> m; return m;}
	template <class T> static BinderIfaceVideo* CreateBinder() {return new T();}
	
	template <class T>
	static void AddProgramClass(String key) {
		ASSERT(GetBinders().Find(key) < 0);
		GetBinders().Add(key, &CreateBinder<T>);
	}
	
};


class SoftShader {
	GVar::ShaderType type;
	String src;
	String err;
	One<SoftShaderBase> s;
	
protected:
	SoftProgram* prog = 0;
	
public:
	typedef SoftShader CLASSNAME;
	SoftShader();
	
	void Clear();
	void SetType(GVar::ShaderType t) {type = t;}
	
	void SetSource(String s);
	GVar::ShaderType GetType() const {return type;}
	SoftShaderBase& Get() {ASSERT(s); return *s;}
	
	void SetShaderBase(SoftShaderBase* s) {this->s = s;}
	String GetLastError() const {return err;}
	
	SoftProgram* GetSoftProgram() const {return prog;}
	void SetSoftProgram(SoftProgram* p) {prog = p;}
	
	void SetPassthroughVertexShader(SoftProgram& p, SoftShaderBase* s) {prog = &p; type = GVar::VERTEX_SHADER; this->s = s;};
	
};


NAMESPACE_TOPSIDE_END

#endif
