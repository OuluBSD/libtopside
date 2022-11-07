#ifndef _IGraphics_ProgBase_h_
#define _IGraphics_ProgBase_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class FboProgAtomT :
	public BufferBaseT<Gfx>
{
	using DataState = DataStateT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	
    FramebufferT<Gfx> fb;
    One<ImageDraw> id;
    Size sz;
    ProgImage pi;
    Image img;
	DataState data;
	
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
