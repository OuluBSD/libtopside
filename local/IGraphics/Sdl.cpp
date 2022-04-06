#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

#ifdef flagSDL2
#ifdef flagOGL

void SdlOglGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r, NativeFrameBuffer& color_buf) {
	SDL_GL_SwapWindow(&w);
}

#endif

void SdlCpuGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r, NativeFrameBuffer& color_buf) {
	SDL_RenderCopy(&r, color_buf.GetTex(), NULL, NULL);
	SDL_RenderPresent(&r);
}

Size SdlGfx::GetWindowSize(NativeWindow& win) {
	int w, h;
	SDL_GetWindowSize(&win, &w, &h);
	return Size(w, h);
}

#endif


NAMESPACE_PARALLEL_END
