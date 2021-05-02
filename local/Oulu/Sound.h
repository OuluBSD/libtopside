#ifndef _Oulu_Sound_h_
#define _Oulu_Sound_h_

NAMESPACE_UPP
inline void EndianSwap(unsigned char&)	{}
inline void EndianSwap(char&)			{}
inline void EndianSwap(float& f)		{EndianSwap(*(dword*)&f);}
inline void EndianSwap(double& d)		{EndianSwap(*(uint64*)&d);}
END_UPP_NAMESPACE

NAMESPACE_OULU_BEGIN

struct AudioFormat {
	int var_size = 0;
	int sample_rate = 0;
	int channels = 0;
	int freq = 0;
	bool is_var_float = 0;
	bool is_var_signed = 0;
	bool is_var_bigendian = 0;
	
	bool IsValid() const {return var_size > 0 && sample_rate > 0 && channels > 0 && freq > 0;}
	void Clear() {memset(this, 0, sizeof(AudioFormat));}
	
	bool operator!=(const AudioFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const AudioFormat& fmt) const {
		return	var_size			== fmt.var_size &&
				sample_rate			== fmt.sample_rate &&
				channels			== fmt.channels &&
				freq				== fmt.freq &&
				is_var_float		== fmt.is_var_float &&
				is_var_signed		== fmt.is_var_signed &&
				is_var_bigendian	== fmt.is_var_bigendian;
	}
	
	int GetFrameBytes() const {return var_size * sample_rate * channels;}
	int GetFrameBytes(int dst_sample_rate) const {return var_size * dst_sample_rate * channels;}
	
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

class Sound {
	
public:
	Sound() = default;
	virtual ~Sound() = default;
	
	virtual void Exchange(AudioEx& e) = 0;
	virtual int GetQueueSize() const = 0;
	virtual AudioFormat GetAudioFormat() const = 0;
	virtual bool IsQueueFull() const = 0;
	virtual dword GetWriteFrame() const = 0;
	virtual bool GetFrameFrom(Sound& snd, bool realtime) = 0;
#ifdef flagOPENGL
	virtual bool PaintOpenGLTexture(int texture) {return false;}
#endif
	
};


class SoundProxy : public Sound {
	Sound* snd = 0;
	
public:
	SoundProxy() = default;
	SoundProxy(Sound* snd) : snd(snd) {}
	
	void Set(Sound* snd) {this->snd = snd;}
	
	operator bool() const {return snd != 0;}
	void Exchange(AudioEx& e) override {if (snd) snd->Exchange(e);}
	int GetQueueSize() const override {if (snd) return snd->GetQueueSize(); return 0;}
	AudioFormat GetAudioFormat() const override {if (snd) return snd->GetAudioFormat(); return AudioFormat();}
	bool IsQueueFull() const override {if (snd) return snd->IsQueueFull(); return 0;}
	dword GetWriteFrame() const override {if (snd) return snd->GetWriteFrame(); return 0;}
	bool GetFrameFrom(Sound& dst, bool realtime) override {if (snd) return snd->GetFrameFrom(dst, realtime); return false;}
	
};

template <typename SRC, typename DST, bool SRC_NATIVE_ENDIAN=1, bool DST_NATIVE_ENDIAN=1> DST ConvertSoundSample(SRC v) {
	static_assert(!SRC_NATIVE_ENDIAN || !DST_NATIVE_ENDIAN, "Only native endian sample should use default implementation");
	if (!SRC_NATIVE_ENDIAN)
		EndianSwap(v);
	DST r = ConvertSoundSample<SRC,DST,1,1>(v);
	if (!DST_NATIVE_ENDIAN)
		EndianSwap(r);
	return r;
}

#define SAMPLE_PASSTHROUGH(TYPE) \
	template <> inline TYPE ConvertSoundSample<TYPE, TYPE, 1,1>(TYPE u) {return u;} \
	template <> inline TYPE ConvertSoundSample<TYPE, TYPE, 0,0>(TYPE u) {return u;}
SAMPLE_PASSTHROUGH(unsigned char)
SAMPLE_PASSTHROUGH(unsigned short)
SAMPLE_PASSTHROUGH(unsigned int)
SAMPLE_PASSTHROUGH(char)
SAMPLE_PASSTHROUGH(short)
SAMPLE_PASSTHROUGH(int)
SAMPLE_PASSTHROUGH(float)
SAMPLE_PASSTHROUGH(double)
#undef SAMPLE_PASSTHROUGH

template <> inline unsigned char ConvertSoundSample<unsigned int, unsigned char, 1,1>(unsigned int u)		{return (unsigned char)	((dword)u >> 24);}
template <> inline unsigned short ConvertSoundSample<unsigned int, unsigned short, 1,1>(unsigned int u)		{return (unsigned short)((dword)u >> 16);}
template <> inline unsigned char ConvertSoundSample<unsigned short, unsigned char, 1,1>(unsigned short u)	{return (unsigned char)	((dword)u >> 8);}
template <> inline unsigned int ConvertSoundSample<unsigned char, unsigned int, 1,1>(unsigned char u)		{return (unsigned int)	((dword)u << 24);}
template <> inline unsigned int ConvertSoundSample<unsigned short, unsigned int, 1,1>(unsigned short u)		{return (unsigned int)	((dword)u << 16);}
template <> inline unsigned short ConvertSoundSample<unsigned char, unsigned short, 1,1>(unsigned char u)	{return (unsigned short)((dword)u << 8);}

template <> inline char ConvertSoundSample<int, char, 1,1>(int i)						{return (char)	(i >= 0 ? (int)i >> 24	: -((int)-i >> 24));}
template <> inline short ConvertSoundSample<int, short, 1,1>(int i)						{return (short)	(i >= 0 ? (int)i >> 16	: -((int)-i >> 16));}
template <> inline char ConvertSoundSample<short, char, 1,1>(short i)					{return (char)	(i >= 0 ? (int)i >> 8	: -((int)-i >> 8));}
template <> inline int ConvertSoundSample<char, int, 1,1>(char i)						{return (int)	(i >= 0 ? (int)i << 24	: -((int)-i << 24));}
template <> inline int ConvertSoundSample<short, int, 1,1>(short i)						{return (int)	(i >= 0 ? (int)i << 16	: -((int)-i << 16));}
template <> inline short ConvertSoundSample<char, short, 1,1>(char i)					{return (short)	(i >= 0 ? (int)i << 8	: -((int)-i << 8));}

template <> inline char ConvertSoundSample<unsigned int, char, 1,1>(unsigned int u)		{return (char)	((int)((dword)u >> 24)	+ (int)std::numeric_limits<char>::min());}
template <> inline short ConvertSoundSample<unsigned int, short, 1,1>(unsigned int u)	{return (short)	((int)((dword)u >> 16)	+ (int)std::numeric_limits<short>::min());}
template <> inline char ConvertSoundSample<unsigned short, char, 1,1>(unsigned short u)	{return (char)	((int)((dword)u >> 8)	+ (int)std::numeric_limits<char>::min());}
template <> inline int ConvertSoundSample<unsigned char, int, 1,1>(unsigned char u)		{return (int)	(((int)u + (int)std::numeric_limits<char>::min()) << 24);}
template <> inline int ConvertSoundSample<unsigned short, int, 1,1>(unsigned short u)	{return (int)	(((int)u + (int)std::numeric_limits<short>::min()) << 16);}
template <> inline short ConvertSoundSample<unsigned char, short, 1,1>(unsigned char u)	{return (short)	(((int)u + (int)std::numeric_limits<char>::min()) << 8);}

template <> inline unsigned char ConvertSoundSample<int, unsigned char, 1,1>(int u)		{return (unsigned char)	(((int)u >> 24)	- (int)std::numeric_limits<char>::min());}
template <> inline unsigned short ConvertSoundSample<int, unsigned short, 1,1>(int u)	{return (unsigned short)(((int)u >> 16)	- (int)std::numeric_limits<short>::min());}
template <> inline unsigned char ConvertSoundSample<short, unsigned char, 1,1>(short u)	{return (unsigned char)	(((int)u >> 8)	- (int)std::numeric_limits<char>::min());}
template <> inline unsigned int ConvertSoundSample<char, unsigned int, 1,1>(char u)		{return (unsigned int)	(((int)u - (int)std::numeric_limits<char>::min()) << 24);}
template <> inline unsigned int ConvertSoundSample<short, unsigned int, 1,1>(short u)	{return (unsigned int)	(((int)u - (int)std::numeric_limits<short>::min()) << 16);}
template <> inline unsigned short ConvertSoundSample<char, unsigned short, 1,1>(char u)	{return (unsigned short)(((int)u - (int)std::numeric_limits<char>::min()) << 8);}

template <> inline unsigned char ConvertSoundSample<char, unsigned char, 1,1>(char u)			{return (unsigned char)		((int)u - (int)std::numeric_limits<char>::min());}
template <> inline unsigned short ConvertSoundSample<short, unsigned short, 1,1>(short u)		{return (unsigned short)	((int)u - (int)std::numeric_limits<short>::min());}
template <> inline unsigned int ConvertSoundSample<int, unsigned int, 1,1>(int u)				{return (unsigned int)		((int64)u - (int64)std::numeric_limits<int>::min());}
template <> inline char ConvertSoundSample<unsigned char, char, 1,1>(unsigned char u)			{return (char)	((int)u + (int)std::numeric_limits<char>::min());}
template <> inline short ConvertSoundSample<unsigned short, short, 1,1>(unsigned short u)		{return (short)	((int)u + (int)std::numeric_limits<short>::min());}
template <> inline int ConvertSoundSample<unsigned int, int, 1,1>(unsigned int u)				{return (int)	((int64)u + (int64)std::numeric_limits<int>::min());}

template <> inline float ConvertSoundSample<double, float, 1,1>(double d) {return (float)d;}
template <> inline double ConvertSoundSample<float, double, 1,1>(float f) {return (double)f;}

#define UNSIGNED_TO_FLOAT(TYPE, FLOAT) \
template <> inline FLOAT ConvertSoundSample<TYPE,FLOAT,1,1>(TYPE u) { \
	static constexpr double recip = 2.0 / (double)std::numeric_limits<TYPE>::max(); \
	return (FLOAT)(u * recip - 1.0); \
}
#define SIGNED_TO_FLOAT(TYPE, FLOAT) \
template <> inline FLOAT ConvertSoundSample<TYPE,FLOAT,1,1>(TYPE i) { \
	static constexpr double recip = 1.0 / (double)std::numeric_limits<TYPE>::max(); \
	return (FLOAT)(i * recip); \
}
#define FLOAT_TO_UNSIGNED(FLOAT, TYPE) \
template <> inline TYPE ConvertSoundSample<FLOAT,TYPE,1,1>(FLOAT f) { \
	static constexpr double recip = (double)std::numeric_limits<TYPE>::max() / 2.0; \
	f = std::min<FLOAT>(1, std::max<FLOAT>(-1, f));\
	return (TYPE)((f * recip) + recip); \
}
#define FLOAT_TO_SIGNED(FLOAT, TYPE) \
template <> inline TYPE ConvertSoundSample<FLOAT,TYPE,1,1>(FLOAT f) { \
	static constexpr double recip = (double)std::numeric_limits<TYPE>::max(); \
	f = std::min<FLOAT>(1, std::max<FLOAT>(-1, f));\
	return (TYPE)(f * recip); \
}
#define INTEGER_TO_INTEGER(SRC, DST) \
template <> inline DST ConvertSoundSample<SRC,DST,1,1>(SRC f) { \
	unsigned int u32 = ConvertSoundSample<SRC,unsigned int, 1,1>(f); \
	static constexpr double recip = (double)std::numeric_limits<DST>::max(); \
	return (DST)(f * recip); \
}

#define INTEGERS_TO_FLOATS(FLOAT) \
	SIGNED_TO_FLOAT(int, FLOAT) \
	SIGNED_TO_FLOAT(short, FLOAT) \
	SIGNED_TO_FLOAT(char, FLOAT) \
	UNSIGNED_TO_FLOAT(unsigned int, FLOAT) \
	UNSIGNED_TO_FLOAT(unsigned short, FLOAT) \
	UNSIGNED_TO_FLOAT(unsigned char, FLOAT)
#define FLOATS_TO_INTEGERS(FLOAT) \
	FLOAT_TO_SIGNED(FLOAT, int) \
	FLOAT_TO_SIGNED(FLOAT, short) \
	FLOAT_TO_SIGNED(FLOAT, char) \
	FLOAT_TO_UNSIGNED(FLOAT, unsigned int) \
	FLOAT_TO_UNSIGNED(FLOAT, unsigned short) \
	FLOAT_TO_UNSIGNED(FLOAT, unsigned char)
INTEGERS_TO_FLOATS(float)
INTEGERS_TO_FLOATS(double)
FLOATS_TO_INTEGERS(float)
FLOATS_TO_INTEGERS(double)

struct SoundConverter {
	
	template <typename SRC, typename DST, bool SRC_NATIVE_ENDIAN, bool DST_NATIVE_ENDIAN>
	static void TypeConvert(const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst) {
		const SRC* src_it = (const SRC*)src;
		const SRC* src_end = src_it + src_fmt.sample_rate * src_fmt.channels;
		DST* dst_it = (DST*)dst;
		DST* dst_end = dst_it + src_fmt.sample_rate * dst_fmt.channels;
		for(int i = 0; i < src_fmt.sample_rate; i++) {
			for(int j = 0; j < dst_fmt.channels; j++)
				*dst_it++ =
					ConvertSoundSample<SRC, DST, SRC_NATIVE_ENDIAN, DST_NATIVE_ENDIAN>(
						src_it[j % src_fmt.channels]);
			src_it += src_fmt.channels;
		}
		ASSERT(src_it == src_end);
		ASSERT(dst_it == dst_end);
	}
	
	static bool Convert(const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst);
	
};

class VolatileSoundBuffer : public Sound {
	// Settings
	AudioFormat aud_fmt;
	int frames = 0;
	int frame_size = 0;
	SpinLock lock;
	
	// Runtime values
	Vector<byte> data[2];
	int data_i = 0, read_pos = 0, write_pos = 0, queue_size = 0;
	dword write_frame = 0;
	
	#ifdef flagDEBUG
	int size_limit = 10*1024*1024;
	#endif
	
	bool CheckSize(int size);
	void Get(AudioEx& e);
	void Put(AudioEx& e);
	
public:
	
	VolatileSoundBuffer() = default;
	
	void SetSize(AudioFormat aud_fmt, int frames=2);
	void Clear();
	void Zero();
	
	byte* GetActiveMem() {return data[data_i].Begin();}
	const byte* GetActiveMem() const {return data[data_i].Begin();}
	int GetMemSize() const {return data[0].GetCount();}
	bool IsEmpty() const {return data[0].IsEmpty();}
	
	void Exchange(AudioEx& e) override;
	int GetQueueSize() const override {return queue_size * aud_fmt.sample_rate;}
	AudioFormat GetAudioFormat() const override {return aud_fmt;}
	bool IsQueueFull() const override {return queue_size >= frames;}
	dword GetWriteFrame() const override {return write_frame;}
	bool GetFrameFrom(Sound& snd, bool realtime) override;
	
	#ifdef flagDEBUG
	void SetSizeLimit(int l) {size_limit = l;}
	#else
	void SetSizeLimit(int l) {}
	#endif
	
};


void SoundBufferUnitTest();


NAMESPACE_OULU_END

#endif
