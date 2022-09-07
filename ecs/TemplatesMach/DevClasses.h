#ifndef _TemplatesMach_DevClasses_h_
#define _TemplatesMach_DevClasses_h_

NAMESPACE_TOPSIDE_BEGIN



#define DUMMY_DEV_LIST \
	DEV(Center) \
	DEV(Net) \
	DEV(Perma)

#define DEV(x) \
	struct x##ComponentGroupBase; \
	struct x##ComponentConfBase {}; \
	struct x##ComponentBase : \
		RTTIBase, \
		public RefScopeEnabler<x##ComponentBase, Entity> \
	{ \
		RTTI_DECL_R0(x##ComponentBase) \
		String ToString() const {return String();} \
		void Clear() {} \
		void Close() {} \
		void Process() {} \
		bool Open() {return false;} \
		bool CheckDevice() {return true;} \
		void UpdateCompFlags(TypeCls val_spec, int comp_i, int comp_count) {} \
		virtual bool RequiresDeviceProgram() const {return false;} \
	};
DUMMY_DEV_LIST
#undef DEV



class AccelComponentGroupBase;
struct AccelComponentConfBase;
struct AccelComponentBase;


struct ContextConnectorBase;


struct TypeContextLoader {
	String last_error;
	
	void Clear() {last_error.Clear();}
	virtual bool Load(String path, Object& o, ContextConnectorBase* b) = 0;
	
	Callback WhenError;
	
};

struct ContextConnectorBase :
	RTTIBase
{
	RTTI_DECL0(ContextConnectorBase)
	
	typedef bool (*LoadFn)(String, Object&, ContextConnectorBase*);
	using ExtLoaders = LinkedMap<String, LoadFn>;
	using DevLoaders = LinkedMap<TypeCls, ExtLoaders>;
	
	template <class T> static bool LoaderFn(String path, Object& o, ContextConnectorBase* b) {return T().Load(path,o,b);}
	template <class DevSpec> static ExtLoaders& GetExtLoaders() {static ExtLoaders l; return l;}
	template <class DevSpec> static Index<String>& GetDefaultExt() {static Index<String> i; return i;}
	
	
	template <class DevSpec, class T> static void Register(String file_ext) {
		auto& loaders = GetExtLoaders<DevSpec>();
		loaders.Add(file_ext, &LoaderFn<T>);
	}
	
	template <class DevSpec> static void RegisterDefaultFileExt(String file_ext) {
		GetDefaultExt<DevSpec>().FindAdd(file_ext);
	}
	
protected:
	String last_error;
	
	
public:
	
	Callback WhenError;
	
};


NAMESPACE_TOPSIDE_END

#endif
