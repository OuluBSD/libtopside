#ifndef _AtomLocal_Midi_h_
#define _AtomLocal_Midi_h_

#if 0

NAMESPACE_SERIAL_BEGIN


class MixerContextConnector :
	public Connector<MixerContextConnector>
{
	String last_error;
	String post_load_file_path;
	
public:
	RTTI_CONN0(MixerContextConnector)
	COPY_PANIC(MixerContextConnector);
	
	MixerContextConnector();
	
	void Initialize() override;
	void Uninitialize() override;
	void PostLoadFileAny(String path) {post_load_file_path = path;}
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MixerChannelContextConnector :
	public Connector<MixerChannelContextConnector>
{
	String last_error;
	
public:
	RTTI_CONN0(MixerChannelContextConnector)
	COPY_PANIC(MixerChannelContextConnector);
	
	MixerChannelContextConnector();
	
	void Initialize() override;
	void Uninitialize() override;
	
	String GetLastError() const {return last_error;}
	
};


class MixerChannelInputComponent :
	public Component<MixerChannelInputComponent>,
	public AudioSource,
	public AudioSink
{
	String last_error;
	
public:
	RTTI_COMP2(MixerChannelInputComponent, AudioSource, AudioSink)
	COPY_PANIC(MixerChannelInputComponent);
	COMP_DEF_VISIT
	
	MixerChannelInputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	// AudioSource
	AudioStream&	GetStream(AudCtx) override {TODO}
	void				BeginStream(AudCtx) override {TODO}
	void				EndStream(AudCtx) override {TODO}
	
	// AudioSink
	AudioFormat	GetFormat(AudCtx) override {TODO}
	Audio&		GetValue(AudCtx) override {TODO}
	
	String GetLastError() const {return last_error;}
	
};

class MixerChannelOutputComponent :
	public Component<MixerChannelOutputComponent>,
	public AudioSource,
	public AudioSink
{
	String last_error;
	
public:
	RTTI_COMP2(MixerChannelOutputComponent, AudioSource, AudioSink)
	COPY_PANIC(MixerChannelOutputComponent);
	COMP_DEF_VISIT
	
	MixerChannelOutputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	// AudioSource
	AudioStream&	GetStream(AudCtx) override;
	void				BeginStream(AudCtx) override;
	void				EndStream(AudCtx) override;
	
	// AudioSink
	AudioFormat	GetFormat(AudCtx) override;
	Audio&		GetValue(AudCtx) override;
	
	String GetLastError() const {return last_error;}
	
};


class MixerAudioSourceComponent :
	public Component<MixerAudioSourceComponent>,
	public AudioSource,
	public AudioSink
{
	String last_error;
	
public:
	RTTI_COMP2(MixerAudioSourceComponent, AudioSource, AudioSink)
	COPY_PANIC(MixerAudioSourceComponent);
	COMP_DEF_VISIT
	
	MixerAudioSourceComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	// AudioSource
	AudioStream&		GetStream(AudCtx) override;
	void				BeginStream(AudCtx) override;
	void				EndStream(AudCtx) override;
	
	// AudioSink
	AudioFormat	GetFormat(AudCtx) override;
	Audio&		GetValue(AudCtx) override;
	
	String GetLastError() const {return last_error;}
	
};




class MidiFileComponent :
	public Component<MidiFileComponent>,
	public EventSource
{
	String last_error;
	MidiIO::File file;
	Vector<int> track_i;
	double song_dt = 0;
	MidiFrame tmp;
	
public:
	RTTI_COMP1(MidiFileComponent, EventSource)
	COPY_PANIC(MidiFileComponent);
	COMP_DEF_VISIT
	
	MidiFileComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	//void EmitMidi(double dt) override;
	//bool IsSupported(DevType type) override {return true;}
	void OnLink(SinkProv sink, Cookie src_c, Cookie sink_c) override {TODO}
	bool OpenFilePath(String path);
	void Clear();
	void CollectTrackEvents(int i);
	void EmitTrack(int i);
	void DumpMidiFile();
	
	// EventSource
	EventStream&		GetStream(EvCtx) override {TODO}
	void				BeginStream(EvCtx) override {TODO}
	void				EndStream(EvCtx) override {TODO}
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


NAMESPACE_SERIAL_END

#endif
#endif
