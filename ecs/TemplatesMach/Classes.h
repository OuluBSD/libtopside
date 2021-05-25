#ifndef _TemplatesMach_Classes_h_
#define _TemplatesMach_Classes_h_

NAMESPACE_TOPSIDE_BEGIN

class Entity;
class Viewable;
class Transform;
using ViewableRef			= Ref<Viewable,				RefParent1<Entity>>;
using TransformRef			= Ref<Transform,			RefParent1<Entity>>;




class HumanSample {
	
	
};

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
	static bool IsUnsigned(Type t);
	static bool IsSigned(Type t);
	static bool IsFloating(Type t);
	static bool IsDecimal(Type t);
	static bool IsLittleEndian(Type t);
	static bool IsBigEndian(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};

class SpaceSample {
	
};

class VertexSample {
	
};

class TexLocSample {
	
};

class BoneSample {
	
};

class DeviceSample {
	
};

class MidiSample {
	
};

class PhysicsSample {
	
};

class MaterialSample {
	
};

class MaterialSampleFD {
	
};



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
};


template <class T>
class T1D :
	public OnceBase
{
	
public:
	int len = 0;
	
};

template <class T>
class T2D :
	public OnceBase
{
	
public:
	Size sz = {0,0};
	
};

template <class T>
class T3D :
	public OnceBase
{
	
public:
	Size3 vol = {0,0,0};
	
};

template <class T>
class T1DFD :
	public OnceBase
{
	
};

template <class T>
class T2DFD :
	public OnceBase
{
	
};

template <class T>
class T3DFD :
	public OnceBase
{
	
};

class TimeSeriesBase :
	RTTIBase {
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
	
	void operator=(const SampleBase& c) {
		type = c.type;
	}
	
};


#define TS_FUNCS(dim) \
	using TSClass = T##dim##DTimeSeries<T>; \
	T##dim##DTimeSeries() {Clear();} \
	T##dim##DTimeSeries(const T##dim##DTimeSeries& s) {*this = s;} \
	static const int def_sample_rate = T::def_sample_rate; \
	bool IsSame(const TSClass& b) const {\
		return		TimeSeriesBase::IsSame(b) && \
					SampleBase<T>::IsCopyCompatible(b) && \
					DimBase<dim>::IsSame(b); \
	} \
	bool operator==(const TSClass& b) const {return IsSame(b);} \
	bool operator!=(const TSClass& b) const {return !IsSame(b);} \
	void Clear() {TimeSeriesBase::Clear(); SampleBase<T>::Clear(); DimBase<dim>::Clear();} \
	int GetFrameSize() const {return DimBase<dim>::GetArea() * TimeSeriesBase::GetSampleRate() * SampleBase<T>::GetSampleSize();} \
	TSClass& operator=(const TSClass& c) { \
					TimeSeriesBase::operator=(c); \
					SampleBase<T>::operator=(c); \
					DimBase<dim>::operator=(c); \
		return *this; \
	} \
	String ToString() const {return DimBase<1>::ToString() + ", " + TimeSeriesBase::ToString() + ", " + SampleBase<T>::ToString();} \
	


template <class T>
class T1DTimeSeries :
	public TimeSeriesBase,
	public SampleBase<T>,
	public DimBase<1>
{
	RTTI_DECL1(T1DTimeSeries, TimeSeriesBase)
	
public:
	TS_FUNCS(1)
	
	
};

template <class T>
class T2DTimeSeries :
	public TimeSeriesBase,
	public SampleBase<T>,
	public DimBase<2>
{
	RTTI_DECL1(T2DTimeSeries, TimeSeriesBase)
	
public:
	TS_FUNCS(2)
	
};

template <class T>
class T3DTimeSeries :
	public TimeSeriesBase,
	public SampleBase<T>,
	public DimBase<3>
{
	RTTI_DECL1(T3DTimeSeries, TimeSeriesBase)
	
public:
	TS_FUNCS(3)
	
};



template <class T>
class T1DTimeSeriesFD :
	public TimeSeriesBase
{
	
};

template <class T>
class T2DTimeSeriesFD :
	public TimeSeriesBase
{
	
};

template <class T>
class T3DTimeSeriesFD :
	public TimeSeriesBase
{
	
};



class SparseBase {
public:
	static const int def_sample_rate = 1;
	
};

template <class T>
class T1DSparseTimeSeries :
	public SparseBase
{
	
};









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
class T1DMulti4 {
	using T0 = typename T::T0;
	using T1 = typename T::T1;
	using T2 = typename T::T2;
	using T3 = typename T::T3;
	
	T1D<T0>		o0;
	T1D<T1>		o1;
	T1D<T2>		o2;
	T1D<T3>		o3;
	
public:
	static const int def_sample_rate = 1;
	
	
};

template <class T>
class AVTimeSeries {
	using T0 = T1DTimeSeries<typename T::T0>;
	using T1 = T2DTimeSeries<typename T::T1>;
	
	T1D<T0>		o0;
	T1D<T1>		o1;
	
public:
	static const int def_sample_rate = 1;
	
};




NAMESPACE_TOPSIDE_END

#endif
