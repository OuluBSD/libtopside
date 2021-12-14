#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN



void SdlOglGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r, NativeFrameBuffer& color_buf) {
	SDL_GL_SwapWindow(&w);
}

void SdlCpuGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r, NativeFrameBuffer& color_buf) {
	SDL_RenderCopy(&r, color_buf.GetTex(), NULL, NULL);
	SDL_RenderPresent(&r);
}

Size SdlGfx::GetWindowSize(NativeWindow& win) {
	int w, h;
	SDL_GetWindowSize(&win, &w, &h);
	return Size(w, h);
}


NAMESPACE_TOPSIDE_END
