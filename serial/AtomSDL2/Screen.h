#ifndef _AtomSDL2_Screen_h_
#define _AtomSDL2_Screen_h_

NAMESPACE_SERIAL_BEGIN


#ifdef flagGUI

class SDL2ScreenBase :
	public SDL2BaseT<SDL2ScreenBase>
{
	One<OOSDL2::Screen>	obj;
    Serial::Format		fmt;
	OOSDL2::Events*		ev = 0;
	double				dt = 0;
	double				frame_age = 0;
	
public:
	RTTI_DECL1(SDL2ScreenBase, AltBaseT)
	COPY_PANIC(SDL2ScreenBase)
	ATOM_DEF_VISIT
	
	SDL2ScreenBase() = default;
	
	bool			AltInitialize(const Script::WorldState& ws) override;
	void			AltUninitialize() override;
	void			AltForward(FwdScope& fwd) override;
	void			AltStorePacket(Packet& p) override;
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::Screen* GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.vid.SetFPS(fps); dt = 1.0 / (double)fps;}
	
};

#endif


NAMESPACE_SERIAL_END

#endif
