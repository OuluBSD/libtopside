#ifndef _AudioCore_Generators_h_
#define _AudioCore_Generators_h_

NAMESPACE_OULU_BEGIN


class SoundGeneratorComponent :
	public Component<SoundGeneratorComponent>,
	public MidiSink,
	public AudioSource
{
	Vector<float> frame;
	String last_error;
	int mode = 0;
	int preset_i = -1;
	int frame_offset = 0;
	int frame_part_size = 0;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
	void GenerateStereoSine(const SoundFormat& fmt);
	
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
	void EmitAudioSource(float dt) override;
	void Play(const AudioSinkConfig& config, Sound& snd) override;
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


NAMESPACE_OULU_END

#endif
