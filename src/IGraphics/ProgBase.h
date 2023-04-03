#ifndef _IGraphics_ProgBase_h_
#define _IGraphics_ProgBase_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct FboProgAtomT :
	public BufferBaseT<Gfx>
{
	using DataState = DataStateT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	using Material = MaterialT<Gfx>;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	
    FramebufferT<Gfx> fb;
    Size sz;
	DataState data;
	bool dbg_info = 1;
	int dbg_win_id;
	double resize_multiplier = 0.01;
	bool write_ecs = false;
	
	struct Window : Moveable<Window> {
		DrawCommandImageRenderer rend;
		NativeColorBufferRef tex;
		int tex_id;
		bool inited = false;
	};
	VectorMap<hash_t, Window> windows;
	
	DrawCommand* ProcessWindow(DrawCommand* cmd);
	void ProcessWindowCommands(DrawCommand* begin, DrawCommand* end);
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(FboProgAtomT, BufferBase);
	FboProgAtomT() {}
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	void Finalize(RealtimeSourceConfig& cfg) override;
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void Visit(RuntimeVisitor& vis) override {}
	
};


#if defined flagPOSIXDESKTOP
using X11SwFboProgBase = FboProgAtomT<X11SwGfx>;

#ifdef flagOGL
using X11OglFboProgBase = FboProgAtomT<X11OglGfx>;
#endif

#endif

#if defined flagOGL && defined flagSDL2
using SdlOglFboProgBase = FboProgAtomT<SdlOglGfx>;
#endif

NAMESPACE_PARALLEL_END

#endif
