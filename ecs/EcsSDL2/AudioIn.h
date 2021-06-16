#ifndef _EcsSDL2_AudioIn_h_
#define _EcsSDL2_AudioIn_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2AudioInputComponent :
	public Component<SDL2AudioInputComponent>,
	public AudioSource
{
	One<OOSDL2::AudioInput> obj;
	
public:
	RTTI_COMP1(SDL2AudioInputComponent, AudioSource)
	VIS_COMP_1_0(Audio)
	COPY_PANIC(SDL2AudioInputComponent);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	
	SDL2AudioInputComponent() = default;
	
	void				Initialize() override;
	void				Uninitialize() override;
	AudioStream&		GetStream(AudCtx) override;
	void				BeginStream(AudCtx) override;
	void				EndStream(AudCtx) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::AudioInput* GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_TOPSIDE_END

#endif
