#ifndef _AtomSDL2_Joystick_h_
#define _AtomSDL2_Joystick_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2JoystickBase :
	public SDL2BaseT<SDL2JoystickBase>
{
	One<OOSDL2::Joystick> obj;
	
public:
	RTTI_DECL1(SDL2JoystickBase, AltBaseT)
	COPY_PANIC(SDL2JoystickBase)
	ATOM_DEF_VISIT
	
	SDL2JoystickBase() = default;
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOSDL2::Joystick*	GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_SERIAL_END

#endif
#endif
