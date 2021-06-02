#ifndef _AccelCore_Header_h_
#define _AccelCore_Header_h_

NAMESPACE_TOPSIDE_BEGIN

template <class Dev>
class AccelComponentStream :
	public ScopeValDevMachT<Dev>::Stream
{
	RTTI_DECL0(AccelComponentStream)
	
public:
	using Ctx = typename Dev::Value;
	using Format = typename Ctx::Format;
	using Value = typename ScopeValDevMachT<Dev>::Value;
	
	Format fmt;
	
public:
	
	AccelComponentStream() {}
	
	void						FillBuffer() override {}
	void						DropBuffer() override {}
	Value&						Get() override {TODO}
	int							GetActiveFormatIdx() const override {return 0;}
	int							GetFormatCount() const override {return 1;}
	Format						GetFormat(int i) const override {ASSERT(!i); return fmt;}
	bool						FindClosestFormat(const Format&, int& idx) override {return 0;}
	void						Clear() {fmt.Clear();}
	
	bool						IsOpen() const override {TODO}
	bool						Open(int fmt_idx) override {TODO}
	void						Close() override {TODO}
	
};


#define IFACE(x) using AccelComponent##x##Stream = AccelComponentStream<Accel##x##Spec>;
IFACE_LIST
#undef IFACE







typedef enum {
	ACCTYPE_NULL,
	
} AcceleratorType;

class AcceleratorHeader :
	RTTIBase
{
	
public:
	RTTI_DECL0(AcceleratorHeader)
	
	
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
	AccelComponentVideoStream* vstream = 0;
	AccelComponentAudioStream* astream = 0;
	String filepath;
	int id = -1;
	Type type = TYPE_INVALID;
	Wrap wrap = WRAP_REPEAT;
	Filter filter = FILTER_LINEAR;
	bool vflip = 0;
	
	
public:
	
	void				Set(int id, Type t, String path, Filter filter, Wrap wrap, bool vflip);
	void				Set(AccelComponentVideoStream* v, AccelComponentAudioStream* a) {ASSERT(v || a); vstream = v; astream = a;}
	void				SetHeader(const AcceleratorHeader& in);
	void				CopyIdStream(const AcceleratorHeader& in);
	void				SetType(Type t) {type = t;}
	void				SetId(int i) {id = i;}
	void				SetPath(String s) {filepath = s;}
	
	AccelComponentVideoStream*		GetVideo() const {return vstream;}
	AccelComponentAudioStream*		GetAudio() const {return astream;}
	
	int					GetId() const {return id;}
	Type				GetType() const {return type;}
	String				GetPath() const {return filepath;}
    String				GetTypeString() const {return GetStringFromType(type);}
	bool				IsTypeComponentSource() {return IsTypeComponentSource(type);}
	bool				IsTypeEmpty() const {return type == TYPE_EMPTY;}
	bool				IsEqualHeader(const AcceleratorHeader& in) const;
	String				ToString() const {return GetTypeString() + " (id: " + IntStr(id) + ")";}
	String				GetFilterString() const {return GetStringFromFilter(filter);}
	String				GetWrapString() const {return GetStringFromWrap(wrap);}
	
	static String		GetStringFromType(Type i);
	static String		GetStringFromFilter(Filter i);
	static String		GetStringFromWrap(Wrap i);
	static Type			GetTypeFromString(String typestr);
	static Filter		GetFilterFromString(String s);
	static Wrap			GetWrapFromString(String s);
	static bool			IsTypeComponentSource(Type i);
	
};


struct AcceleratorHeaderVector {
	Array<AcceleratorHeader> in;
	
	int Find(const AcceleratorHeader& a) const;
	void Add(const AcceleratorHeader& a);
};



class AccelContextComponent;
using AccelContextComponentRef		= Ref<AccelContextComponent,		RefParent1<Entity>>;

class AccelComponentGroup;
using AccelComponentGroupRef		= Ref<AccelComponentGroup,			RefParent1<AccelContextComponent>>;

NAMESPACE_TOPSIDE_END

#endif
