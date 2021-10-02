#ifndef _AtomSDL2_Events_h_
#define _AtomSDL2_Events_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class SDL2EventsBase :
	public SDL2BaseT<SDL2EventsBase>
{
	One<OOSDL2::Events>	obj;
	Vector<byte>		tmp_events;
	
	CtrlEvent& AddTmpEvent();
	
public:
	RTTI_DECL1(SDL2EventsBase, AltBaseT)
	COPY_PANIC(SDL2EventsBase)
	ATOM_DEF_VISIT
	
	SDL2EventsBase() {}
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	void			Forward(FwdScope& fwd) override;
	void			StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	void			Update(double dt) override;
	bool			LoadPacket(int ch_i, const Packet& p) override;
	bool			IsReady(ValDevCls vd) override;
	
	bool				ReadFrame();
	bool				ProcessFrame();
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOSDL2::Events*		GetOOSDL2() {return &*obj;}
	
};


NAMESPACE_SERIAL_END

#endif
#endif
