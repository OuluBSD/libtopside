#ifndef _SoftRend_Backend_h_
#define _SoftRend_Backend_h_

NAMESPACE_TOPSIDE_BEGIN


#ifdef flagSDL2
struct Sdl {
	using NativeTexture = SDL_Texture;
	using NativeSurface = SDL_Surface;
	
	
	static bool LockTextureToSurface(Texture& tex, Rect r, Surface& surf);
	static void QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h);
	
};
#endif


NAMESPACE_TOPSIDE_END

#endif
