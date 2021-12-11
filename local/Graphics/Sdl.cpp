#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN



void SdlGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r) {
	SDL_GL_SwapWindow(&w);
}

Size SdlGfx::GetWindowSize(NativeWindow& win) {
	int w, h;
	SDL_GetWindowSize(&win, &w, &h);
	return Size(w, h);
}


NAMESPACE_TOPSIDE_END
