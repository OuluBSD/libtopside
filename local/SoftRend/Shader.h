#ifndef _SoftRend_Shader_h_
#define _SoftRend_Shader_h_

NAMESPACE_PARALLEL_BEGIN


template <class Backend>
class SoftProgramT;


template <class Backend>
struct SoftShaderLibraryT {
	typedef SoftShaderBaseT<Backend>* (*ShaderFactory)();
	typedef BinderIfaceVideo* (*VideoBinderFactory)();
	
	static VectorMap<String, VideoBinderFactory>& GetBinders();
	static VectorMap<String, ShaderFactory>& GetMap(int i);
	
	template <class T>
	static void AddShaderClass(GVar::ShaderType type, String key) {
		ASSERT(GetMap(type).Find(key) < 0);
		GetMap(type).Add(key, &CreateShader<T>);
	}
	
	template <class T> static SoftShaderBaseT<Backend>* CreateShader() {return new T();}
	template <class T> static BinderIfaceVideo* CreateBinder() {return new T();}
	
	template <class T>
	static void AddProgramClass(String key) {
		ASSERT(GetBinders().Find(key) < 0);
		GetBinders().Add(key, &CreateBinder<T>);
	}
	
};

template <class Backend>
class SoftShaderT {
	bool inited = false;
	GVar::ShaderType type;
	String src;
	String err;
	SoftShaderBaseT<Backend>* s = 0;
	
protected:
	using SoftProgram = SoftProgramT<Backend>;
	
	SoftProgram* prog = 0;
	
public:
	typedef SoftShaderT CLASSNAME;
	SoftShaderT();
	
	void Clear();
	bool Create(GVar::ShaderType t);
	
	void SetSource(String s);
	GVar::ShaderType GetType() const {return type;}
	SoftShaderBaseT<Backend>& Get() {ASSERT(s); return *s;}
	
	void operator=(SoftShaderBaseT<Backend>& s) {this->s = &s;}
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	String GetLastError() const {return err;}
	
	SoftProgram* GetSoftProgram() const {return prog;}
	void SetSoftProgram(SoftProgram* p) {prog = p;}
	
};


NAMESPACE_PARALLEL_END

#endif
