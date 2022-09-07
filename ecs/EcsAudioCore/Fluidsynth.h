#ifndef _EcsAudioCore_Fluidsynth_h_
#define _EcsAudioCore_Fluidsynth_h_

#if HAVE_FLUIDSYNTH

NAMESPACE_TOPSIDE_BEGIN


class FluidsynthComponent :
	public Component<FluidsynthComponent>,
	public AudioSource,
	public MidiSink
{
	String last_error;
	int mode = 0;
	int track_i = -1;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
public:
	RTTI_COMP2(FluidsynthComponent, AudioSource, MidiSink)
	VIS_COMP_1_1(Audio, Midi)
	COPY_PANIC(FluidsynthComponent);
	IFACE_CB(MidiSink);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
	FluidsynthComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void OpenTrackListener(int track_i);
	//void RecvMidi(const MidiFrame& e) override;
	//void Configure(const MidiIO::File& file) override;
	
	// AudioSource
	AudioStream&		GetStream(AudCtx) override;
	void				BeginStream(AudCtx) override;
	void				EndStream(AudCtx) override;
	
	// MidiSink
	MidiFormat			GetFormat(MidCtx) override;
	Midi&				GetValue(MidCtx) override;
	
	String GetLastError() const {return last_error;}
	
	
};

using FluidsynthComponentRef = RefT_Entity<FluidsynthComponent>;



PREFAB_BEGIN(CompleteFluidsynth)
		//MixerChannelContextConnector,
		FluidsynthComponent
		//MixerChannelOutputComponent
PREFAB_END;



class FluidsynthSystem :
	public System<FluidsynthSystem>
{
	LinkedList<FluidsynthComponentRef> comps;
	LinkedList<FluidsynthComponentRef> track_comps;
	
	Fluidsynth fs;
	
	
	SYS_RTTI(FluidsynthSystem)
	void Visit(RuntimeVisitor& vis) override {
		vis && comps
			&& track_comps;
	}
	
public:
	SYS_CTOR(FluidsynthSystem)
	
	const LinkedList<FluidsynthComponentRef>& GetContext() const {return comps;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
protected:
	friend class FluidsynthComponent;
	
	void Add(FluidsynthComponentRef comp);
	void Remove(FluidsynthComponentRef comp);
	void Assign(const MidiIO::File& file, int track_i, FluidsynthComponentRef comp);
	
};



NAMESPACE_TOPSIDE_END

#endif
#endif
