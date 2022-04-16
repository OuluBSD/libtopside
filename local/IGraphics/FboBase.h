#ifndef _IGraphics_FboBase_h_
#define _IGraphics_FboBase_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct FboAtomT :
	Atom
{
	using StateDraw = StateDrawT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	using SoftShaderLibrary = SoftShaderLibraryT<Gfx>;
	
	Vector<BinderIfaceVideo*> binders;
	String					target;
	EnvStateRef				state;
	int						prev_iter = -1;
	ValDevCls				src_type;
	One<ImageDraw>			id;
	ProgDraw				pd;
	StateDraw				accel_sd;
	DataState				accel_state;
	Framebuffer				cpu_fb;
	bool					draw_mem = false;
	RealtimeSourceConfig*	last_cfg = 0;
	String					program;
	
	One<SoftShaderBaseT<Gfx>>	frag_prog;
	One<SoftShaderBaseT<Gfx>>	vtx_prog;
	One<BinderIfaceVideo>		prog;
	
	static FboAtomT*	latest;
	
public:
	RTTI_DECL1(FboAtomT, Atom);
	FboAtomT();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPacket(PacketValue& in, PacketValue& out) override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	void			Finalize(RealtimeSourceConfig& cfg) override;
	RealtimeSourceConfig* GetConfig() override {return last_cfg;}
	
	void AddBinder(BinderIfaceVideo* iface);
	void RemoveBinder(BinderIfaceVideo* iface);
	
	static Callback1<FboAtomT*>	WhenInitialize;
	static FboAtomT& Latest();
	
};


using X11SwFboBase = FboAtomT<X11SwGfx>;


NAMESPACE_PARALLEL_END

#endif
