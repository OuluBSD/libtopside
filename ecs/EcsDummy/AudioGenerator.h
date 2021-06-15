#ifndef _EcsDummy_AudioGenerator_h_
#define _EcsDummy_AudioGenerator_h_

NAMESPACE_TOPSIDE_BEGIN


template <class T>
class DummySoundGenerator
{
	Vector<T> frame;
	int frame_part_size = 0;
	
public:
	DummySoundGenerator() {}
	void Play(int frame_offset, const AudioPacket& p) {
		int total_bytes = frame.GetCount() * sizeof(T);
		frame_offset = frame_offset % total_bytes;
		int copy_size = p->GetFormat().GetFrameSize();
		p->Data().SetCount(copy_size, 0);
		int frame_remaining = total_bytes - frame_offset;
		byte* dst = p->Data().Begin();
		byte* src = (byte*)(void*)frame.Begin() + frame_offset;
		
		// 2 parts
		if (frame_remaining < copy_size) {
			int right_side = frame_remaining;
			int left_side = copy_size - frame_remaining;
			memcpy(dst, src, right_side);
			src = (byte*)(void*)frame.Begin();
			memcpy(dst, src, left_side);
			//frame_offset = left_side;
		}
		// 1part
		else {
			memcpy(dst, src, copy_size);
			//frame_offset = (frame_offset + copy_size) % total_bytes;
		}
	}
	
	void GenerateStereoSine(const AudioFormat& fmt) {
		ASSERT(fmt.IsSampleType<T>());
		double pan_loop_seconds = 2.0;
		int tone_mul = 4;
		int pan_frames = (int)(fmt.freq * pan_loop_seconds / fmt.sample_rate);
		int pan_samples = pan_frames * fmt.sample_rate;
		int pan_i = 0;
		frame_part_size = fmt.sample_rate * fmt.channels;
		int size = frame_part_size * pan_frames;
		frame.SetCount(size);
		T* f = frame.Begin();
		for (int p = 0; p < pan_frames; p++) {
			for(int i = 0; i < fmt.sample_rate; i++) {
				double tonerad = tone_mul * M_2PI * (double)i / (double)fmt.sample_rate;
				double tonesin = FastSin(tonerad);
				double tonevol = (tonesin + 1.0) * 0.5;
				double panrad = M_2PI * (double)pan_i / (double)pan_samples;
				double pansin = FastSin(panrad);
				double panvol = (pansin + 1.0) * 0.5;
				for(int j = 0; j < fmt.channels; j++) {
					double pan = (j % 2 == 0) ? panvol : (1.0 - panvol);
					//pan = j == 0  ? 1.0 : 0.0;
					double value = pan * tonesin;
					//value = tonesin;
					*f = ConvertAudioSample<double, T>(value);
					f++;
				}
				pan_i++;
			}
		}
		ASSERT(f == frame.End());
	}
};

class DummySoundGeneratorAudio :
	public SimpleAudio
{
	DummySoundGenerator<uint8> gen;
	AudioFormat fmt;
	
public:
	RTTI_DECL1(DummySoundGeneratorAudio, SimpleAudio)
	DummySoundGeneratorAudio();
	
	void StorePacket(AudioPacket& p) override;
	/*void Exchange(AudioEx& e) override;
	AudioFormat GetFormat() const override;
	int GetQueueSize() const override;
	bool IsQueueFull() const override;*/
	
	
};

class DummySoundGeneratorStream :
	public SimpleAudioStream
{
public:
	DummySoundGeneratorAudio gen;
	
public:
	RTTI_DECL1(DummySoundGeneratorStream, SimpleAudioStream)
	DummySoundGeneratorStream() : SimpleAudioStream(gen) {}
	
	
	
};

class DummySoundGeneratorComponent :
	public DevComponent<CenterSpec,AudioSpec,DummySoundGeneratorComponent>,
	public EventSink,
	public OrderSink,
	public AudioSource
{
	DummySoundGeneratorStream gen;
	String last_error;
	int mode = 0;
	int preset_i = -1;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
	void GenerateStereoSine(const AudioFormat& fmt);
	
protected:
	struct LocalSinkValue : public SimpleOrder {
		
		void StorePacket(OrderPacket& p) override {TODO}
		
	};
	
	
	LocalSinkValue		sink_value;
	
public:
	using Component = DevComponent<CenterSpec,AudioSpec,DummySoundGeneratorComponent>;
	RTTI_DCOMP3(DummySoundGeneratorComponent, EventSink, OrderSink, AudioSource)
	VIS_COMP_1_2(Audio, Order, Event)
	COPY_PANIC(DummySoundGeneratorComponent);
	IFACE_GENERIC;
	IFACE_CB(OrderSink);
	IFACE_CB(EventSink);
	IFACE_CB(AudioSource);
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.src.test")
	COMP_MAKE_ACTION_END
	
	DummySoundGeneratorComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	void ForwardExchange(FwdScope& fwd) override;
	
	// OrderSink
	OrderFormat		GetFormat(OrdCtx) override {TODO}
	Order&			GetValue(OrdCtx) override {return sink_value;}
	bool			ReadFrame() {TODO}
	bool			ProcessDeviceFrame() {TODO}
	
	// EventSink
	EventFormat		GetFormat(EvCtx) override {TODO}
	Event&			GetValue(EvCtx) override {TODO}
	
	// AudioSource
	AudioStream&	GetStream(AudCtx) override;
	void			BeginStream(AudCtx) override;
	void			EndStream(AudCtx) override;
	void			StorePacket(AudioPacket& p) {gen.gen.StorePacket(p);}
	
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


NAMESPACE_TOPSIDE_END

#endif
