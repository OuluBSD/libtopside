#include "StaticInterface.h"

#if IS_TS_CORE

#ifdef flagSDL2
#if 0 //def flagMSC
	#include <SDL_image.h>
	#include <SDL_rwops.h>
	#include <SDL_ttf.h>
#else
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_rwops.h>
	#include <SDL2/SDL_ttf.h>
#endif

NAMESPACE_TOPSIDE_BEGIN


Image Sdl2FileBackend::ImageFromSDLSurface(void* surf_) {
	if (!surf_)
		return Image();
	SDL_Surface* surf = (SDL_Surface*)surf_;
	
	RawSysImage* img = new RawSysImage();
	const byte* src = (const byte*)surf->pixels;
	int len = surf->h * surf->pitch;
	img->data.SetCount(len);
	memcpy(img->data.Begin(), src, len);
	img->backend = GetTypeIdClass<CLASSNAME>();
	img->w = surf->w;
	img->h = surf->h;
	img->ch = surf->format->BytesPerPixel;
	img->pitch = surf->pitch;
	
	// Swap red and blue
	if (surf->format->BytesPerPixel >= 3 && surf->format->Bmask == 0xFF && surf->format->Rmask == 0xFF0000) {
		int stride = surf->format->BytesPerPixel;
		byte* row = img->data.Begin();
		for (int y = 0; y < img->h; y++) {
			byte* b = row;
			for (int x = 0; x < img->w; x++) {
				byte t = b[0];
				b[0] = b[2];
				b[2] = t;
				b += stride;
			}
			row += img->pitch;
		}
	}
	
	SDL_FreeSurface(surf);
	
	return Image(img);
}

Image Sdl2FileBackend::LoadStringAny(String content) {
	SDL_RWops* mem = SDL_RWFromConstMem(content.Begin(), content.GetCount());
	SDL_Surface* surf = IMG_Load_RW(mem, 1);
	return ImageFromSDLSurface(surf);
}

Image Sdl2FileBackend::LoadFileAny(String path) {
	SDL_Surface* surf = IMG_Load(path.Begin());
	if (!surf)
		return Image();
	
	return ImageFromSDLSurface(surf);
}

void Sdl2FileBackend::ClearImage(SysImage& img) {
	if (img.raw->native) {
		SDL_FreeSurface((SDL_Surface*)img.raw->native);
		img.raw->native = 0;
	}
}



Font Sdl2FileBackend::LoadFont(String dir, String name, int ptsize, int weight, bool italic) {
	String path = AppendFileName(dir, name);
	
	if (GetFileExt(name).IsEmpty()) {
		switch (weight) {
			case 0:	path += "-Thin";	break;
			case 1:	path += "-Regular";	break;
			case 2:	path += "-Medium";	break;
			case 3:	path += "-Bold";	break;
		}
		path += ".ttf";
	}
	
	if (!FileExists(path)) {
		return Font();
	}
	
	if (ptsize < 0)
		ptsize = 12; // default font size in points (TODO high dpi desktop)
	
	RawSysFont* fnt = new RawSysFont();
	
	DLOG("Opening font " << path);
	fnt->backend = GetTypeIdClass<CLASSNAME>();
	fnt->native = TTF_OpenFont(path.Begin(), ptsize);
	fnt->dir = dir;
	fnt->name = name;
	fnt->ptsize = ptsize;
	fnt->weight = weight;
	fnt->italic = italic;
	
	if (!fnt->native) {
		#ifdef flagSDL2
		if (String(TTF_GetError()) == "Library not initialized") {
			TTF_Init();
			return LoadFont(dir, name, ptsize, weight, italic);
		}
		LOG("Opening font failed: " << TTF_GetError());
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

Image Sdl2FileBackend::RenderTextBlended(const SysFont& fnt, const char* s, SysColor c) {
	SDL_Color clr;
	clr.r = c.r;
	clr.g = c.g;
	clr.b = c.b;
	clr.a = c.a;
	SDL_Surface* surf = TTF_RenderText_Blended((TTF_Font*)fnt.raw->native, s, clr);
	return ImageFromSDLSurface(surf);
}




NAMESPACE_TOPSIDE_END

#endif
#endif
