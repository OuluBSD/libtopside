#ifndef _Local_Audio_h_
#define _Local_Audio_h_

NAMESPACE_UPP
inline void EndianSwap(unsigned char&)	{}
inline void EndianSwap(char&)			{}
inline void EndianSwap(float& f)		{EndianSwap(*(dword*)&f);}
inline void EndianSwap(double& d)		{EndianSwap(*(uint64*)&d);}
END_UPP_NAMESPACE

NAMESPACE_TOPSIDE_BEGIN


template <typename SRC, typename DST, bool SRC_NATIVE_ENDIAN=1, bool DST_NATIVE_ENDIAN=1> DST ConvertAudioSample(SRC v) {
	static_assert(!SRC_NATIVE_ENDIAN || !DST_NATIVE_ENDIAN, "Only native endian sample should use default implementation");
	if (!SRC_NATIVE_ENDIAN)
		EndianSwapT(v);
	DST r = ConvertAudioSample<SRC,DST,1,1>(v);
	if (!DST_NATIVE_ENDIAN)
		EndianSwapT(r);
	return r;
}

#define SAMPLE_PASSTHROUGH(TYPE) \
	template <> inline TYPE ConvertAudioSample<TYPE, TYPE, 1,1>(TYPE u) {return u;} \
	template <> inline TYPE ConvertAudioSample<TYPE, TYPE, 0,0>(TYPE u) {return u;}
SAMPLE_PASSTHROUGH(unsigned char)
SAMPLE_PASSTHROUGH(unsigned short)
SAMPLE_PASSTHROUGH(unsigned int)
SAMPLE_PASSTHROUGH(char)
SAMPLE_PASSTHROUGH(short)
SAMPLE_PASSTHROUGH(int)
SAMPLE_PASSTHROUGH(float)
SAMPLE_PASSTHROUGH(double)
#undef SAMPLE_PASSTHROUGH

template <> inline unsigned char ConvertAudioSample<unsigned int, unsigned char, 1,1>(unsigned int u)		{return (unsigned char)	((dword)u >> 24);}
template <> inline unsigned short ConvertAudioSample<unsigned int, unsigned short, 1,1>(unsigned int u)		{return (unsigned short)((dword)u >> 16);}
template <> inline unsigned char ConvertAudioSample<unsigned short, unsigned char, 1,1>(unsigned short u)	{return (unsigned char)	((dword)u >> 8);}
template <> inline unsigned int ConvertAudioSample<unsigned char, unsigned int, 1,1>(unsigned char u)		{return (unsigned int)	((dword)u << 24);}
template <> inline unsigned int ConvertAudioSample<unsigned short, unsigned int, 1,1>(unsigned short u)		{return (unsigned int)	((dword)u << 16);}
template <> inline unsigned short ConvertAudioSample<unsigned char, unsigned short, 1,1>(unsigned char u)	{return (unsigned short)((dword)u << 8);}

template <> inline char ConvertAudioSample<int, char, 1,1>(int i)						{return (char)	(i >= 0 ? (int)i >> 24	: -((int)-i >> 24));}
template <> inline short ConvertAudioSample<int, short, 1,1>(int i)						{return (short)	(i >= 0 ? (int)i >> 16	: -((int)-i >> 16));}
template <> inline char ConvertAudioSample<short, char, 1,1>(short i)					{return (char)	(i >= 0 ? (int)i >> 8	: -((int)-i >> 8));}
template <> inline int ConvertAudioSample<char, int, 1,1>(char i)						{return (int)	(i >= 0 ? (int)i << 24	: -((int)-i << 24));}
template <> inline int ConvertAudioSample<short, int, 1,1>(short i)						{return (int)	(i >= 0 ? (int)i << 16	: -((int)-i << 16));}
template <> inline short ConvertAudioSample<char, short, 1,1>(char i)					{return (short)	(i >= 0 ? (int)i << 8	: -((int)-i << 8));}

template <> inline char ConvertAudioSample<unsigned int, char, 1,1>(unsigned int u)		{return (char)	((int)((dword)u >> 24)	+ (int)std::numeric_limits<char>::min());}
template <> inline short ConvertAudioSample<unsigned int, short, 1,1>(unsigned int u)	{return (short)	((int)((dword)u >> 16)	+ (int)std::numeric_limits<short>::min());}
template <> inline char ConvertAudioSample<unsigned short, char, 1,1>(unsigned short u)	{return (char)	((int)((dword)u >> 8)	+ (int)std::numeric_limits<char>::min());}
template <> inline int ConvertAudioSample<unsigned char, int, 1,1>(unsigned char u)		{return (int)	(((int)u + (int)std::numeric_limits<char>::min()) << 24);}
template <> inline int ConvertAudioSample<unsigned short, int, 1,1>(unsigned short u)	{return (int)	(((int)u + (int)std::numeric_limits<short>::min()) << 16);}
template <> inline short ConvertAudioSample<unsigned char, short, 1,1>(unsigned char u)	{return (short)	(((int)u + (int)std::numeric_limits<char>::min()) << 8);}

template <> inline unsigned char ConvertAudioSample<int, unsigned char, 1,1>(int u)		{return (unsigned char)	(((int)u >> 24)	- (int)std::numeric_limits<char>::min());}
template <> inline unsigned short ConvertAudioSample<int, unsigned short, 1,1>(int u)	{return (unsigned short)(((int)u >> 16)	- (int)std::numeric_limits<short>::min());}
template <> inline unsigned char ConvertAudioSample<short, unsigned char, 1,1>(short u)	{return (unsigned char)	(((int)u >> 8)	- (int)std::numeric_limits<char>::min());}
template <> inline unsigned int ConvertAudioSample<char, unsigned int, 1,1>(char u)		{return (unsigned int)	(((int)u - (int)std::numeric_limits<char>::min()) << 24);}
template <> inline unsigned int ConvertAudioSample<short, unsigned int, 1,1>(short u)	{return (unsigned int)	(((int)u - (int)std::numeric_limits<short>::min()) << 16);}
template <> inline unsigned short ConvertAudioSample<char, unsigned short, 1,1>(char u)	{return (unsigned short)(((int)u - (int)std::numeric_limits<char>::min()) << 8);}

template <> inline unsigned char ConvertAudioSample<char, unsigned char, 1,1>(char u)			{return (unsigned char)		((int)u - (int)std::numeric_limits<char>::min());}
template <> inline unsigned short ConvertAudioSample<short, unsigned short, 1,1>(short u)		{return (unsigned short)	((int)u - (int)std::numeric_limits<short>::min());}
template <> inline unsigned int ConvertAudioSample<int, unsigned int, 1,1>(int u)				{return (unsigned int)		((int64)u - (int64)std::numeric_limits<int>::min());}
template <> inline char ConvertAudioSample<unsigned char, char, 1,1>(unsigned char u)			{return (char)	((int)u + (int)std::numeric_limits<char>::min());}
template <> inline short ConvertAudioSample<unsigned short, short, 1,1>(unsigned short u)		{return (short)	((int)u + (int)std::numeric_limits<short>::min());}
template <> inline int ConvertAudioSample<unsigned int, int, 1,1>(unsigned int u)				{return (int)	((int64)u + (int64)std::numeric_limits<int>::min());}

template <> inline float ConvertAudioSample<double, float, 1,1>(double d) {return (float)d;}
template <> inline double ConvertAudioSample<float, double, 1,1>(float f) {return (double)f;}

#define UNSIGNED_TO_FLOAT(TYPE, FLOAT) \
template <> inline FLOAT ConvertAudioSample<TYPE,FLOAT,1,1>(TYPE u) { \
	static constexpr double recip = 2.0 / (double)std::numeric_limits<TYPE>::max(); \
	return (FLOAT)(u * recip - 1.0); \
}
#define SIGNED_TO_FLOAT(TYPE, FLOAT) \
template <> inline FLOAT ConvertAudioSample<TYPE,FLOAT,1,1>(TYPE i) { \
	static constexpr double recip = 1.0 / (double)std::numeric_limits<TYPE>::max(); \
	return (FLOAT)(i * recip); \
}
#define FLOAT_TO_UNSIGNED(FLOAT, TYPE) \
template <> inline TYPE ConvertAudioSample<FLOAT,TYPE,1,1>(FLOAT f) { \
	static constexpr double recip = (double)std::numeric_limits<TYPE>::max() / 2.0; \
	f = std::min<FLOAT>(1, std::max<FLOAT>(-1, f));\
	return (TYPE)((f * recip) + recip); \
}
#define FLOAT_TO_SIGNED(FLOAT, TYPE) \
template <> inline TYPE ConvertAudioSample<FLOAT,TYPE,1,1>(FLOAT f) { \
	static constexpr double recip = (double)std::numeric_limits<TYPE>::max(); \
	f = std::min<FLOAT>(1, std::max<FLOAT>(-1, f));\
	return (TYPE)(f * recip); \
}
#define INTEGER_TO_INTEGER(SRC, DST) \
template <> inline DST ConvertAudioSample<SRC,DST,1,1>(SRC f) { \
	unsigned int u32 = ConvertAudioSample<SRC,unsigned int, 1,1>(f); \
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






struct GlobalAudioTime {
	float time = 0;
	
	static GlobalAudioTime& Local();
	float Get() const {return time;}
	void Set(float f) {time = f;}
	void Add(float f) {time += f;}
	void Clear() {time = 0;}
};

NAMESPACE_TOPSIDE_END

#endif
