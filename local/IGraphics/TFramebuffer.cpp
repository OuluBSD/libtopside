#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


#ifdef flagSDL2
template <>
void FramebufferT<SdlCpuGfx>::DrawFill(const byte* mem, int sz) {
	SDL_Texture* tex = color_buf[0].GetTex();
	ASSERT(tex);
	
	uint32 fmt = 0;
	int access, w = 0, h = 0;
	if (SDL_QueryTexture(tex, &fmt, &access, &w, &h) < 0 || w == 0 || h == 0)
		return;
	
	SDL_Surface* surf = 0;
	SDL_Rect r {0, 0, w, h};
	if (SDL_LockTextureToSurface(tex, &r, &surf) < 0 || !surf)
		return;
	
	int stride = surf->format->BytesPerPixel;
	int pitch = surf->pitch;
	byte* pixels = (byte*)surf->pixels;
	
	
	if (sz == h * pitch) {
		memcpy(pixels, mem, sz);
	}
	else if (sz == w * h * stride) {
		int row = w * stride;
		byte* dst = pixels;
		for (int y = 0; y < h; y++) {
			memcpy(dst, mem, row);
			mem += row;
			dst += pitch;
		}
	}
	else {
		sz = min(sz, h * pitch);
		memcpy(pixels, mem, sz);
	}
	
	SDL_UnlockTexture(tex);
}

GFX_EXCPLICIT_INITIALIZE_CLASS(InputStateT)
GFX_EXCPLICIT_INITIALIZE_CLASS(FramebufferT)

#endif




NAMESPACE_PARALLEL_END
