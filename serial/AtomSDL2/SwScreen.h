#ifndef _AtomSDL2_SwScreen_h_
#define _AtomSDL2_SwScreen_h_

NAMESPACE_SERIAL_BEGIN


#ifdef flagGUI

class SDL2SwScreenBase :
	public SDL2BaseT<SDL2SwScreenBase>
{
	One<OOSDL2::SwScreen>	obj;
    Serial::Format			fmt;
	OOSDL2::Events*			ev = 0;
	double					dt = 0;
	double					frame_age = 0;
	int						fps;
	
public:
	RTTI_DECL1(SDL2SwScreenBase, AltBaseT)
	COPY_PANIC(SDL2SwScreenBase)
	ATOM_DEF_VISIT
	
	SDL2SwScreenBase() = default;
	
	bool			AltInitialize(const Script::WorldState& ws) override;
	void			AltUninitialize() override;
	void			AltForward(FwdScope& fwd) override;
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::SwScreen* GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.vid.SetFPS(fps);}
	
};

#endif


NAMESPACE_SERIAL_END

#endif
