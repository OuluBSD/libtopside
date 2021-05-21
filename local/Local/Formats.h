#ifndef _Local_Formats_h_
#define _Local_Formats_h_

NAMESPACE_TOPSIDE_BEGIN


class Camerable;
class Transform;

using CamerableRef			= Ref<Camerable,			RefParent1<Entity>>;
using TransformRef			= Ref<Transform,			RefParent1<Entity>>;



struct AudioFormat {
	int freq = 0;
	int sample_rate = 0;
	int var_size = 0;
	int channels = 0;
	bool is_var_float = 0;
	bool is_var_signed = 0;
	bool is_var_bigendian = 0;
	
	bool IsValid() const {return var_size > 0 && sample_rate > 0 && channels > 0 && freq > 0;}
	bool IsCopyCompatible(const AudioFormat& fmt) const {
		return	var_size			== fmt.var_size &&
				channels			== fmt.channels &&
				is_var_float		== fmt.is_var_float &&
				is_var_signed		== fmt.is_var_signed &&
				is_var_bigendian	== fmt.is_var_bigendian;
	}
	bool IsPlaybackCompatible(const AudioFormat& fmt) const {
		return	freq				== fmt.freq &&
				IsCopyCompatible(fmt);
	}
	bool IsSame(const AudioFormat& fmt) const {
		return	sample_rate			== fmt.sample_rate &&
				IsCopyCompatible(fmt);
	}
	void Clear() {memset(this, 0, sizeof(AudioFormat));}
	bool operator!=(const AudioFormat& fmt) const {return !IsSame(fmt);}
	bool operator==(const AudioFormat& fmt) const {return IsSame(fmt);}
	
	int GetSampleSize() const {return var_size * channels;}
	int GetFrameSize() const {return var_size * channels * sample_rate;}
	int GetFrameSize(int dst_sample_rate) const {return var_size * channels * dst_sample_rate;}
	double GetFrameSeconds() const {return (double)sample_rate / (double)freq;}
	
	template <class T> bool IsSampleType() const {
		#if CPU_LITTLE_ENDIAN
		if (is_var_bigendian) return false;
		#else
		if (!is_var_bigendian) return false;
		#endif
		if (is_var_float != (std::is_same<T,float>() || std::is_same<T,double>())) return false;
		if (is_var_signed != (std::is_same<T,float>() || std::is_same<T,double>() || std::is_same<T,int>() || std::is_same<T,short>() || std::is_same<T,char>())) return false;
		return var_size == sizeof(T);
	}
};

LOCAL_CTX(Audio, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define AUDCTX ((AudioContext*)0)
#define AudCtx AudioContext*


struct VideoFormat {
	Size res = {0,0};
	int depth = 0; // volume video is a thing
	double fps = 0;
	int var_size = 0;
	int channels = 0;
	int pitch = 0;
	String codec;
	
	void	Clear();
	bool	IsValid() const {return res.cx > 0 && res.cy > 0 && depth > 0 && fps > 0 && var_size > 0 && channels > 0 && pitch >= GetMinPitch();}
	int		GetMinPitch() const {return res.cx * channels * var_size;}
	void	SetLinePadding(int bytes) {ASSERT(bytes >= 0); pitch = GetMinPitch() + bytes;}
	void	SetPitch(int bytes) {pitch = bytes; ASSERT(bytes >= GetMinPitch());}
	Size	GetSize() const {return res;}
	int		GetDepth() const {return depth;}
	int		GetFrameBytes() const {return res.cy * pitch;}
	bool	operator!=(const VideoFormat& fmt) const {return !(*this == fmt);}
	bool	operator==(const VideoFormat& fmt) const {
		return	res == fmt.res &&
				depth == fmt.depth &&
				fps == fmt.fps &&
				var_size == fmt.var_size &&
				channels == fmt.channels &&
				pitch == fmt.pitch &&
				codec == fmt.codec
				;
	}
	
};

VideoFormat MakeVideoFormat(Size res, double fps, int var_size, int channels, int pitch, int depth=1, String codec=String());


LOCAL_CTX(Video, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define VIDCTX ((VideoContext*)0)
#define VidCtx VideoContext*




struct MediaFormat {
	AudioFormat snd;
	VideoFormat vid;
	
	bool IsValid() const {return snd.IsValid() || vid.IsValid();}
	
	bool operator!=(const MediaFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const MediaFormat& fmt) const {
		return	snd		== fmt.snd &&
				vid		== fmt.vid;
	}
};

struct AVBase :
	RTTIBase
{
	RTTI_DECL0(AVBase)
	virtual Audio& GetAudio() = 0;
	virtual Video& GetVideo() = 0;
};

struct AVStreamBase :
	RTTIBase
{
	RTTI_DECL0(AVStreamBase)
	//virtual void FillVideoBuffer() = 0;
	//virtual void FillAudioBuffer() = 0;
	//virtual void Close() = 0;
	//virtual Audio& GetAudio() = 0;
	//virtual Video& GetVideo() = 0;
	virtual AudioStream& GetAudioStream() = 0;
	virtual VideoStream& GetVideoStream() = 0;
};

LOCAL_CTX(Media, AVBase, AVStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define MEDCTX ((MediaContext*)0)
#define MedCtx MediaContext*


class AVMediaProxy : public Media {
public:
	Audio* aud = 0;
	Video* vid = 0;

public:
	RTTI_DECL1(AVMediaProxy, Media)

	AVMediaProxy() = default;

	void Set(Audio& a, Video& v) {aud = &a; vid = &v;}
	Audio& GetAudio() override {return *aud;}
	Video& GetVideo() override {return *vid;}

	void			Exchange(MediaEx& e) override;
	int				GetQueueSize() const override;
	MediaFormat		GetFormat() const override;
	bool			IsQueueFull() const override;
	
};




struct DisplayFormat {
	VideoFormat vid;
	double fps;
	
	void Clear() {vid.Clear();}
	bool IsValid() const {return vid.IsValid();}
	double GetFrameSeconds() const {return 1.0 / fps;}
	bool operator!=(const DisplayFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const DisplayFormat& fmt) const {
		return	vid == fmt.vid &&
				fps == fmt.fps
				;
	}
	
};

class DisplaySystemBase;

LOCAL_CTX(Display, DummyValueBase, DummyStreamBase, DisplaySystemBase, DummyCustomSinkBase)
#define DISCTX ((DisplayContext*)0)
#define DisCtx DisplayContext*




typedef enum {
	STCTYPE_NULL,
	
} StaticType;

struct StaticFormat {
	StaticType type;
	
	void Clear() {type = STCTYPE_NULL;}
	bool IsValid() const {return type != STCTYPE_NULL;}
	
	bool operator!=(const StaticFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const StaticFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};

struct StaticValueData {
	int obj_i;
	int w;
	int h;
	int d;
	int stride;
	int pitch;
	const byte* data;
};

struct StaticStreamBase :
	RTTIBase
{
	RTTI_DECL0(StaticStreamBase)
	
	virtual bool LoadFileAny(String path) {return false;}
	virtual bool GetImage(Image& img) {return false;}
	virtual Size GetResolution() const {return Size(0,0);}
	virtual int GetDepth() const {return 1;}
	
};

LOCAL_CTX(Static, DummyValueBase, StaticStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define STCCTX ((StaticContext*)0)
#define StcCtx StaticContext*




typedef enum {
	DEVTYPE_NULL,
	
} DeviceType;

struct DeviceFormat {
	DeviceType type;
	
	void Clear() {type = DEVTYPE_NULL;}
	bool IsValid() const {return type != DEVTYPE_NULL;}
	
	bool operator!=(const DeviceFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const DeviceFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};


LOCAL_CTX(Device, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define DEVCTX ((DeviceContext*)0)
#define DevCtx DeviceContext*




typedef enum {
	PHYSTYPE_NULL,
	
} PhysicsType;

struct PhysicsFormat {
	PhysicsType type;
	
	void Clear() {type = PHYSTYPE_NULL;}
	bool IsValid() const {return type != PHYSTYPE_NULL;}
	
	bool operator!=(const PhysicsFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const PhysicsFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};

class PhysicsSystemBase;

LOCAL_CTX(Physics, DummyValueBase, DummyStreamBase, PhysicsSystemBase, DummyCustomSinkBase)
#define PHYCTX ((PhysicsContext*)0)
#define PhyCtx PhysicsContext*





typedef enum {
	SCRIPTTYPE_NULL,
	
} ScriptingType;

struct ScriptingFormat {
	ScriptingType type;
	
	void Clear() {type = SCRIPTTYPE_NULL;}
	bool IsValid() const {return type != SCRIPTTYPE_NULL;}
	
	bool operator!=(const ScriptingFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const ScriptingFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};


LOCAL_CTX(Scripting, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define SCRCTX ((ScriptingContext*)0)
#define ScrCtx ScriptingContext*




typedef enum {
	HUMTYPE_NULL,
	
} HumanType;

struct HumanFormat {
	HumanType type;
	
	void Clear() {type = HUMTYPE_NULL;}
	bool IsValid() const {return type != HUMTYPE_NULL;}
	
	bool operator!=(const HumanFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const HumanFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};

struct HumanCustomSinkBase :
	RTTIBase
{
	RTTI_DECL0(HumanCustomSinkBase)
	virtual CamerableRef GetCamerable();
	virtual TransformRef GetTransform();
};

LOCAL_CTX(Human, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, HumanCustomSinkBase)
#define HUMCTX ((HumanContext*)0)
#define HumCtx HumanContext*





typedef enum {
	MDLTYPE_NULL,
	
} ModelType;

struct ModelFormat {
	ModelType type;
	
	void Clear() {type = MDLTYPE_NULL;}
	bool IsValid() const {return type != MDLTYPE_NULL;}
	
	bool operator!=(const ModelFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const ModelFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};


LOCAL_CTX(Model, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define MDLCTX ((ModelContext*)0)
#define MdlCtx ModelContext*





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
	
	void				Set(int id, Type t, String path, int filter, int wrap, bool vflip) {TODO}
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

class AcceleratorStreamBase :
	RTTIBase
{
public:
	RTTI_DECL0(AcceleratorStreamBase)
	virtual const AcceleratorHeader& GetHeader() const = 0;
};

struct AcceleratorFormat {
	AcceleratorType type;
	
	void Clear() {type = ACCTYPE_NULL;}
	bool IsValid() const {return type != ACCTYPE_NULL;}
	
	bool operator!=(const AcceleratorFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const AcceleratorFormat& fmt) const {
		return	type == fmt.type
				;
	}
	
};


LOCAL_CTX(Accelerator, DummyValueBase, AcceleratorStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define ACCCTX ((AcceleratorContext*)0)
#define AccCtx AcceleratorContext*






#define IFACE_LIST \
	IFACE(Human)\
	IFACE(Audio)\
	IFACE(Video)\
	IFACE(Media)\
	IFACE(Display)\
	IFACE(Static)\
	IFACE(Model)\
	IFACE(Device)\
	IFACE(Physics)\
	IFACE(Scripting)\
	IFACE(Accelerator)


NAMESPACE_TOPSIDE_END

#endif
