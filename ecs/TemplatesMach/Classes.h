#ifndef _TemplatesMach_Classes_h_
#define _TemplatesMach_Classes_h_

NAMESPACE_TOPSIDE_BEGIN

class Entity;
class Viewable;
class Transform;
using ViewableRef			= Ref<Viewable,				RefParent1<Entity>>;
using TransformRef			= Ref<Transform,			RefParent1<Entity>>;






class SoundSample {
public:
	static const int def_sample_rate = 1024;
	
	#define SND_SMPL_LIST \
		SND_SMPL(S_U8_LE) \
		SND_SMPL(S_U16_LE) \
		SND_SMPL(S_U24_LE) \
		SND_SMPL(S_U32_LE) \
		SND_SMPL(S_U64_LE) \
		SND_SMPL(S_S8_LE) \
		SND_SMPL(S_S16_LE) \
		SND_SMPL(S_S24_LE) \
		SND_SMPL(S_S32_LE) \
		SND_SMPL(S_S64_LE) \
		SND_SMPL(S_FLT_LE) \
		SND_SMPL(S_DBL_LE) \
		SND_SMPL(S_U8_BE) \
		SND_SMPL(S_U16_BE) \
		SND_SMPL(S_U24_BE) \
		SND_SMPL(S_U32_BE) \
		SND_SMPL(S_U64_BE) \
		SND_SMPL(S_S8_BE) \
		SND_SMPL(S_S16_BE) \
		SND_SMPL(S_S24_BE) \
		SND_SMPL(S_S32_BE) \
		SND_SMPL(S_S64_BE) \
		SND_SMPL(S_FLT_BE) \
		SND_SMPL(S_DBL_BE)
		
	typedef enum {
		INVALID,
		#define SND_SMPL(x) x ,
		SND_SMPL_LIST
		#undef SND_SMPL
		TYPE_COUNT
	} Type;
	
	template <class T> static Type GetSampleType();
	template <class T> static bool IsSampleType(Type t) {return t == GetSampleType<T>();}
	
	
	static void Clear(Type& t) {t = INVALID;}
	static String ToString(Type t);
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static int GetSize(Type t);
	static bool IsUnsigned(Type t);
	static bool IsSigned(Type t);
	static bool IsFloating(Type t);
	static bool IsDecimal(Type t);
	static bool IsLittleEndian(Type t);
	static bool IsBigEndian(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};



class LightSampleFD
{
	
public:
	static const int def_sample_rate = 1;
	
	#define LTFD_SMPL_LIST \
		LTFD_SMPL(S_R_U8_LE) \
		LTFD_SMPL(S_RG_U8_LE) \
		LTFD_SMPL(S_RGB_U8_LE) \
		LTFD_SMPL(S_RGBA_U8_LE) \
		LTFD_SMPL(S_BGR_U8_LE) \
		LTFD_SMPL(S_R_FLT_LE) \
		LTFD_SMPL(S_RG_FLT_LE) \
		LTFD_SMPL(S_RGB_FLT_LE) \
		LTFD_SMPL(S_RGBA_FLT_LE) \
		LTFD_SMPL(S_BGR_FLT_LE)
	
	typedef enum {
		INVALID,
		#define LTFD_SMPL(x) x ,
		LTFD_SMPL_LIST
		#undef LTFD_SMPL
		TYPE_COUNT
	} Type;
	
	
	static void Clear(Type& t) {t = INVALID;}
	static String ToString(Type t);
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static int GetSize(Type t);
	static int GetChannelSizeFD(Type t);
	static int GetChannelCountFD(Type t);
	static bool IsUnsigned(Type t);
	static bool IsSigned(Type t);
	static bool IsFloating(Type t);
	static bool IsDecimal(Type t);
	static bool IsLittleEndian(Type t);
	static bool IsBigEndian(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};

#define DUMMY_SAMPLE(x) \
	class x { \
		public: \
		static const int def_sample_rate = 1024; \
		typedef enum { \
			INVALID, \
			\
			TYPE_COUNT \
		} Type; \
		static void Clear(Type& t) {t = INVALID;} \
		static String ToString(Type t) {return IntStr((int)t);} \
		static bool IsCopyCompatible(Type a, Type b) {return a == b;} \
		static int GetSize(Type t) {return 0;} \
		static bool IsUnsigned(Type t) {return false;} \
		static bool IsSigned(Type t) {return false;} \
		static bool IsFloating(Type t) {return false;} \
		static bool IsDecimal(Type t) {return false;} \
		static bool IsLittleEndian(Type t) {return false;} \
		static bool IsBigEndian(Type t) {return false;} \
		static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;} \
	};
		
DUMMY_SAMPLE(HumanSample)
DUMMY_SAMPLE(SpaceSample)
DUMMY_SAMPLE(VertexSample)
DUMMY_SAMPLE(TexLocSample)
DUMMY_SAMPLE(BoneSample)
DUMMY_SAMPLE(DeviceSample)
DUMMY_SAMPLE(MidiSample)
DUMMY_SAMPLE(PhysicsSample)
DUMMY_SAMPLE(MaterialSample)
DUMMY_SAMPLE(MaterialSampleFD)



template <int> struct DimBase;
template<> struct DimBase<1> {
	union {
		int size[1];
		int channels;
		int width;
		int length;
	};
	
	DimBase() {Clear();}
	DimBase(const DimBase& b) {*this = b;}
	void Clear() {for(int i = 0; i < 1; i++) size[i] = 0;}
	String ToString() const {return "len(" + IntStr(channels) + ")";}
	bool IsSame(const DimBase& b) const {return size[0] == b.size[0];}
	int GetArea() const {return size[0];}
	DimBase& operator=(const DimBase& b) {for(int i = 0; i < 1; i++) size[i] = b.size[i]; return *this;}
};

template<> struct DimBase<2> {
	union {
		int size[2];
		Size res;
		union {
			int channels;
			int sources;
		};
		union {
			int width;
			int height;
		};
	};
	int width_pad;
	
	DimBase() {Clear();}
	DimBase(const DimBase& b) {*this = b;}
	void Clear() {
		for(int i = 0; i < 2; i++) size[i] = 0;
		width_pad = 0;
	}
	String ToString() const {return res.ToString();}
	bool IsSame(const DimBase& b) const {return size[0] == b.size[0] && size[1] == b.size[1];}
	int GetArea() const {return size[0] * size[1];}
	DimBase& operator=(const DimBase& b) {
		for(int i = 0; i < 2; i++) size[i] = b.size[i];
		width_pad = b.width_pad;
		return *this;
	}
	
	void SetLinePadding(int bytes) {ASSERT(bytes >= 0); width_pad = bytes;}
	
};

template<> struct DimBase<3> {
	union {
		int size[3];
		Size3 res;
		union {
			int channels;
			int sources;
			int variants;
		};
		union {
			int width;
			int height;
			int depth;
		};
	};
	
	DimBase() {Clear();}
	DimBase(const DimBase& b) {*this = b;}
	
	String ToString() const {return res.ToString();}
	void Clear() {for(int i = 0; i < 3; i++) size[i] = 0;}
	bool IsSame(const DimBase& b) const {return size[0] == b.size[0] && size[1] == b.size[1] && size[2] == b.size[2];}
	int GetArea() const {return size[0] * size[1] * size[2];}
	DimBase& operator=(const DimBase& b) {for(int i = 0; i < 3; i++) size[i] = b.size[i]; return *this;}
};


class OnceBase {
public:
	
	static const int def_sample_rate = 1;
	
	void Clear() {}
	
	int GetSampleRate() const {return 1;}
	bool IsSame(const OnceBase& b) const {return true;}
	String ToString() const {return "OnceBase";}
	
};

class SparseTimeSeriesBase {
public:
	static const int def_sample_rate = 1;
	
	void Clear() {}
	
	int GetSampleRate() const {return 1;}
	bool IsSame(const SparseTimeSeriesBase& b) const {return true;}
	String ToString() const {return "SparseTimeSeriesBase";}
	
};

class TimeSeriesBase {
public:
	int freq = 0;
	int sample_rate = 0;
	
	
	void Clear() {freq = 0; sample_rate = 0;}
	void Set(int freq, int sample_rate) {this->freq = freq; this->sample_rate = sample_rate;}
	void SetFPS(int fps, int sample_rate=1) {freq = fps * sample_rate; this->sample_rate = sample_rate;}
	
	String ToString() const {return "freq: " + IntStr(freq) + ", sample-rate: " + IntStr(sample_rate);}
	bool IsPlaybackCompatible(const TimeSeriesBase& b) const {return b.freq == freq;}
	bool IsSame(const TimeSeriesBase& b) const {
		return	b.freq == freq &&
				b.sample_rate == sample_rate;
	}
	double GetFrameSeconds() const {return (double)sample_rate / (double)freq;}
	int GetSampleRate() const {return sample_rate;}
	int GetFrequency() const {return freq;}
	double GetFPS() const {return freq / sample_rate;}
	
	void operator=(const TimeSeriesBase& c) {
		freq = c.freq;
		sample_rate = c.sample_rate;
	}
	
};

template <class T>
class SampleBase {
public:
	using Sample = T;
	using SampleType = typename T::Type;
	
	SampleType type;
	
	
	void Clear() {Sample::Clear(type);}
	void SetType(SampleType t) {type = t;}
	
	String ToString() const {return Sample::ToString(type);}
	int GetSampleSize() const {return Sample::GetSize(type);}
	bool IsSampleFloat() const {return Sample::IsFloating(type);}
	bool IsSampleSigned() const {return Sample::IsSigned(type);}
	bool IsSampleBigEndian() const {return Sample::IsBigEndian(type);}
	bool IsCopyCompatible(const SampleBase& b) const {return Sample::IsCopyCompatible(type, b.type);}
	bool IsValid() const {return Sample::IsValid(type);}
	template <class K> bool IsSampleType() const {return Sample::template IsSampleType<K>(type);}
	int GetChannelSizeFD() const {return Sample::GetChannelSizeFD(type);}
	int GetChannelCountFD() const {return Sample::GetChannelCountFD(type);}
	
	void operator=(const SampleBase& c) {
		type = c.type;
	}
	
};




#define FUNC_TMPL(dim, post, d) \
	using Class = d##dim##post<T>; \
	d##dim##post() {Clear();} \
	d##dim##post(const d##dim##post& s) {*this = s;} \
	static const int def_sample_rate = T::def_sample_rate; \
	bool IsSame(const Class& b) const {\
		return		post##Base::IsSame(b) && \
					SampleBase<T>::IsCopyCompatible(b) && \
					DimBase<dim>::IsSame(b); \
	} \
	bool operator==(const Class& b) const {return IsSame(b);} \
	bool operator!=(const Class& b) const {return !IsSame(b);} \
	void Clear() {post##Base::Clear(); SampleBase<T>::Clear(); DimBase<dim>::Clear();} \
	int GetFrameSize() const {return DimBase<dim>::GetArea() * post##Base::GetSampleRate() * SampleBase<T>::GetSampleSize();} \
	Class& operator=(const Class& c) { \
					post##Base::operator=(c); \
					SampleBase<T>::operator=(c); \
					DimBase<dim>::operator=(c); \
		return *this; \
	} \
	String ToString() const {return DimBase<dim>::ToString() + ", " + post##Base::ToString() + ", " + SampleBase<T>::ToString();} \
	


#define COMBINE_CLASS(dim, post, d) \
	template <class T> \
	class d##dim##post : \
		public post##Base, \
		public SampleBase<T>, \
		public DimBase<dim> \
	{ \
	 \
	public: \
		FUNC_TMPL(dim, post, d) \
	 \
	};

#define COMBINE_CLASS_3(post, d) \
	COMBINE_CLASS(1, post, d) \
	COMBINE_CLASS(2, post, d) \
	COMBINE_CLASS(3, post, d)

#define COMBINE_CLASS_TDFD(x) \
	COMBINE_CLASS_3(x, TD) \
	COMBINE_CLASS_3(x, FD)


COMBINE_CLASS_TDFD(Once)
COMBINE_CLASS_TDFD(TimeSeries)
COMBINE_CLASS_TDFD(SparseTimeSeries)


#undef FUNC_TMPL
#undef COMBINE_CLASS
#undef COMBINE_CLASS_3
#undef COMBINE_CLASS_TDFD







template <class S0, class S1>
class MultiSample2 {
public:
	using T0 = S0;
	using T1 = S1;
	
	
};

template <class S0, class S1, class S2, class S3>
class MultiSample4 {
public:
	using T0 = S0;
	using T1 = S1;
	using T2 = S2;
	using T3 = S3;
	
	
};





template <class T>
class TD1OnceMulti4 {
	using T0 = typename T::T0;
	using T1 = typename T::T1;
	using T2 = typename T::T2;
	using T3 = typename T::T3;
	
	TD1Once<T0>		o0;
	TD1Once<T1>		o1;
	TD1Once<T2>		o2;
	TD1Once<T3>		o3;
	
public:
	static const int def_sample_rate = 1;
	
	
};

template <class T>
class AVTimeSeries {
	using T0 = TD1TimeSeries<typename T::T0>;
	using T1 = TD2TimeSeries<typename T::T1>;
	
	T0		o0;
	T1		o1;
	
public:
	static const int def_sample_rate = 1;
	
};




NAMESPACE_TOPSIDE_END


#endif
