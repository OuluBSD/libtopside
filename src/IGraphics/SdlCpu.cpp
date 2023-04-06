#include "IGraphics.h"

// What even is this?
#if 0
#ifdef flagSDL2

NAMESPACE_PARALLEL_BEGIN



//SdlCpuGfx::Thread& SdlCpuGfx::Local() {thread_local static Thread t; return t;}

int SdlCpuGfx::GetBytesPerPixel(NativeSurface& surf) {
	return surf->format->BytesPerPixel;
}

int SdlCpuGfx::GetPitch(NativeSurface& surf) {
	return surf->pitch;
}

byte* SdlCpuGfx::GetData(NativeSurface& surf) {
	return (byte*)surf->pixels;
}

bool SdlCpuGfx::LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf) {
	SDL_Rect re {
		r.left,
		r.top,
		r.GetWidth(),
		r.GetHeight()
	};
	return SDL_LockTextureToSurface(tex, &re, &surf) >= 0;
}

void SdlCpuGfx::QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h) {
	SDL_QueryTexture(tex, &fmt, &access, &w, &h);
}

void SdlCpuGfx::UnlockTextureToSurface(NativeTexture& tex) {
	SDL_UnlockTexture(tex);
}

void SdlCpuGfx::ActivateNextFrame(NativeDisplay&, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf) {
	const auto& fb = color_buf;
	//NativeColorBufferRef& fb = color_buf;
	
	#if 0
	{
		ASSERT(fb);
		uint32 fmt = 0;
		int access, w = 0, h = 0;
		if (SDL_QueryTexture(fb, &fmt, &access, &w, &h) < 0 || w == 0 || h == 0)
			return;
		SDL_Surface* surf = 0;
		SDL_Rect r {0, 0, w, h};
		if (SDL_LockTextureToSurface(fb, &r, &surf) < 0 || !surf)
			return;
		int stride = surf->format->BytesPerPixel;
		int pitch = surf->pitch;
		byte* pixels = (byte*)surf->pixels;
		int sz = h * pitch;
		memset(pixels, Random(0x100), sz);
		SDL_UnlockTexture(fb);
	}
	#endif
	
	TODO
	int ret = 0;//SDL_RenderCopy(r, fb, NULL, NULL);
	if (ret) {
		LOG("SdlCpuGfx::ActivateNextFrame: error: " << SDL_GetError());
		ASSERT(0);
	}
	SDL_RenderPresent(r);
}


NAMESPACE_PARALLEL_END

#endif
#endif
