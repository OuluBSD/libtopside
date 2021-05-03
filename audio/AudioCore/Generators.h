#ifndef _AudioCore_Generators_h_
#define _AudioCore_Generators_h_

NAMESPACE_OULU_BEGIN

template <class T>
class DummySoundGenerator {
	Vector<T> frame;
	int frame_offset = 0;
	int frame_part_size = 0;
	
public:
	DummySoundGenerator() {}
	void Play(const RealtimeSourceConfig& config, Audio& aud) {
		if (frame.IsEmpty())
			GenerateStereoSine(aud.GetAudioFormat());
		
		TODO
		//aud.Put(frame.Begin() + frame_offset, frame_part_size * sizeof(float), config.sync);
		
		frame_offset = (frame_offset + frame_part_size) % frame.GetCount();
		ASSERT(frame_offset % aud.GetAudioFormat().sample_rate == 0);
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
		double min = std::numeric_limits<T>::min();
		double max = std::numeric_limits<T>::max();
		double range = max - min;
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
		frame_offset = 0;
	}
};


class SoundGeneratorComponent :
	public Component<SoundGeneratorComponent>,
	public MidiSink,
	public AudioSource
{
	DummySoundGenerator<float> gen_f32;
	DummySoundGenerator<unsigned short> gen_u16;
	String last_error;
	int mode = 0;
	int preset_i = -1;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
	void GenerateStereoSine(const AudioFormat& fmt);
	
public:
	COPY_PANIC(SoundGeneratorComponent);
	IFACE_CB(MidiSink);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	
	SoundGeneratorComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void RecvMidi(const MidiFrame& e) override;
	void Configure(const Midi::File& file) override;
	
	// Audio
	AudioStream&	GetAudioSource() override;
	void			BeginAudioSource() override;
	void			EndAudioSource(bool any_sink_consumed) override;
	
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


NAMESPACE_OULU_END

#endif
