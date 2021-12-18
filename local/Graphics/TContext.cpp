#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
void RendererT<Gfx>::DefaultPreFrame() {
	ASSERT(rend);
	Gfx::BindFramebufferDefault();
	Gfx::ClearBuffers();
	Gfx::SetSmoothShading();
	Gfx::SetClearValue(RGBA(0,0,0,255), 255);
	Gfx::SetDepthTest();
	Gfx::SetDepthOrderLess(false);
	Gfx::SetFastPerspectiveCorrection();
	Gfx::SetTriangleBacksideCulling();
	Gfx::SetTriangleFrontsideCCW();
	Gfx::SetViewport(output_sz);
}


GFX_EXCPLICIT_INITIALIZE_CLASS(ContextStateT)
GFX_EXCPLICIT_INITIALIZE_CLASS(RendererT)


NAMESPACE_TOPSIDE_END
