#ifndef _Graphics_TContext_h_
#define _Graphics_TContext_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
struct ContextStateT : GfxContextState {
	RTTI_DECL1(ContextStateT, GfxContextState)
	using Base = ContextStateT<Gfx>;
	
};

template <class Gfx>
struct RendererT : GfxRenderer {
	using NatWin = typename Gfx::NativeWindow;
	using NatRend = typename Gfx::NativeRenderer;
	using FrameBuf = typename Gfx::Framebuffer;
	
	
	NatWin* win = NULL;
    NatRend* rend = NULL;
    FrameBuf output;
	
public:
	using Base = RendererT<Gfx>;
	RTTI_DECL1(RendererT, GfxRenderer)
	RendererT() {}
	virtual ~RendererT() {}
	
	
	void PreFrame() override {DefaultPreFrame();}
	void PostFrame() override {DefaultPostFrame();}
	GfxFramebuffer& GetOutputFramebuffer() override {return output;}
	FrameBuf& GetFramebuffer() {return output;}
	
	
	void DefaultPreFrame() {
		ASSERT(rend);
		NatRend& r = *rend;
		Gfx::LeaveFramebuffer(r);
		Gfx::ClearBuffers(r);
		Gfx::SetSmoothShading(r);
		Gfx::SetClearValue(r, RGBA(0,0,0,255), 255);
		Gfx::SetDepthTest(r);
		Gfx::SetDepthOrderLess(r);
		Gfx::SetFastPerspectiveCorrection(r);
		Gfx::SetTriangleBacksideCulling(r);
		Gfx::SetTriangleFrontsideCCW(r);
		Gfx::SetViewport(r, output_sz);
	}
	
	void DefaultPostFrame() {
		ASSERT(win && rend);
		Gfx::ActivateNextFrame(*win, *rend);
	}
};




NAMESPACE_TOPSIDE_END

#endif
