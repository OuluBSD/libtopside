#ifndef _SerialMach_Formats_h_
#define _SerialMach_Formats_h_

NAMESPACE_SERIAL_BEGIN


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

struct MidiFormat :
	public SampleBase<MidiSample>,
	public DimBase<1>,
	public SparseTimeSeriesBase
{
	static constexpr int base_size =
		sizeof(SampleBase<MidiSample>) +
		sizeof(DimBase<1>) +
		sizeof(SparseTimeSeriesBase);
	
	void SetDefault() {SampleBase<MidiSample>::SetDefault(); DimBase<1>::SetDefault();}
	int GetFrameSize() const;
	int GetMinBufSamples() const {return 2;}
	String ToString() const;
	bool IsValid() const;
	bool IsSame(const MidiFormat& fmt) const;
	
	
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
		MidiFormat			mid;
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
	bool IsMidi()  const {return vd.val == ValCls::MIDI;}
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
	void SetMidi();
	
	operator const AudioFormat&() const {ASSERT(IsAudio()); return aud;}
	operator       AudioFormat&()       {ASSERT(IsAudio()); return aud;}
	operator const VideoFormat&() const {ASSERT(IsVideo()); return vid;}
	operator       VideoFormat&()       {ASSERT(IsVideo()); return vid;}
	operator const MidiFormat&()  const {ASSERT(IsMidi());  return mid;}
	operator       MidiFormat&()        {ASSERT(IsMidi());  return mid;}
	
	
};

NAMESPACE_SERIAL_END

#endif
