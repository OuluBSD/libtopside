#ifndef _ParallelMach_SampleBase_h_
#define _ParallelMach_SampleBase_h_

NAMESPACE_PARALLEL_BEGIN


#define TYPE_LIST(endianess, pack_code, pack_sz) \
	TYPE(U8,	1,	0,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(S8,	1,	1,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(U16,	2,	0,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(S16,	2,	1,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(U24,	3,	0,	0,	0,	endianess, pack_code, pack_sz) \
	TYPE(S24,	3,	1,	0,	0,	endianess, pack_code, pack_sz) \
	TYPE(U32,	4,	0,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(S32,	4,	1,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(U64,	8,	0,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(S64,	8,	1,	0,	1,	endianess, pack_code, pack_sz) \
	TYPE(FLT,	4,	1,	1,	1,	endianess, pack_code, pack_sz) \
	TYPE(DBL,	8,	1,	1,	1,	endianess, pack_code, pack_sz)

#define SAMPLE_LIST \
	TYPE_LIST(LE,,) \
	TYPE_LIST(BE,,)

#define ENDIAN_TYPE_LIST(pack_code, pack_sz) \
	TYPE_LIST(LE, pack_code, pack_sz) \
	TYPE_LIST(BE, pack_code, pack_sz)

#define PACKED_SAMPLE_LIST \
	ENDIAN_TYPE_LIST(A, 1) \
	ENDIAN_TYPE_LIST(AB, 2) \
	ENDIAN_TYPE_LIST(ABC, 3) \
	ENDIAN_TYPE_LIST(ABCD, 4) \
	ENDIAN_TYPE_LIST(BA, 2) \
	ENDIAN_TYPE_LIST(CBA, 3) \
	ENDIAN_TYPE_LIST(DCBA, 4)


class BinarySample {
	
public:
	static const int def_sample_rate = 1;
	

		
	typedef enum : byte {
		INVALID,
		DEV_INTERNAL,
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			type_code##_##endianess ,
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			type_code##_##endianess##_##pack_code ,
		PACKED_SAMPLE_LIST
		#undef TYPE
		TYPE_COUNT,
		
		DEFAULT = U8_LE,
	} Type;
	
	template <class T> static Type GetSampleType();
	template <class T> static bool IsSampleType(Type t) {return t == GetSampleType<T>();}
	template <class T> static bool GetPackedSingleSize() {return GetPackedSingleSize(GetSampleType<T>());}
	
	
	static void Clear(Type& t) {t = INVALID;}
	static String ToString(Type t);
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static int GetSize(Type t);
	static int GetPackedSingleSize(Type t);
	static int GetPackedCount(Type t);
	static bool IsUnsigned(Type t);
	static bool IsSigned(Type t);
	static bool IsFloating(Type t);
	static bool IsDecimal(Type t);
	static bool IsLittleEndian(Type t);
	static bool IsBigEndian(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};

GVar::Sample GetGVarType(BinarySample::Type s);





template <int> struct DimBase;
template<> class DimBase<1> {
public:
	static const int n = 1;
	int res[1];
	
	using DimArg = int;
	
	void	SetSize(DimArg a) {res[0] = a;}
	void	SetDefault() {for(int i = 0; i < n; i++) res[i] = 1;}
	void	Clear() {for(int i = 0; i < n; i++) res[i] = 0;}
	
	String	ToString() const {return "len(" + IntStr(res[0]) + ")";}
	bool	IsSame(const DimBase& b) const {return res[0] == b.res[0];}
	int		GetScalar() const {return res[0];}
	bool	IsValid() const {for(int i = 0; i < n; i++) if (res[i] <= 0) return false; return true;}
	int		GetSize() const {return res[0];}
	
	DimBase& operator=(const DimBase& b) {for(int i = 0; i < n; i++) res[i] = b.res[i]; return *this;}
};

static_assert(std::is_trivially_constructible<DimBase<1>>::value == true, "DimBase<1> must be trivial to construct");


template<> struct DimBase<2> {
	static const int n = 2;
	int					res[2];
	int					width_pad;
	
	using DimArg = FixedArray<int,2>;
	
	
	void	SetSize(DimArg a) {res[0] = a[0]; res[1] = a[1];}
	void	SetSize(Size a) {res[0] = a.cx; res[1] = a.cy;}
	void	SetDefault() {for(int i = 0; i < n; i++) res[i] = 1;}
	void	Clear() {
		for(int i = 0; i < n; i++) res[i] = 0;
		width_pad = 0;
	}
	DimBase& operator=(const Size& b) {res[0] = b.cx; res[1] = b.cy; width_pad = 0; return *this;}
	DimBase& operator=(const DimBase& b) {
		for(int i = 0; i < n; i++) res[i] = b.res[i];
		width_pad = b.width_pad;
		return *this;
	}
	
	String	ToString() const {return Size(res[0], res[1]).ToString();}
	bool	IsSame(const DimBase& b) const {return res[0] == b.res[0] && res[1] == b.res[1];}
	int		GetArea() const {return res[0] * res[1];}
	int		GetScalar() const {return res[0] * res[1];}
	bool	IsValid() const {for(int i = 0; i < n; i++) if (res[i] <= 0) return false; return true;}
	Size	GetSize() const {return Size(res[0], res[1]);}
	
	void	SetLinePadding(int bytes) {ASSERT(bytes >= 0); width_pad = bytes;}
	
};

template<> struct DimBase<3> {
	static const int n = 3;
	int					res[3];
	//int					width_pad, height_pad;
	
	using DimArg = Size3;
	
	DimBase() {Clear();}
	DimBase(const DimBase& b) {*this = b;}
	
	void	SetSize(DimArg a) {res[0] = a.cx; res[1] = a.cy; res[2] = a.cz;}
	void	SetDefault() {for(int i = 0; i < n; i++) res[i] = 1;}
	void	Clear() {for(int i = 0; i < n; i++) res[i] = 0;}
	DimBase& operator=(const Size3& b) {res[0] = b.cx; res[1] = b.cy; res[2] = b.cz; return *this;}
	DimBase& operator=(const DimBase& b) {for(int i = 0; i < n; i++) res[i] = b.res[i]; return *this;}
	
	String	ToString() const {return Size3(res[0], res[1], res[2]).ToString();}
	bool	IsSame(const DimBase& b) const {return res[0] == b.res[0] && res[1] == b.res[1] && res[2] == b.res[2];}
	int		GetVolume() const {return res[0] * res[1] * res[2];}
	int		GetScalar() const {return res[0] * res[1] * res[2];}
	bool	IsValid() const   {for(int i = 0; i < n; i++) if (res[i] <= 0) return false; return true;}
	bool	IsValid2D() const {for(int i = 0; i < n; i++) if ((i < 2 && res[i] <= 0) || (i >= 2 && res[i] < 0)) return false; return true;}
	Size3	GetSize() const {return Size3(res[0], res[1], res[2]);}
	
};


class OnceBase {
public:
	
	static const int def_sample_rate = 1;
	
	void	Clear() {}
	void	SetTimeSeries(int,int) {Panic("never");}
	//void SetDeviceInternal() {}
	
	int		GetSampleRate() const {return 1;}
	bool	IsSame(const OnceBase& b) const {return true;}
	String	ToString() const {return "OnceBase";}
	bool	IsValid() const {return true;}
	
};

class SparseTimeSeriesBase {
public:
	static const int def_sample_rate = 1;
	
	void	Clear() {}
	void	SetTimeSeries(int,int) {Panic("never");}
	//void SetDeviceInternal() {}
	
	int		GetSampleRate() const {return 1;}
	bool	IsSame(const SparseTimeSeriesBase& b) const {return true;}
	String	ToString() const {return "SparseTimeSeriesBase";}
	bool	IsValid() const {return true;}
	double	GetFrameSeconds() const {return 0;}
	
};

struct TimeSeriesBase {
	double freq;
	int sample_rate;
	
	
	void	Clear() {freq = 0; sample_rate = 0;}
	void	SetTimeSeries(double freq, int sample_rate) {this->freq = freq; this->sample_rate = sample_rate;}
	void	SetFPS(double fps, int sample_rate=1) {freq = fps * sample_rate; this->sample_rate = sample_rate;}
	void	SetDefault() {freq = 1; sample_rate = 1;}
	void	SetSampleRate(int i) {sample_rate = i;}
	void	SetFrequency(double d) {freq = d;}
	
	String	ToString() const {return "freq: " + DblStr(freq) + ", sample-rate: " + IntStr(sample_rate);}
	bool	IsPlaybackCompatible(const TimeSeriesBase& b) const {return b.freq == freq;}
	bool	IsSame(const TimeSeriesBase& b) const {
		return	b.freq == freq &&
				b.sample_rate == sample_rate;
	}
	bool	IsValid() const {return freq > 0 && sample_rate > 0;}
	double	GetFrameSeconds() const {return (double)sample_rate / (double)freq;}
	int		GetSampleRate() const {return sample_rate;}
	double	GetFrequency() const {return freq;}
	double	GetFPS() const {return freq / sample_rate;}
	
	void operator=(const TimeSeriesBase& c) {
		freq = c.freq;
		sample_rate = c.sample_rate;
	}
	
};

static_assert(std::is_trivially_constructible<TimeSeriesBase>::value == true, "TimeSeriesBase must be trivial to construct");



template <class T>
class SampleBase {
	
public:
	using Sample = T;
	using SampleType = typename T::Type;
	
	SampleType type;
	
	
	void	Clear() {Sample::Clear(type);}
	void	SetType(SampleType t) {type = t;}
	void	SetDefault() {type = Sample::DEFAULT;}
	
	String	ToString() const {return Sample::ToString(type);}
	int		GetSampleSize() const {return Sample::GetSize(type);}
	bool	IsSampleFloat() const {return Sample::IsFloating(type);}
	bool	IsSampleSigned() const {return Sample::IsSigned(type);}
	bool	IsSampleBigEndian() const {return Sample::IsBigEndian(type);}
	bool	IsCopyCompatible(const SampleBase& b) const {return Sample::IsCopyCompatible(type, b.type);}
	bool	IsValid() const {return Sample::IsValid(type);}
	bool	IsDeviceInternal() const {return type == SampleType::DEV_INTERNAL;}
	template <class K> bool IsSampleType() const {return Sample::template IsSampleType<K>(type);}
	int		GetPackedSingleSize() const {return Sample::GetPackedSingleSize(type);}
	int		GetPackedCount() const {return Sample::GetPackedCount(type);}
	SampleType GetType() const {return type;}
	
	void operator=(const SampleBase& c) {
		type = c.type;
	}
	
};

//static_assert(std::is_trivially_constructible<SampleBase<SoundSample>>::value == true, "SampleBase<SoundSample> must be trivial to construct");


struct DevBase : RTTIBase {
	TypeCls dev_spec;
	
public:
	RTTI_DECL0(DevBase)
	
	DevBase() {dev_spec = AsVoidTypeCls();}
	
	void	Clear() {dev_spec = AsVoidTypeCls();}
	void	SetDevSpec(TypeCls t) {dev_spec = t;}
	void operator=(const DevBase& b) {dev_spec = b.dev_spec;}
	
	template <class DevSpec>
	void SetDevSpec() {
		dev_spec = AsTypeCls<DevSpec>();
	}
	
	TypeCls	GetDevSpec() const {return dev_spec;}
	bool	IsDeviceSpecific() const {return dev_spec != AsVoidTypeCls();}
	bool	IsSame(const DevBase& f) const {return dev_spec == f.dev_spec;}
	bool	IsValid() const {return dev_spec != AsVoidTypeCls();}
	
	String	ToString() const;
};


NAMESPACE_PARALLEL_END

#endif
