#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN



void SdlGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r) {
	SDL_GL_SwapWindow(&w);
}


NAMESPACE_TOPSIDE_END
