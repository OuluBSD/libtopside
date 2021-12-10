#ifndef _AtomSDL2_ScreenT_h_
#define _AtomSDL2_ScreenT_h_

NAMESPACE_SERIAL_BEGIN

#ifdef flagSCREEN

template <class Gfx>
class SDL2ScreenBaseT :
	public SDL2BaseT<SDL2ScreenBaseT<Gfx>>,
	public OglBufferBase,
	public FramePollerBase
{
	using OOScreen = OOSDL2::ScreenT<Gfx>;
	using AltBaseT = SDL2BaseT<SDL2ScreenBaseT<Gfx>>;
	One<OOScreen>		obj;
    Serial::Format		fmt;
	OOSDL2::Events*		ev = 0;
	EnvStateRef			env;
	bool				close_machine = false;
	
public:
	RTTI_DECL3(SDL2ScreenBaseT, AltBaseT, OglBufferBase, FramePollerBase)
	COPY_PANIC(SDL2ScreenBaseT)
	using Base = SDL2ScreenBaseT<Gfx>;
	
	void Visit(RuntimeVisitor& vis) override {vis & env; vis.VisitThis<AltBaseT>(this); vis.VisitThis<OglBufferBase>(this); vis.VisitThis<FramePollerBase>(this);}
	
	SDL2ScreenBaseT() = default;
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	bool			IsReady(PacketIO& io) override;
	void			Update(double dt) final;
	
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOScreen*			GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.vid.SetFPS(fps); FramePollerBase::SetFPS(fps);}
	
};


using SDL2CpuScreenBase = SDL2ScreenBaseT<SdlCpuGfx>;
using SDL2OglScreenBase = SDL2ScreenBaseT<SdlOglGfx>;

#endif

NAMESPACE_SERIAL_END

#endif
