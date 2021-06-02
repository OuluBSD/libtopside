#ifndef _TemplatesMach_DevClasses_h_
#define _TemplatesMach_DevClasses_h_

NAMESPACE_TOPSIDE_BEGIN

struct CenterComponentGroupBase {};
struct NetComponentGroupBase {};
struct PermaComponentGroupBase {};

struct CenterComponentBase :
	RTTIBase,
	public RefScopeEnabler<CenterComponentBase, Entity>
{
	RTTI_DECL0(CenterComponentBase)
	String ToString() const {return String();}
};

struct NetComponentBase :
	RTTIBase,
	public RefScopeEnabler<NetComponentBase, Entity>
{
	RTTI_DECL0(NetComponentBase)
	String ToString() const {return String();}
};

struct PermaComponentBase :
	RTTIBase,
	public RefScopeEnabler<PermaComponentBase, Entity>
{
	RTTI_DECL0(PermaComponentBase)
	String ToString() const {return String();}
};

struct CenterComponentConfBase {};
struct NetComponentConfBase {};
struct PermaComponentConfBase {};

struct AccelComponentGroupBase {
	Vector<uint32> gl_stages;
	
};

struct AccelComponentConfBase {

	
	#define ACCEL_FILTER_LIST \
		ACCEL_FILTER_ITEM(FILTER_INVALID, "invalid") \
		ACCEL_FILTER_ITEM(FILTER_NEAREST, "nearest") \
		ACCEL_FILTER_ITEM(FILTER_LINEAR, "linear") \
		ACCEL_FILTER_ITEM(FILTER_MIPMAP, "mipmap")
	
	typedef enum {
		#define ACCEL_FILTER_ITEM(x,y) x,
		ACCEL_FILTER_LIST
		#undef ACCEL_FILTER_ITEM
		
		ACCEL_FILTER_COUNT,
		DEFAULT_FILTER = FILTER_LINEAR
	} Filter;
	
	
	#define ACCEL_WRAP_LIST \
		ACCEL_WRAP_ITEM(WRAP_INVALID, "invalid") \
		ACCEL_WRAP_ITEM(WRAP_CLAMP, "clamp") \
		ACCEL_WRAP_ITEM(WRAP_REPEAT, "repeat")
	
	typedef enum {
		#define ACCEL_WRAP_ITEM(x,y) x,
		ACCEL_WRAP_LIST
		#undef ACCEL_WRAP_ITEM
		
		ACCEL_WRAP_COUNT,
		DEFAULT_WRAP = WRAP_REPEAT
	} Wrap;
	
	
	#define ACCEL_TYPE_LIST \
		ACCEL_TYPE_ITEM(TYPE_INVALID, "invalid") \
		ACCEL_TYPE_ITEM(TYPE_EMPTY, "empty") \
		ACCEL_TYPE_ITEM(TYPE_BUFFER, "buffer") \
		ACCEL_TYPE_ITEM(TYPE_KEYBOARD, "keyboard") \
		ACCEL_TYPE_ITEM(TYPE_TEXTURE, "texture") \
		ACCEL_TYPE_ITEM(TYPE_CUBEMAP, "cubemap") \
		ACCEL_TYPE_ITEM(TYPE_WEBCAM, "webcam") \
		ACCEL_TYPE_ITEM(TYPE_MUSIC, "music") \
		ACCEL_TYPE_ITEM(TYPE_MUSICSTREAM, "musicstream") \
		ACCEL_TYPE_ITEM(TYPE_VOLUME, "volume") \
		ACCEL_TYPE_ITEM(TYPE_VIDEO, "video")
		
	typedef enum {
		#define ACCEL_TYPE_ITEM(x,y) x,
		ACCEL_TYPE_LIST
		#undef ACCEL_TYPE_ITEM
		ACCEL_TYPE_COUNT
	} Type;
	
	
	static const char* filter_names[ACCEL_FILTER_COUNT+1];
	static const char* wrap_names[ACCEL_WRAP_COUNT+1];
	static const char* type_names[ACCEL_TYPE_COUNT+1];
	
protected:
	String filepath;
	int id = -1;
	Type type = TYPE_INVALID;
	Wrap wrap = WRAP_REPEAT;
	Filter filter = FILTER_LINEAR;
	bool vflip = 0;

};


struct AccelComponentBase;
class ContextComponentBase;


struct TypeContextLoader {
	String last_error;
	
	void Clear() {last_error.Clear();}
	virtual bool Load(String path, Object& o, ContextComponentBase* b) = 0;
	
	Callback WhenError;
	
};

struct ContextComponentBase {
	typedef bool (*LoadFn)(String, Object&, ContextComponentBase*);
	using ExtLoaders = LinkedMap<String, LoadFn>;
	using DevLoaders = LinkedMap<TypeCls, ExtLoaders>;
	
	template <class T> static bool LoaderFn(String path, Object& o, ContextComponentBase* b) {return T().Load(path,o,b);}
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
