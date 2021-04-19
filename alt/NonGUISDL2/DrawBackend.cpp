#include "NonGUISDL2.h"
#include <Oulu/Oulu.h>
#include <OOSDL2/OOSDL2.h>

NAMESPACE_UPP_BEGIN

Image StreamRaster::LoadFileAny(String path) {
	return Image(IMG_Load(path.Begin()));
}

RawSysFont* LoadSysFont(String path, int size) {
	return TTF_OpenFont(path.Begin(), size);
}

Size GetSysFontTextSize(RawSysFont* fnt, String s) {
	Size sz;
	TTF_SizeText(fnt, s.Begin(), &sz.cx, &sz.cy);
	return sz;
}

void SysFont::Clear() {
	if (raw && Oulu::OOSDL2::IsSDL2Open())
		TTF_CloseFont(raw);
	raw = 0;
}

void SysImage::Clear() {
	if (raw && Oulu::OOSDL2::IsSDL2Open()) {
		if (--raw->refcount == 0)
			SDL_FreeSurface(raw);
	}
	raw = 0;
}

NAMESPACE_UPP_END

