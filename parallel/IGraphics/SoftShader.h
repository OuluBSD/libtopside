#ifndef _SoftRend_Shader_h_
#define _SoftRend_Shader_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class SoftProgramT;


template <class Gfx>
struct SoftShaderLibraryT {
	typedef SoftShaderBaseT<Gfx>* (*ShaderFactory)();
	typedef BinderIfaceVideo* (*VideoBinderFactory)();
	
	static VectorMap<String, VideoBinderFactory>& GetBinders();
	static VectorMap<String, ShaderFactory>& GetMap(int i);
	
	template <class T>
	static void AddShaderClass(GVar::ShaderType type, String key) {
		ASSERT(GetMap(type).Find(key) < 0);
		GetMap(type).Add(key, &CreateShader<T>);
	}
	
	template <class T> static SoftShaderBaseT<Gfx>* CreateShader() {return new T();}
	template <class T> static BinderIfaceVideo* CreateBinder() {return new T();}
	
	template <class T>
	static void AddProgramClass(String key) {
		ASSERT(GetBinders().Find(key) < 0);
		GetBinders().Add(key, &CreateBinder<T>);
	}
	
};

template <class Gfx>
class SoftShaderT {
	bool inited = false;
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
	bool Create(GVar::ShaderType t);
	
	void SetSource(String s);
	GVar::ShaderType GetType() const {return type;}
	SoftShaderBaseT<Gfx>& Get() {ASSERT(s); return *s;}
	
	void operator=(SoftShaderBaseT<Gfx>* s) {this->s = s;}
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	String GetLastError() const {return err;}
	
	SoftProgram* GetSoftProgram() const {return prog;}
	void SetSoftProgram(SoftProgram* p) {prog = p;}
	
};


NAMESPACE_PARALLEL_END

#endif
