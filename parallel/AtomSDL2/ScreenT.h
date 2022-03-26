#ifndef _AtomSDL2_ScreenT_h_
#define _AtomSDL2_ScreenT_h_

NAMESPACE_SERIAL_BEGIN

#ifdef flagSCREEN

template <class Gfx> bool IsDefaultGfxVal(const ValCls& val);
template <> inline bool IsDefaultGfxVal<SdlCpuGfx>(const ValCls& val) {return val == ValCls::VIDEO;}
template <> inline bool IsDefaultGfxVal<SdlOglGfx>(const ValCls& val) {return val == ValCls::FBO;}

template <class Gfx>
struct SDL2ScreenBaseT :
	SDL2BaseT<SDL2ScreenBaseT<Gfx>>,
	BufferBaseT<Gfx>,
	FramePollerBase
{
	
private:
	using OOScreen = OOSDL2::ScreenT<Gfx>;
	using AltBaseT = SDL2BaseT<SDL2ScreenBaseT<Gfx>>;
	One<OOScreen>		obj;
    Parallel::Format	fmt;
	OOSDL2::Events*		ev = 0;
	EnvStateRef			env;
	bool				close_machine = false;
	bool				render_on_side = false;
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	using Base = SDL2ScreenBaseT<Gfx>;
	using Buffer = typename Gfx::Buffer;
	RTTI_DECL3(SDL2ScreenBaseT, AltBaseT, BufferBase, FramePollerBase)
	COPY_PANIC(SDL2ScreenBaseT)
	
	void Visit(RuntimeVisitor& vis) override {vis & env; vis.VisitThis<AltBaseT>(this); vis.VisitThis<BufferBase>(this); vis.VisitThis<FramePollerBase>(this);}
	
	SDL2ScreenBaseT() = default;
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool ProcessPackets(PacketIO& io) override;
	bool IsReady(PacketIO& io) override;
	void Update(double dt) final;
	bool NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override;
	
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOScreen*			GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.vid.SetFPS(fps); FramePollerBase::SetFPS(fps);}
	
};


using SDL2CpuScreenBase = SDL2ScreenBaseT<SdlCpuGfx>;
using SDL2OglScreenBase = SDL2ScreenBaseT<SdlOglGfx>;

#endif

NAMESPACE_SERIAL_END

#endif
