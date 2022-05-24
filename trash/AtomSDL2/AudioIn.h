#ifndef _AtomSDL2_AudioIn_h_
#define _AtomSDL2_AudioIn_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2AudioInputBase :
	public SDL2BaseT<SDL2AudioInputBase>
{
	One<OOSDL2::AudioInput> obj;
	
public:
	RTTI_DECL1(SDL2AudioInputBase, AltBaseT)
	COPY_PANIC(SDL2AudioInputBase)
	ATOM_DEF_VISIT
	
	SDL2AudioInputBase() = default;
	
	bool				Initialize(const Script::WorldState& ws) override;
	void				Uninitialize() override;
	/*AudioStream&		GetStream(AudCtx) override;
	void				BeginStream(AudCtx) override;
	void				EndStream(AudCtx) override;*/
	
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOSDL2::AudioInput*	GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_SERIAL_END

#endif
#endif
