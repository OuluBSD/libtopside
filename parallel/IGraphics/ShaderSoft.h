#ifndef _SoftRend_Shader_h_
#define _SoftRend_Shader_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class SoftProgramT;


template <class Gfx>
struct DummySoftShaderLibraryT {
	typedef SoftShaderBaseT<Gfx>* (*ShaderFactory)();
	
	static VectorMap<String, ShaderFactory>& GetMap(int i) {ASSERT(i >= 0 && i < GVar::SHADERTYPE_COUNT); static VectorMap<String, ShaderFactory> m[GVar::SHADERTYPE_COUNT]; return m[i];}
	
};

template <class Gfx>
struct SoftShaderLibraryT {
	typedef SoftShaderBaseT<Gfx>* (*ShaderFactory)();
	
	static VectorMap<String, ShaderFactory>& GetMap(int i);// {ASSERT(i>=0&&i<GL::SHADERTYPE_COUNT); static VectorMap<String, ShaderFactory> m[GL::SHADERTYPE_COUNT]; return m[i];}
	
	template <class T>
	static void AddShaderClass(GVar::ShaderType type, String key) {
		ASSERT(GetMap(type).Find(key) < 0);
		GetMap(type).Add(key, &CreateShader<T>);
	}
	
	template <class T> static SoftShaderBaseT<Gfx>* CreateShader() {return new T();}
	
	
};

template <class Gfx>
struct ShaderLibraryT {
	typedef BinderIfaceVideo* (*VideoBinderFactory)();
	static VectorMap<String, VideoBinderFactory>& GetBinders() {static VectorMap<String, VideoBinderFactory> m; return m;}
	template <class T> static BinderIfaceVideo* CreateBinder() {return new T();}
	
	template <class T>
	static void AddProgramClass(String key) {
		ASSERT(GetBinders().Find(key) < 0);
		GetBinders().Add(key, &CreateBinder<T>);
	}
	
};

template <class Gfx>
class SoftShaderT {
	GVar::ShaderType type;
	String src;
	String err;
	SoftShaderBaseT<Gfx>* s = 0;
	
protected:
	using SoftProgram = SoftProgramT<Gfx>;
	
	SoftProgram* prog = 0;
	
public:
	typedef SoftShaderT CLASSNAME;
	SoftShaderT();
	
	void Clear();
	void SetType(GVar::ShaderType t) {type = t;}
	
	void SetSource(String s);
	GVar::ShaderType GetType() const {return type;}
	SoftShaderBaseT<Gfx>& Get() {ASSERT(s); return *s;}
	
	void SetShaderBase(SoftShaderBaseT<Gfx>& s) {this->s = &s;}
	String GetLastError() const {return err;}
	
	SoftProgram* GetSoftProgram() const {return prog;}
	void SetSoftProgram(SoftProgram* p) {prog = p;}
	
	void SetPassthroughVertexShader(SoftProgram& p, SoftShaderBaseT<Gfx>& s) {prog = &p; type = GVar::VERTEX_SHADER; this->s = &s;};
	
};


NAMESPACE_PARALLEL_END

#endif
