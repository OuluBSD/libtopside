#ifndef _EcsSDL2_AudioOut_h_
#define _EcsSDL2_AudioOut_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2AudioOutputComponent :
	public Component<SDL2AudioOutputComponent>,
	public AudioSink
{
	One<OOSDL2::AudioOutput> obj;
	AudioProxy empty_aud;
    RealtimeSourceConfig aconfig;
	
	
public:
	RTTI_COMP1(SDL2AudioOutputComponent, AudioSink)
	VIS_COMP_0_1(Audio)
	COPY_PANIC(SDL2AudioOutputComponent);
	IFACE_CB(AudioSink);
	IFACE_GENERIC;
	
	SDL2AudioOutputComponent() = default;
	
	void			Initialize() override;
	void			Uninitialize() override;
	void			Visit(RuntimeVisitor& vis) override {}
	
	AudioFormat		GetFormat(AudCtx) override;
	Audio&			GetValue(AudCtx) override;
	
	/*SystemAudio&	BeginPlay() override {return obj ? obj->GetSystemAudio() : empty_aud;}
	void			CommitPlay() override {}
	void			UndoPlay() override {ASSERT_(0, "UndoPlay is not implemented");}
	bool			IsAudioSampleFloating() override {return obj ? obj->IsSampleFloating() : 0;}
	int				GetAudioSampleRate() override {return obj ? obj->GetSampleRate() : 0;}
	int				GetAudioChannels() override {return obj ? obj->GetChannels() : 0;}
	int				GetAudioFrequency() override {return obj ? obj->GetFrequency() : 0;}
	int				GetAudioSampleSize() override {return obj ? obj->GetSampleSize() : 0;}*/
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::AudioOutput* GetOOSDL2() {return &*obj;}
	
	void SetAudioSyncInterval(double seconds) {aconfig.sync_dt = seconds;}
	
};



NAMESPACE_TOPSIDE_END

#endif
