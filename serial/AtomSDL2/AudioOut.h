#ifndef _AtomSDL2_AudioOut_h_
#define _AtomSDL2_AudioOut_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class SDL2AudioOutputBase :
	public SDL2BaseT<SDL2AudioOutputBase>,
	public AsyncMemForwarderBase
{
	One<OOSDL2::AudioOutput>	obj;
	
	
public:
	RTTI_DECL2(SDL2AudioOutputBase, AltBaseT, AsyncMemForwarderBase)
	COPY_PANIC(SDL2AudioOutputBase)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this); vis.VisitThis<AsyncMemForwarderBase>(this);}
	
	SDL2AudioOutputBase() {}
	
	bool	Initialize(const Script::WorldState& ws) override;
	bool	PostInitialize() override;
	void	Uninitialize() override;
	bool	PassProcessPackets(PacketIO& io) override;
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::AudioOutput* GetOOSDL2() {return &*obj;}
	
	
};


NAMESPACE_SERIAL_END

#endif
#endif
