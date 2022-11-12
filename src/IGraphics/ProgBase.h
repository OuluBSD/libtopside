#ifndef _IGraphics_ProgBase_h_
#define _IGraphics_ProgBase_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class FboProgAtomT :
	public BufferBaseT<Gfx>
{
	using DataState = DataStateT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	using Material = MaterialT<Gfx>;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	
    FramebufferT<Gfx> fb;
    Size sz;
	DataState data;
	
	struct Window : Moveable<Window> {
		ProgImage pi;
		One<ImageDraw> id;
		NativeColorBufferRef tex;
		Image img;
		Size sz;
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
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void Visit(RuntimeVisitor& vis) override {}
	
};


#if defined flagPOSIX
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
