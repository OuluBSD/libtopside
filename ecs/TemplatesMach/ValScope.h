#ifndef _TemplatesMach_ValScope_h_
#define _TemplatesMach_ValScope_h_

NAMESPACE_ECS_BEGIN



/*static String TypeStringT(const char* t) {
	String s;
	s << ValSpec::GetName() << t;
	return s;
}*/

#define STD_FMT_SIZE (4*16)

struct AudioFormat :
	public SampleBase<SoundSample>,
	public DimBase<1>,
	public TimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<SoundSample>) +
		sizeof(DimBase<1>) +
		sizeof(TimeSeriesBase);
	
	void Set(SoundSample::Type t, int channels, int freq, int sample_rate);
	
	int GetFrameSize() const;
	int GetMinBufSamples() const {return TimeSeriesBase::GetSampleRate() * 2;}
	String ToString() const;
	bool IsValid() const;
	bool IsSame(const AudioFormat& fmt) const;
	
	
	byte pad[STD_FMT_SIZE - base_size - 4];
};

struct VideoFormat :
	public SampleBase<LightSampleFD>,
	public DimBase<2>,
	public TimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<LightSampleFD>) +
		sizeof(DimBase<2>) +
		sizeof(TimeSeriesBase);
	
	int GetFrameSize() const;
	int GetMinBufSamples() const {return 2;}
	String ToString() const;
	bool IsValid() const;
	bool IsSame(const VideoFormat& fmt) const;
	
	
	byte pad[STD_FMT_SIZE - base_size - 4];
};

struct DataFormat {
	
	
	
	byte pad[STD_FMT_SIZE - 0];
};

struct EventFormat {
	
	
	
	byte pad[STD_FMT_SIZE - 0];
};

#define TEST_FORMAT(x) \
	static_assert(std::is_trivially_constructible<x>::value == true, #x " must be trivial to construct"); \
	static_assert(sizeof(x) == STD_FMT_SIZE, "Expecting standard format size in " #x);

TEST_FORMAT(AudioFormat)
TEST_FORMAT(VideoFormat)
TEST_FORMAT(DataFormat)
TEST_FORMAT(EventFormat)

class Format : RTTIBase {
public:
	RTTI_DECL0(Format)
	
	ValDevCls			vd;
	union {
		byte				data[STD_FMT_SIZE];
		AudioFormat			aud;
		VideoFormat			vid;
		DataFormat			dat;
		EventFormat			ev;
	};
	
public:
	Format() {memset(data, 0, sizeof(data));}
	Format(const Format& f) : vd(f.vd) {memcpy(data, f.data, sizeof(data));}
	
	String ToString() const;
	DevCls GetDevSpec() const {return vd.dev;}
	int GetSampleSize() const;
	int GetArea() const;
	int GetFrameSize() const;
	double GetFrameSeconds() const;
	int GetMinBufSamples() const;
	
	bool IsAudio() const {return vd.val == ValCls::AUDIO;}
	bool IsVideo() const {return vd.val == ValCls::VIDEO;}
	bool IsValid() const;
	bool IsSame(const Format& f) const; // {return FormatBase::IsSame(f);}
	bool IsCopyCompatible(const Format& f) const; // {return FormatBase::IsCopyCompatible(f);}
	bool operator ==(const Format& f); // {return IsSame(f);}
	bool operator !=(const Format& f); // {return !IsSame(f);}
	void operator=(const Format& f);
	void SetDefault(ValDevCls t); // {FormatBase::template SetDefault<DevSpec>();}
	void Clear();
	bool HasData() const;
	
	void SetAudio(SoundSample::Type t, int channels, int freq, int sample_rate);
	void SetOrder();
	void SetReceipt();
	
	operator const AudioFormat&() const {ASSERT(IsAudio()); return aud;}
	operator       AudioFormat&()       {ASSERT(IsAudio()); return aud;}
	operator const VideoFormat&() const {ASSERT(IsVideo()); return vid;}
	operator       VideoFormat&()       {ASSERT(IsVideo()); return vid;}
	
	
};


typedef dword PacketId;


class PacketValue :
	RTTIBase,
	Moveable<PacketValue>
{
	Vector<byte>		data;
	Format				fmt;
	off32				offset;
	double				time;
	PacketId			id = 0;
	TypeCls				custom_data = 0;
	
public:
	using Pool = RecyclerPool<PacketValue>;
	
	//static const int def_sample_rate = Format::def_sample_rate;
	
	
	RTTI_DECL0(PacketValue);
	PacketValue(off32 offset) : offset(offset) {}
	~PacketValue() {data.Clear(); StopTracking(this);}
	
	Vector<byte>&			Data() {return data;}
	void					Set(Format fmt, double time) {this->fmt = fmt; this->time = time;}
	void					SetFormat(Format fmt) {this->fmt = fmt;}
	void					SetTime(double seconds) {time = seconds;}
	void					SetTrackingId(PacketId i) {id = i;}
	void					Clear() {data.SetCount(0); fmt.Clear(); offset.Clear(); time = 0; id = 0; custom_data = 0;}
	void					SetOffset(off32 o) {offset = o;}
	
	const Vector<byte>&		GetData() const {return data;}
	Format					GetFormat() const {return fmt;}
	off32					GetOffset() const {return offset;}
	double					GetTime() const {return time;}
	bool					IsOffset(const off32& o) const {return offset.value == o.value;}
	int						GetSizeBytes() const {return data.GetCount();}
	int						GetSizeTotalSamples() const {return data.GetCount() / fmt.GetSampleSize();}
	int						GetSizeChannelSamples() const {return data.GetCount() / (fmt.GetArea() * fmt.GetSampleSize());}
	void					CheckTracking(TrackerInfo info);
	void					StopTracking(TrackerInfo info);
	PacketId				GetTrackingId() const {return id;}
	bool					HasTrackingId() const {return id != 0;}
	bool					IsBuffered() const {return fmt.vd.val.type == ValCls::AUDIO;}
	
	String					ToString() const;
	
	template <class T> T& SetData() {
		custom_data = AsTypeCls<T>();
		data.SetCount(sizeof(T));
		byte* b = &data[0];
		memset(b,0, sizeof(T));
		return *(T*)b;
	}
	
	template <class T> bool IsData() {return custom_data == AsTypeCls<T>();}
	bool IsCustomData() const {return custom_data != 0;}
	
	template <class T> T& GetData() {
		ASSERT(custom_data == AsTypeCls<T>());
		ASSERT(data.GetCount() == sizeof(T));
		byte* b = &data[0];
		return *(T*)b;
	}
	
#if HAVE_OPENGL
	virtual bool PaintOpenGLTexture(int texture);
#endif
	
};


using Packet			= SharedRecycler<PacketValue>;
using PacketBuffer		= LinkedList<Packet>;
using RecRefBase		= RecyclerRefBase<PacketValue>;

static Packet CreatePacket(off32 off) {
	PacketValue* obj = PacketValue::Pool::StaticPool().New(off);
	RecRefBase* base = RecRefBase::Pool::StaticPool().New();
	base->SetObj(obj);
	return Packet(obj, base);
}

void PacketTracker_Track(const char* fn, const char* file, int line, PacketValue& p);
void PacketTracker_Checkpoint(const char* fn, const char* file, int line, PacketValue& p);
void PacketTracker_StopTracking(const char* fn, const char* file, int line, PacketValue& p);


struct ValStreamState : RTTIBase {
	RTTI_DECL0(ValStreamState)
	Format fmt;
	TimeStop frame_time;
	double total_seconds = 0;
	double frame_seconds = 0;
	double last_sync_sec = 0;
	int frames = 0;
	int frames_after_sync = 0;
	int sink_frame = 0;
	bool is_sync = 0;
	
	void Clear();
	void Reset();
	void Step();
};


class ComponentExtBase;

class PacketBufferParent :
	public RefScopeEnabler<PacketBufferParent, ComponentExtBase>,
	RTTIBase
{
public:
	RTTI_DECL0(PacketBufferParent)
	
};


struct PacketBufferBase :
	public RefScopeEnabler<PacketBufferBase, PacketBufferParent>,
	RTTIBase
{
public:
	RTTI_DECL0(PacketBufferBase)
	
	PacketBuffer buf;
	int max_packets = 2;
	
	virtual void FillBuffer() = 0;
	virtual void Close() = 0;
	virtual void Clear() {buf.Clear();}
	bool IsQueueFull() const {return buf.GetCount() >= max_packets;}
	void StorePacket(Packet& p);
	
};

struct PacketBufferBasePtr :
	RTTIBase
{
	Ref<PacketBufferBase> base;
	
	RTTI_DECL0(PacketBufferBasePtr)
	
	
};


NAMESPACE_ECS_END

#endif
