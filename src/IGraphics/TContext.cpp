#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
void RendererT<Gfx>::DefaultPreFrame() {
	//ASSERT(rend);
	Gfx::BindFramebufferDefault();
	Gfx::SetClearValue(RGBAC(0,0,0,255), 255);
	Gfx::ClearBuffers();
	Gfx::SetSmoothShading();
	Gfx::SetDepthTest(1);
	// TODO check if supported by profile: Gfx::SetFastPerspectiveCorrection();
	Gfx::SetTriangleBacksideCulling();
	Gfx::SetDepthOrderLess(1);
	#if IS_NEGATIVE_Z
	Gfx::SetTriangleFrontsideCCW(1);
	#else
	Gfx::SetTriangleFrontsideCCW(0);
	#endif
	Gfx::SetViewport(output_sz);
}


GFX3D_EXCPLICIT_INITIALIZE_CLASS(ContextStateT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(RendererT)


NAMESPACE_PARALLEL_END
