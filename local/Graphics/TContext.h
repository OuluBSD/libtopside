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
		Gfx::UnbindFramebuffer();
		Gfx::ClearBuffers();
		Gfx::SetSmoothShading();
		Gfx::SetClearValue(RGBA(0,0,0,255), 255);
		Gfx::SetDepthTest();
		Gfx::SetDepthOrderLess();
		Gfx::SetFastPerspectiveCorrection();
		Gfx::SetTriangleBacksideCulling();
		Gfx::SetTriangleFrontsideCCW();
		Gfx::SetViewport(output_sz);
	}
	
	void DefaultPostFrame() {
		ASSERT(win && rend);
		Gfx::ActivateNextFrame(*win, *rend);
	}
};




NAMESPACE_TOPSIDE_END

#endif
