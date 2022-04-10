#ifndef _SoftRend_Backend_h_
#define _SoftRend_Backend_h_

NAMESPACE_TOPSIDE_BEGIN


#ifdef flagSDL2
struct Sdl {
	using NativeTexture = SDL_Texture*;
	using NativeSurface = SDL_Surface*;
	using NativeColorBuffer = SDL_Texture*;
	
	
	static bool LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf);
	static void QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h);
	
};
#define SDL2_BACKEND(x) BACKEND(x, Sdl)
#define SDL2_BACKEND_EXCPLICIT_INIT(x) template struct x <Sdl>;
#else
#define SDL2_BACKEND(x)
#define SDL2_BACKEND_EXCPLICIT_INIT(x)
#endif



#define SOFTREND_BACKEND_LIST(x) \
	SDL2_BACKEND(x)

#define SOFTREND_EXCPLICIT_INITIALIZE_CLASS(x) \
	SDL2_BACKEND_EXCPLICIT_INIT(x)



NAMESPACE_TOPSIDE_END

#endif
