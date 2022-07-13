#include "StaticInterface.h"

#ifdef flagSDL2
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_ttf.h>

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
	if (!surf)
		return Image();
	
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

void Sdl2FileBackend::ClearImage(SysImage& img) {
	if (img.raw->native) {
		SDL_FreeSurface((SDL_Surface*)img.raw->native);
		img.raw->native = 0;
	}
}



Font Sdl2FileBackend::LoadFont(String dir, String name, int ptsize, int weight, bool italic) {
	String path = AppendFileName(dir, name);
	switch (weight) {
		case 0:	path += "-Thin";	break;
		case 1:	path += "-Regular";	break;
		case 2:	path += "-Medium";	break;
		case 3:	path += "-Bold";	break;
	}
	path += ".ttf";
	
	if (!FileExists(path)) {
		return Font();
	}
	
	RawSysFont* fnt = new RawSysFont();
	
	DLOG("Opening font " << path);
	fnt->backend = TypeIdClass();
	fnt->native = TTF_OpenFont(path.Begin(), ptsize);
	fnt->dir = dir;
	fnt->name = name;
	fnt->ptsize = ptsize;
	fnt->weight = weight;
	fnt->italic = italic;
	
	if (!fnt->native) {
		#if HAVE_SDL2
		DLOG("Opening font failed: " << TTF_GetError());
		#else
		DLOG("Opening font failed");
		#endif
	}
	return fnt;
}

Size Sdl2FileBackend::GetTextSize(const SysFont& fnt, const String& s) {
	if (!fnt.raw)
		return Size(0,0);
	TTF_Font* native = (TTF_Font*)fnt.raw->native;
	
	Size sz;
	TTF_SizeText(native, s.Begin(), &sz.cx, &sz.cy);
	return sz;
}

void Sdl2FileBackend::ClearFont(SysFont& fnt) {
	if (fnt.raw->native) {
		TTF_CloseFont((TTF_Font*)fnt.raw->native);
		fnt.raw->native = 0;
	}
}




NAMESPACE_TOPSIDE_END

#endif
