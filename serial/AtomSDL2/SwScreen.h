#ifndef _AtomSDL2_SwScreen_h_
#define _AtomSDL2_SwScreen_h_

NAMESPACE_SERIAL_BEGIN


#ifdef flagGUI

class SDL2SwScreenBase :
	public SDL2BaseT<SDL2SwScreenBase>,
	public FramePollerBase
{
	One<OOSDL2::SwScreen>	obj;
    Serial::Format			fmt;
	OOSDL2::Events*			ev = 0;
	
public:
	RTTI_DECL2(SDL2SwScreenBase, AltBaseT, FramePollerBase)
	COPY_PANIC(SDL2SwScreenBase)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this); vis.VisitThis<FramePollerBase>(this);}
	
	SDL2SwScreenBase() = default;
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	void			Forward(FwdScope& fwd) override;
	bool			LoadPacket(int ch_i, const Packet& p) override;
	void			StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	//bool			PassLoadPacket(int ch_i, const Packet& p) override;
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::SwScreen* GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.vid.SetFPS(fps); FramePollerBase::SetFPS(fps);}
	
};

#endif


NAMESPACE_SERIAL_END

#endif
