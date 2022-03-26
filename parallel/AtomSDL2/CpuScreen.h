#ifndef _AtomSDL2_CpuScreen_h_
#define _AtomSDL2_CpuScreen_h_

#if 0

NAMESPACE_SERIAL_BEGIN


#ifdef flagSCREEN

class SDL2CpuScreenBase :
	public SDL2BaseT<SDL2CpuScreenBase>,
	public CpuBufferBase,
	public FramePollerBase
{
	One<OOSDL2::CpuScreen>	obj;
    Parallel::Format		fmt;
	OOSDL2::Events*			ev = 0;
	EnvStateRef				env;
	bool					close_machine = false;
	bool					is_testshader = false;
	
public:
	RTTI_DECL2(SDL2CpuScreenBase, AltBaseT, FramePollerBase)
	COPY_PANIC(SDL2CpuScreenBase)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this); vis.VisitThis<FramePollerBase>(this);}
	
	SDL2CpuScreenBase() = default;
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Update(double dt) final;
	//bool			PassConsumePacket(int sink_ch, const Packet& in) override;
	bool			NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override;
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::CpuScreen* GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.vid.SetFPS(fps); FramePollerBase::SetFPS(fps);}
	
};

#endif


NAMESPACE_SERIAL_END

#endif
#endif
