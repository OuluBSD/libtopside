#ifndef _TemplatesMach_DefAccel_h_
#define _TemplatesMach_DefAccel_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


typedef enum {
	ACCTYPE_NULL,
	
} AccelType;

class AccelHeader :
	RTTIBase
{
	
public:
	RTTI_DECL0(AccelHeader)
	
	enum {
		FILTER_NEAREST,
		FILTER_LINEAR,
		FILTER_MIPMAP,
		
		DEFAULT_FILTER = FILTER_LINEAR
	};
	
	enum {
		WRAP_CLAMP,
		WRAP_REPEAT,
		
		DEFAULT_WRAP = WRAP_REPEAT
	};
	
	typedef enum {
		INVALID = -1,
		EMPTY,
		BUFFER,
		KEYBOARD,
		TEXTURE,
		CUBEMAP,
		WEBCAM,
		MUSIC,
		MUSICSTREAM,
		VOLUME,
		VIDEO,
	} Type;
	
protected:
	VideoStream* stream = 0;
	String filepath;
	int id = -1;
	Type type = INVALID;
	int wrap = WRAP_REPEAT;
	int filter = FILTER_LINEAR;
	bool vflip = 0;
	
	
public:
	
	void				Set(int id, Type t, String path, int filter, int wrap, bool vflip);
	void				Set(int id, VideoStream* s) {this->id = id; stream = s;}
	void				SetHeader(const AccelHeader& in);
	void				CopyIdStream(const AccelHeader& in);
	void				SetType(Type t) {type = t;}
	void				SetId(int i) {id = i;}
	void				SetPath(String s) {filepath = s;}
	
	VideoStream*		GetVideo() const {return stream;}
	int					GetId() const {return id;}
	Type				GetType() const {return type;}
	String				GetPath() const {return filepath;}
    String				GetTypeString() const {return GetStringFromType(type);}
	bool				IsTypeComponentSource() {return IsTypeComponentSource(type);}
	bool				IsTypeEmpty() const {return type == EMPTY;}
	bool				IsEqualHeader(const AccelHeader& in) const;
	String				ToString() const {return GetTypeString() + " (id: " + IntStr(id) + ")";}
	
	static String		GetStringFromType(Type i);
	static String		GetStringFromFilter(int i);
	static String		GetStringFromWrap(int i);
	static Type			GetTypeFromString(String typestr);
	static int			GetFilterFromString(String s);
	static int			GetWrapFromString(String s);
	static bool			IsTypeComponentSource(Type i);
	
};

struct AccelHeaderVector {
	Array<AccelHeader> in;
	
	int Find(const AccelHeader& a) const;
	void Add(const AccelHeader& a);
};

class AccelStreamBase :
	RTTIBase
{
public:
	RTTI_DECL0(AccelStreamBase)
	virtual const AccelHeader& GetHeader() const = 0;
};

struct AccelFormat {
	static const int def_sample_rate = 1;
	
	AccelType type;
	
	void Clear() {type = ACCTYPE_NULL;}
	bool IsValid() const {return type != ACCTYPE_NULL;}
	
	bool operator!=(const AccelFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const AccelFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};


LOCAL_CTX(Accel, DummyValueBase, AccelStreamBase, DummyCustomSystemBase, DummyCustomSinkBase, DummyCustomPacketBase)
#define ACCCTX ((AccelContext*)0)
#define AccCtx AccelContext*


NAMESPACE_TOPSIDE_END

#endif
#endif
