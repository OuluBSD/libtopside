#ifndef _AudioCore_System_h_
#define _AudioCore_System_h_


NAMESPACE_TOPSIDE_BEGIN


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
	VIS_COMP_1_1(Audio, Audio)
	COPY_PANIC(MixerChannelInputComponent);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
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
	VIS_COMP_1_1(Audio, Audio)
	COPY_PANIC(MixerChannelOutputComponent);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
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
	VIS_COMP_1_1(Audio, Audio)
	COPY_PANIC(MixerAudioSourceComponent);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
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
	VIS_COMP_1_0(Event)
	COPY_PANIC(MidiFileComponent);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
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





/*PREFAB_BEGIN(CompleteMixer)
		//MixerContextConnector
PREFAB_END;*/

PREFAB_BEGIN(CompleteMixerChannel)
		//MixerChannelContextConnector,
		MixerChannelInputComponent,
		MixerChannelOutputComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMixerOutput)
		//MixerChannelContextConnector,
		MixerChannelInputComponent,
		MixerAudioSourceComponent
PREFAB_END;

PREFAB_BEGIN(MidiFileController)
		MidiFileComponent
PREFAB_END;

NAMESPACE_TOPSIDE_END


#endif
