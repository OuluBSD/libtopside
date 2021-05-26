#ifndef _AccelCore_Header_h_
#define _AccelCore_Header_h_

NAMESPACE_TOPSIDE_BEGIN


typedef enum {
	ACCTYPE_NULL,
	
} AcceleratorType;

class AcceleratorHeader :
	RTTIBase
{
	
public:
	RTTI_DECL0(AcceleratorHeader)
	
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
	void				SetHeader(const AcceleratorHeader& in);
	void				CopyIdStream(const AcceleratorHeader& in);
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
	bool				IsEqualHeader(const AcceleratorHeader& in) const;
	String				ToString() const {return GetTypeString() + " (id: " + IntStr(id) + ")";}
	
	static String		GetStringFromType(Type i);
	static String		GetStringFromFilter(int i);
	static String		GetStringFromWrap(int i);
	static Type			GetTypeFromString(String typestr);
	static int			GetFilterFromString(String s);
	static int			GetWrapFromString(String s);
	static bool			IsTypeComponentSource(Type i);
	
};

struct AcceleratorHeaderVector {
	Array<AcceleratorHeader> in;
	
	int Find(const AcceleratorHeader& a) const;
	void Add(const AcceleratorHeader& a);
};

NAMESPACE_TOPSIDE_END

#endif
