#include "StaticInterface.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>

#ifdef flagSDL2

NAMESPACE_TOPSIDE_BEGIN


Image Sdl2FileBackend::LoadStringAny(String content) {
	SDL_RWops* mem = SDL_RWFromConstMem(content.Begin(), content.GetCount());
	SDL_Surface* surf = IMG_Load_RW(mem, 1);
	
	RawSysImage* img = new RawSysImage();
	const byte* src = (const byte*)surf->pixels;
	int len = surf->h * surf->pitch;
	img->data.SetCount(len);
	memcpy(img->data.Begin(), src, len);
	img->backend = TypeIdClass();
	img->w = surf->w;
	img->h = surf->h;
	img->ch = surf->format->BytesPerPixel;
	img->pitch = surf->pitch;
	
	SDL_FreeSurface(surf);
	
	return Image(img);
}

Image Sdl2FileBackend::LoadFileAny(String path) {
	SDL_Surface* surf = IMG_Load(path.Begin());
	
	RawSysImage* img = new RawSysImage();
	const byte* src = (const byte*)surf->pixels;
	int len = surf->h * surf->pitch;
	img->data.SetCount(len);
	memcpy(img->data.Begin(), src, len);
	img->backend = TypeIdClass();
	img->w = surf->w;
	img->h = surf->h;
	img->ch = surf->format->BytesPerPixel;
	img->pitch = surf->pitch;
	
	SDL_FreeSurface(surf);
	
	return Image(img);
}


NAMESPACE_TOPSIDE_END

#endif
