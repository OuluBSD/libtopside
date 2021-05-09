#ifndef _Oulu_Audio_h_
#define _Oulu_Audio_h_

NAMESPACE_UPP
inline void EndianSwap(unsigned char&)	{}
inline void EndianSwap(char&)			{}
inline void EndianSwap(float& f)		{EndianSwap(*(dword*)&f);}
inline void EndianSwap(double& d)		{EndianSwap(*(uint64*)&d);}
END_UPP_NAMESPACE

NAMESPACE_OULU_BEGIN

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
	
	int GetSampleBytes() const {return var_size * channels;}
	int GetFrameBytes() const {return var_size * channels * sample_rate;}
	int GetFrameBytes(int dst_sample_rate) const {return var_size * channels * dst_sample_rate;}
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



class AudioPacketBase : Moveable<AudioPacketBase> {
	Vector<byte>		data;
	AudioFormat			fmt;
	off32				offset;
	double				time;
	
	
public:
	
	using Pool = RecyclerPool<AudioPacketBase>;
	
	AudioPacketBase() {}
	
	Vector<byte>&			Data() {return data;}
	void					Set(AudioFormat fmt, off32 offset, double time) {this->fmt = fmt; this->offset = offset; this->time = time;}
	void					SetFormat(AudioFormat fmt) {this->fmt = fmt;}
	void					SetOffset(off32 offset) {this->offset = offset;}
	void					SetTime(double seconds) {time = seconds;}
	
	const Vector<byte>&		GetData() const {return data;}
	AudioFormat				GetFormat() const {return fmt;}
	off32					GetOffset() const {return offset;}
	double					GetTime() const {return time;}
	bool					IsOffset(const off32& o) const {return offset.value == o.value;}
	int						GetSizeBytes() const {return data.GetCount();}
	
};

using AudioPacket = SharedRecycler<AudioPacketBase>;
using AudioPacketBuffer = LinkedList<AudioPacket>;

AudioPacket CreateAudioPacket();



class Audio {
	
public:
	Audio() = default;
	virtual ~Audio() = default;
	
	virtual void Exchange(AudioEx& e) = 0;
	virtual int GetQueueSize() const = 0;
	virtual AudioFormat GetAudioFormat() const = 0;
	virtual bool IsQueueFull() const = 0;
#ifdef flagOPENGL
	virtual bool PaintOpenGLTexture(int texture) {return false;}
#endif
	
};


class AudioProxy : public Audio {
	Audio* aud = 0;
	
public:
	AudioProxy() = default;
	AudioProxy(Audio* aud) : aud(aud) {}
	
	void Set(Audio* aud) {this->aud = aud;}
	
	operator bool() const {return aud != 0;}
	void Exchange(AudioEx& e) override {if (aud) aud->Exchange(e);}
	int GetQueueSize() const override {if (aud) return aud->GetQueueSize(); return 0;}
	AudioFormat GetAudioFormat() const override {if (aud) return aud->GetAudioFormat(); return AudioFormat();}
	bool IsQueueFull() const override {if (aud) return aud->IsQueueFull(); return 0;}
	
};

template <typename SRC, typename DST, bool SRC_NATIVE_ENDIAN=1, bool DST_NATIVE_ENDIAN=1> DST ConvertAudioSample(SRC v) {
	static_assert(!SRC_NATIVE_ENDIAN || !DST_NATIVE_ENDIAN, "Only native endian sample should use default implementation");
	if (!SRC_NATIVE_ENDIAN)
		EndianSwap(v);
	DST r = ConvertAudioSample<SRC,DST,1,1>(v);
	if (!DST_NATIVE_ENDIAN)
		EndianSwap(r);
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

struct AudioConverter {
	
	template <typename SRC, typename DST, bool SRC_NATIVE_ENDIAN, bool DST_NATIVE_ENDIAN>
	static void TypeConvert(const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst) {
		const SRC* src_it = (const SRC*)src;
		const SRC* src_end = src_it + src_fmt.sample_rate * src_fmt.channels;
		DST* dst_it = (DST*)dst;
		DST* dst_end = dst_it + src_fmt.sample_rate * dst_fmt.channels;
		for(int i = 0; i < src_fmt.sample_rate; i++) {
			for(int j = 0; j < dst_fmt.channels; j++) {
				SRC src_v = src_it[j % src_fmt.channels];
				DST dst_v = ConvertAudioSample<SRC, DST, SRC_NATIVE_ENDIAN, DST_NATIVE_ENDIAN>(src_v);
				*dst_it++ = dst_v;
			}
			src_it += src_fmt.channels;
		}
		ASSERT(src_it == src_end);
		ASSERT(dst_it == dst_end);
	}
	
	static bool Convert(const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst);
	static bool Convert(const AudioPacket& src, AudioPacket& dst);
	
};


class VolatileAudioBuffer;


class AudioPacketProducer {
	AudioPacketBuffer*		src = 0;
	VolatileAudioBuffer*	dst = 0;
	off32					offset;
	bool					dst_realtime = false;
	
public:
	AudioPacketProducer() {}
	
	
	void		SetOffset(off32 offset) {this->offset = offset;}
	void		SetSource(AudioPacketBuffer& src) {this->src = &src;}
	void		SetDestination(VolatileAudioBuffer& dst) {this->dst = &dst;}
	void		SetDestinationRealtime(bool b) {dst_realtime = b;}
	void		ClearDestination() {dst = 0;}
	
	
	void		ProduceAll(bool blocking=false);
	bool		ProducePacket();
	bool		IsFinished() const;
	bool		IsEmptySource() const {return src == 0;}
	off32		GetOffset() const {return offset;}
	
	operator bool() const {return IsFinished();}
	
};


class AudioPacketConsumer {
	VolatileAudioBuffer*	src = 0;
	off32					offset;
	int						leftover_size = 0;
	AudioPacket				leftover;
	
	AudioFormat				dst_fmt;
	VolatileAudioBuffer*	dst_buf = 0;
	void*					dst_mem = 0;
	byte*					dst_iter = 0;
	byte*					dst_iter_end = 0;
	int						dst_remaining = 0;
	bool					dst_realtime = 0;
	
	int						internal_count;
	
	void Consume(AudioPacket& p, int data_shift);
	
public:
	AudioPacketConsumer() {}
	
	void		SetOffset(off32 offset) {ASSERT(!HasLeftover()); this->offset = offset;}
	void		SetSource(VolatileAudioBuffer& src);
	void		SetDestination(const AudioFormat& fmt, void* dst, int src_dst_size);
	void		SetDestination(VolatileAudioBuffer& dst);
	void		SetDestinationRealtime(bool b) {dst_realtime = b;}
	void		ClearDestination();
	void		ClearLeftover() {leftover_size = 0; leftover.Clear();}
	void		TestSetOffset(off32 offset);
	
	void		ConsumeAll(bool blocking=false);
	bool		ConsumePacket();
	bool		IsFinished() const;
	bool		IsEmptySource() const {return src == 0;}
	off32		GetOffset() const {return offset;}
	bool		HasLeftover() const {return leftover_size != 0;}
	
	operator bool() const {return IsFinished();}
	
};


class VolatileAudioBuffer : public Audio, public RealtimePacketBuffer<AudioPacket> {
	AudioFormat preferred_fmt;
	One<AudioPacketConsumer> consumer;
	off32 dbg_offset;
	
public:
	using Buffer = RealtimePacketBuffer<AudioPacket>;
	
	VolatileAudioBuffer() = default;
	
	#if DEBUG_AUDIO_PIPE
	AudioPacket	Get(off32 offset) {
		AudioPacket p = Buffer::Get(offset);
		if (p.IsEmpty()) {
			AUDIOLOG("error: got empty packet in VolatileAudioBuffer");
		}
		return p;
	}
	void Put(const AudioPacket& p, bool realtime) {
		off32 off = p->GetOffset();
		ASSERT(off == dbg_offset);
		dbg_offset.value = off.value + 1;
		Buffer::Put(p, realtime);
	}
	#endif
	
	void		SetSize(AudioFormat fmt, int frames) {preferred_fmt = fmt; Buffer::SetLimit(frames);}
	
	void		Exchange(AudioEx& e)	override;
	int			GetQueueSize() const	override {return Buffer::GetQueueSize();}
	AudioFormat	GetAudioFormat() const	override {return preferred_fmt;}
	bool		IsQueueFull() const		override;
	
	
	
};




class AudioStream : public virtual RealtimeStream {
	
	
public:
	using Parent = ComponentBase;
	
	virtual ~AudioStream() {}
	
	virtual Audio&	GetAudio() = 0;
	virtual void	FillAudioBuffer() = 0;
	virtual void	DropAudioBuffer() = 0;
	
};


NAMESPACE_OULU_END

#endif
