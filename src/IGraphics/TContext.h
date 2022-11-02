#ifndef _IGraphics_TContext_h_
#define _IGraphics_TContext_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct ContextStateT : GfxContextState {
	RTTI_DECL1(ContextStateT, GfxContextState)
	using Base = ContextStateT<Gfx>;
	
};

template <class Gfx>
struct RendererT : GfxRenderer {
	using NativeDisplay = typename Gfx::NativeDisplay;
	using NativeWindow = typename Gfx::NativeWindow;
	using NativeRenderer = typename Gfx::NativeRenderer;
	using Framebuffer = FramebufferT<Gfx>;
	
	
	NativeDisplay display;
	NativeWindow win;
    NativeRenderer rend;
    Framebuffer output;
	
public:
	using Base = RendererT<Gfx>;
	RTTI_DECL1(RendererT, GfxRenderer)
	RendererT() {}
	virtual ~RendererT() {}
	
	
	void PreFrame() override {DefaultPreFrame();}
	void PostFrame() override {DefaultPostFrame();}
	GfxFramebuffer& GetOutputFramebuffer() override {return output;}
	Framebuffer& GetFramebuffer() {return output;}
	
	
	void DefaultPreFrame();
	
	void DefaultPostFrame() {
		ASSERT(win);
		Gfx::ActivateNextFrame(display, win, rend, output.GetActiveColorBuffer());
	}
};




NAMESPACE_PARALLEL_END

#endif
