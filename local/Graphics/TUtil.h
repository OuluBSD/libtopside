#ifndef _Graphics_TUtil_h_
#define _Graphics_TUtil_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
struct DrawFramebufferT : GfxStateDraw {
	RTTI_DECL1(DrawFramebufferT, GfxStateDraw)
	using Base = DrawFramebufferT<Gfx>;
	using Renderer = typename Gfx::Renderer;
	using Framebuffer = typename Gfx::Framebuffer;
	using ShaderPipeline = typename Gfx::ShaderPipeline;
	
	GfxRenderer* rend = 0;
	GfxFramebuffer* fb = 0;
	
	//GfxRenderer* GetRenderer() override {return rend;}
	//GfxFramebuffer* GetFramebuffer() override {return fb;}
	
	
	void DrawShaderPipeline(ShaderPipeline&);
	
};

template <class Gfx>
struct StateDrawT : GfxStateDraw {
	RTTI_DECL1(StateDrawT, GfxStateDraw)
	using Base = StateDrawT<Gfx>;
	using ShaderPipeline = typename Gfx::ShaderPipeline;
	
	
	void DrawShaderPipeline(ShaderPipeline&) {TODO}
	
};


NAMESPACE_TOPSIDE_END

#endif
