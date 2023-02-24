#include "Atom.h"

namespace UPP {

#define LLOG(x)  LOG(x)
#define LDUMP(x) //DDUMP(x)

#if 0
struct RectSDL {
	SDL_Rect sr;
	
	operator SDL_Rect *() { return &sr; }
	
	RectSDL(const Rect& r)
	{
		sr.x = r.left;
		sr.y = r.top;
		sr.w = r.GetWidth();
		sr.h = r.GetHeight();
	}
};

SDL_Texture *SDLTextureFromImage(SDL_Renderer *renderer, const Image& m)
{
	Size isz = m.GetSize();
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                                         SDL_TEXTUREACCESS_STATIC, isz.cx, isz.cy);
	if(texture) {
		SDL_UpdateTexture(texture, RectSDL(isz), ~m, isz.cx * sizeof(RGBA));
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}
	return texture;
}
#endif

void AtomVirtualGui::SetMouseCursor(const Image& image)
{
	if (mgr)
		wins->OverrideCursor(image);
}

}
