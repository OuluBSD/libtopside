#ifndef _AtomSDL2_Timer_h_
#define _AtomSDL2_Timer_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class SDL2TimerBase :
	public SDL2BaseT<SDL2TimerBase>
{
	One<OOSDL2::Timer> obj;
	
public:
	RTTI_DECL1(SDL2TimerBase, AltBaseT)
	COPY_PANIC(SDL2TimerBase)
	ATOM_DEF_VISIT
	
	SDL2TimerBase() = default;
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::Timer* GetOOSDL2() {return &*obj;}
	
	static AtomTypeCls GetAtomType();
};


NAMESPACE_SERIAL_END

#endif
#endif
