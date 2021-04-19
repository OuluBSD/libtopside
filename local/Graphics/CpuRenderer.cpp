#include "GL.h"

NAMESPACE_OULU_BEGIN

bool CpuMemoryFramebuffer::Create(int w, int h, int channels) {
	int sz = w * h * channels;
	pixels.SetCount(sz);
	pitch = w * stride;
	this->stride = channels;
	this->w = w;
	this->h = h;
	return true;
}







void CpuRenderer::PreFrame() {
	output.Create(screen_sz.cx, screen_sz.cy, 3);
}

void CpuRenderer::PostFrame() {
	RawSysTexture* fb = output.GetRawSysTexture();
#if defined(flagSDL2)
	if (rend && fb) {
		SDL_RenderCopy(rend, fb, NULL, NULL);
		SDL_RenderPresent(rend);
	}
#endif
}

int CpuRenderer::AddModel(Model& model) {
	TODO
}




NAMESPACE_OULU_END
