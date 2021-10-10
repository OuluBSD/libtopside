#ifndef _AtomSDL2_Events_h_
#define _AtomSDL2_Events_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class SDL2EventsBase :
	public SDL2BaseT<SDL2EventsBase>
{
	One<OOSDL2::Events>	obj;
	Vector<byte>		tmp_events;
	UPP::CtrlEvent		ev;
	bool				ev_sendable = false;
	
	CtrlEvent& AddTmpEvent();
	
public:
	RTTI_DECL1(SDL2EventsBase, AltBaseT)
	COPY_PANIC(SDL2EventsBase)
	ATOM_DEF_VISIT
	
	SDL2EventsBase() {}
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Update(double dt) override;
	bool			IsReady(dword active_iface_mask) override;
	
	bool				ReadFrame();
	bool				ProcessFrame();
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOSDL2::Events*		GetOOSDL2() {return &*obj;}
	
};


NAMESPACE_SERIAL_END

#endif
#endif
