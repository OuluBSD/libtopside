#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN


bool X11Sw::LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf) {
	
	TODO
	
}

void X11Sw::QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h) {
	
	TODO
	
}


#ifdef flagSDL2
bool Sdl::LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf) {
	SDL_Rect re {
		r.left,
		r.top,
		r.GetWidth(),
		r.GetHeight()
	};
	return SDL_LockTextureToSurface(tex, &re, &surf) >= 0;
}

void Sdl::QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h) {
	SDL_QueryTexture(tex, &fmt, &access, &w, &h);
}
#endif


NAMESPACE_TOPSIDE_END
