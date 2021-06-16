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
	COMP_DEF_VISIT
	
	SDL2AudioOutputComponent() = default;
	
	void			Initialize() override;
	void			Uninitialize() override;
	
	void			Forward(FwdScope& fwd) override;
	void			ForwardExchange(FwdScope& fwd) override;
	
	AudioFormat		GetFormat(AudCtx) override;
	Audio&			GetValue(AudCtx) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::AudioOutput* GetOOSDL2() {return &*obj;}
	
	void SetAudioSyncInterval(double seconds) {aconfig.sync_dt = seconds;}
	
};



NAMESPACE_TOPSIDE_END

#endif
