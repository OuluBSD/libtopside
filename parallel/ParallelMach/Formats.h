#ifndef _ParallelMach_Formats_h_
#define _ParallelMach_Formats_h_

NAMESPACE_PARALLEL_BEGIN


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
	
	int		GetFrameSize() const;
	String	ToString() const;
	bool	IsValid() const;
	bool	IsSame(const AudioFormat& fmt) const;
	
	
	byte pad[STD_FMT_SIZE - base_size - 4];
};

#define TEST_TRIVIAL(x) \
	static_assert(std::is_trivially_constructible<x>::value == true, #x " must be trivial to construct");

struct VideoFormat :
	public SampleBase<LightSampleFD>,
	public DimBase<2>,
	public TimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<LightSampleFD>) +
		sizeof(DimBase<2>) +
		sizeof(TimeSeriesBase);
		
	TEST_TRIVIAL(SampleBase<LightSampleFD>)
	TEST_TRIVIAL(DimBase<2>)
	TEST_TRIVIAL(TimeSeriesBase)
	
	void	Set(LightSampleFD::Type t, int w, int h, int freq, int sample_rate);
	void	SetCubemap() {cubemap = true;}
	
	int		GetFrameSize() const;
	String	ToString() const;
	bool	IsValid() const;
	bool	IsCubemap() const {return cubemap;}
	bool	IsSame(const VideoFormat& fmt) const;
	int		GetChannels() const {return SampleBase<LightSampleFD>::GetPackedCount();}
	
	
	bool	cubemap;
	byte	pad[STD_FMT_SIZE - base_size - 5];
};

struct VolumeFormat :
	public SampleBase<BinarySample>,
	public DimBase<3>,
	public TimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<BinarySample>) +
		sizeof(DimBase<3>) +
		sizeof(TimeSeriesBase);
	
	void	SetDefault() {SampleBase<BinarySample>::SetDefault(); DimBase<3>::SetDefault(); TimeSeriesBase::SetDefault();}
	void	Set(BinarySample::Type t, int w, int h, int d, int freq, int sample_rate);
	
	int		GetFrameSize() const;
	String	ToString() const;
	bool	IsValid() const;
	bool	IsSame(const VolumeFormat& fmt) const;
	int		GetScalar() const {return DimBase<3>::GetVolume();} // TODO fix unit semantics
	bool	IsCopyCompatible(const VolumeFormat& b) const;
	int		GetChannels() const {return SampleBase<BinarySample>::GetPackedCount();}
	
	byte pad[STD_FMT_SIZE - base_size - 4];
};

struct FboFormat :
	public SampleBase<BinarySample>,
	public DimBase<3>,
	public TimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<LightSampleFD>) +
		sizeof(DimBase<3>) +
		sizeof(TimeSeriesBase);
	
	void Set(BinarySample::Type t, int w, int h, int d, int freq, int sample_rate);
	
	int		GetFrameSize() const;
	String	ToString() const;
	bool	IsValid() const;
	bool	IsSame(const FboFormat& fmt) const;
	int		GetChannels() const {return SampleBase<BinarySample>::GetPackedCount();}
	
	byte pad[STD_FMT_SIZE - base_size - 4];
};

struct MidiFormat :
	public SampleBase<MidiSample>,
	public DimBase<1>,
	public SparseTimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<MidiSample>) +
		sizeof(DimBase<1>) +
		sizeof(SparseTimeSeriesBase);
	
	void	SetDefault() {SampleBase<MidiSample>::SetDefault(); DimBase<1>::SetDefault();}
	int		GetFrameSize() const;
	String	ToString() const;
	bool	IsValid() const;
	bool	IsSame(const MidiFormat& fmt) const;
	
	
	byte pad[STD_FMT_SIZE - base_size - 4];
};

struct DataFormat
{
	
	
	
	byte pad[STD_FMT_SIZE - 0];
};

struct EventFormat :
	public SampleBase<EventSample>,
	public DimBase<1>,
	public SparseTimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<EventSample>) +
		sizeof(DimBase<1>) +
		sizeof(SparseTimeSeriesBase);
	
	String	ToString() const;
	bool	IsValid() const;
	bool	IsSame(const EventFormat& fmt) const;
	int		GetFrameSize() const;
	
	
	byte pad[STD_FMT_SIZE - base_size - 4];
};

struct ProgFormat :
	public SampleBase<BinarySample>,
	public DimBase<1>,
	public SparseTimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<BinarySample>) +
		sizeof(DimBase<1>) +
		sizeof(SparseTimeSeriesBase);
	
	String	ToString() const;
	bool	IsValid() const;
	bool	IsSame(const ProgFormat& fmt) const;
	int		GetFrameSize() const;
	
	
	byte pad[STD_FMT_SIZE - base_size - 4];
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
		VolumeFormat		vol;
		MidiFormat			mid;
		DataFormat			dat;
		EventFormat			ev;
		FboFormat			fbo;
		ProgFormat			prog;
	};
	
public:
	Format() {memset(data, 0, sizeof(data));}
	Format(const Format& f) : vd(f.vd) {memcpy(data, f.data, sizeof(data));}
	
	String	ToString() const;
	DevCls	GetDevSpec() const {return vd.dev;}
	int		GetSampleSize() const;
	int		GetScalar() const;
	int		GetFrameSize() const;
	double	GetFrameSeconds() const;
	
	bool IsOrder() const {return vd.val == ValCls::ORDER;}
	bool IsAudio() const {return vd.val == ValCls::AUDIO;}
	bool IsVideo() const {return vd.val == ValCls::VIDEO;}
	bool IsVolume() const {return vd.val == ValCls::VOLUME;}
	bool IsMidi()  const {return vd.val == ValCls::MIDI;}
	bool IsEvent() const {return vd.val == ValCls::EVENT;}
	bool IsFbo()   const {return vd.val == ValCls::FBO;}
	bool IsProg()   const {return vd.val == ValCls::PROG;}
	bool IsValid() const;
	bool IsSame(const Format& f) const; // {return FormatBase::IsSame(f);}
	bool IsCopyCompatible(const Format& f) const; // {return FormatBase::IsCopyCompatible(f);}
	bool operator ==(const Format& f); // {return IsSame(f);}
	bool operator !=(const Format& f); // {return !IsSame(f);}
	void operator=(const Format& f);
	void SetDefault(ValDevCls t); // {FormatBase::template SetDefault<DevSpec>();}
	void Clear();
	bool HasData() const;
	
	void SetAudio(DevCls dev, SoundSample::Type t, int channels, int freq, int sample_rate);
	void SetOrder(DevCls dev);
	void SetReceipt(DevCls dev);
	void SetMidi(DevCls dev);
	void SetVolume(DevCls dev, BinarySample::Type t, int w, int h, int d, int freq, int sample_rate);
	void SetVideo(DevCls dev, LightSampleFD::Type t, int w, int h, int freq, int sample_rate);
	void SetVideo(DevCls dev, const VideoFormat& vid);
	void SetFbo(DevCls dev, BinarySample::Type t, int w, int h, int d, int freq, int sample_rate);
	void SetEvent(DevCls dev);
	void SetProg(DevCls dev);
	
	operator const AudioFormat&() const {ASSERT(IsAudio()); return aud;}
	operator       AudioFormat&()       {ASSERT(IsAudio()); return aud;}
	operator const VideoFormat&() const {ASSERT(IsVideo()); return vid;}
	operator       VideoFormat&()       {ASSERT(IsVideo()); return vid;}
	operator const VolumeFormat&() const {ASSERT(IsVolume()); return vol;}
	operator       VolumeFormat&()       {ASSERT(IsVolume()); return vol;}
	operator const MidiFormat&()  const {ASSERT(IsMidi());  return mid;}
	operator       MidiFormat&()        {ASSERT(IsMidi());  return mid;}
	operator const EventFormat&() const {ASSERT(IsEvent()); return ev;}
	operator       EventFormat&()       {ASSERT(IsEvent()); return ev;}
	operator const FboFormat&() const   {ASSERT(IsFbo()); return fbo;}
	operator       FboFormat&()         {ASSERT(IsFbo()); return fbo;}
	operator const ProgFormat&() const  {ASSERT(IsProg()); return prog;}
	operator       ProgFormat&()        {ASSERT(IsProg()); return prog;}
	
	
};

NAMESPACE_PARALLEL_END

#endif
