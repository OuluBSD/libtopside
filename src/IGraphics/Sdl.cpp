#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

#ifdef flagSDL2
#ifdef flagOGL

void SdlOglGfx::ActivateNextFrame(NativeDisplay&, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf) {
	SDL_GL_SwapWindow(w);
}

bool SdlOglGfx::LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf) {
	TODO
}

void SdlOglGfx::QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h) {
	TODO
}

#endif

int SdlSwGfx::GetBytesPerPixel(NativeSurface& surf) {
	return surf->format->BytesPerPixel;
}

int SdlSwGfx::GetPitch(NativeSurface& surf) {
	return surf->pitch;
}

byte* SdlSwGfx::GetData(NativeSurface& surf) {
	return (byte*)surf->pixels;
}

void SdlSwGfx::ActivateNextFrame(NativeDisplay&, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf) {
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

Size SdlGfx::GetWindowSize(NativeWindow& win) {
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	return Size(w, h);
}

bool SdlGfx::CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow& win, NativeRenderer& rend) {
	Panic("deprecated");
	NEVER();
	//return SDL_CreateWindowAndRenderer(screen_sz.cx, screen_sz.cy, flags, &win, &rend) >= 0;
	return false;
}

void SdlGfx::SetTitle(NativeDisplay&, NativeWindow& win, String title) {
	SDL_SetWindowTitle(win, title);
}

void SdlGfx::DestroyRenderer(NativeRenderer& rend) {
	SDL_DestroyRenderer(rend);
}

void SdlGfx::DestroyWindow(NativeWindow& win) {
	SDL_DestroyWindow(win);
}

void SdlGfx::DeleteContext(NativeGLContext& ctx) {
	SDL_GL_DeleteContext(ctx);
}

void SdlGfx::SetWindowFullscreen(NativeWindow& win, bool b) {
	if (b)
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(win, 0);
}

void SdlGfx::MaximizeWindow(NativeWindow& win) {
	SDL_MaximizeWindow(win);
}

void SdlGfx::RestoreWindow(NativeWindow& win) {
	SDL_RestoreWindow(win);
}

void SdlGfx::SetWindowPosition(NativeWindow& win, Point pt) {
	SDL_SetWindowPosition(win, pt.x, pt.y);
}

void SdlGfx::SetWindowSize(NativeWindow& win, Size sz) {
	SDL_SetWindowSize(win, sz.cx, sz.cy);
}

void SdlSwGfx::ClearFramebufferRef(NativeTexture& fb) {
	fb = 0;
}

void SdlSwGfx::ClearFramebufferRef(NativeFrameBufferRef& fb) {
	fb = 0;
}

#endif


NAMESPACE_PARALLEL_END
