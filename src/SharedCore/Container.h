#ifndef _CoreAlt_Container_h_
#define _CoreAlt_Container_h_

NAMESPACE_UPP


#if 0
template <class T>
class Pick {
	T* var = NULL;
public:
	Pick(T& var) : var(&var) {}
	Pick(Pick&& p) : var(p.var) {p.var = NULL;}
	Pick(const Pick& p) : var(p.var) {}
	T& Get() const {return *var;}
};

template <class T> Pick<T> PickFn(T& o) {return Pick<T>(o);}

// The file is included in Topside and this is required to prevent regular U++ errors
#ifdef LIBTOPSIDE
template <class T> Pick<T> pick(T& o) {return Pick<T>(o);}
#endif
#endif


template <class T>
struct ManagedStatic {
	T o;
	bool destructed = false;
	const char* file;
	int line;
	
	typedef ManagedStatic CLASSNAME;
	ManagedStatic(const char* f, int l);
	template <class Arg> ManagedStatic(const char* f, int l, const Arg& value);
	~ManagedStatic() {
		#if IS_TS_CORE
		ASSERT(destructed);
		#endif
		Destruct();
	}
	void Destruct() {if (!destructed) {Clear(); destructed = true;}}
	void Clear() {o.Clear();}
};

template <class T>
struct ManagedStaticThreadLocal {
	T o;
	bool destructed = false;
	const char* file;
	int line;
	
	typedef ManagedStaticThreadLocal CLASSNAME;
	ManagedStaticThreadLocal(const char* f, int l);
	template <class Arg> ManagedStaticThreadLocal(const char* f, int l, const Arg& value);
	~ManagedStaticThreadLocal() {if (!destructed) Destruct();}
	void Destruct() {if (!destructed) {Clear(); destructed = true;}}
	void Clear() {o.Clear();}
};

#define MAKE_STATIC(t, x) static ::UPP::ManagedStatic<t> __##x(__FILE__,__LINE__); t& x = __##x.o;
#define MAKE_STATIC_(t, x, param) static ::UPP::ManagedStatic<t> __##x(__FILE__,__LINE__,param); t& x = __##x.o;
#define MAKE_STATIC_LOCAL(t, x) thread_local static ::UPP::ManagedStaticThreadLocal<t> __##x(__FILE__,__LINE__); t& x = __##x.o;

#undef RTTI_STRING_FN
#define RTTI_STRING_FN(TypeString) MAKE_STATIC_LOCAL(::UPP::String, s); s = TypeString; return s;


END_UPP_NAMESPACE

#endif
