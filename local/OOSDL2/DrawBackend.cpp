#include "OOSDL2.h"

NAMESPACE_UPP


Image ImageBuffer::GetImage() {
	if (sz.IsEmpty())
		return Image();
	SDL_Surface* surf = SDL_CreateRGBSurface(0, sz.cx, sz.cy, 32, 0,0,0,0);
	if (!surf || !surf->format)
		return Image();
	byte* dst = (byte*)surf->pixels;
	const RGBA* src = buf.Begin();
	int pitch = surf->pitch;
	int size = sz.cy * pitch;
	int stride = surf->format->BytesPerPixel;
	int line = sz.cx * stride;
	if (stride != 4)
		return Image();
	
	if (pitch == sz.cx * 4) {
		memcpy(dst, src, size);
	}
	else {
		for (int y = 0; y < surf->h; y++) {
			memcpy(dst, src, line);
			src += sz.cx;
			dst += pitch;
		}
	}

	return surf;
}


END_UPP_NAMESPACE
