#include "SDL2GUI3D.h"

NAMESPACE_UPP_BEGIN

RawSysFont* LoadSysFont(String path, int size) {
	return TTF_OpenFont(path.Begin(), size);
}

Size GetSysFontTextSize(RawSysFont* fnt, String s) {
	Size sz;
	TTF_SizeText(fnt, s.Begin(), &sz.cx, &sz.cy);
	return sz;
}

void SysFont::Clear() {
	if (raw && Topside::OOSDL2::IsSDL2Open())
		TTF_CloseFont(raw);
	raw = 0;
}

void SysImage::Clear() {
	if (raw && Topside::OOSDL2::IsSDL2Open()) {
		if (--raw->refcount == 0)
			SDL_FreeSurface(raw);
	}
	raw = 0;
}

NAMESPACE_UPP_END
