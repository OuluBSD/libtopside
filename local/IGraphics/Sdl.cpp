#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

#ifdef flagSDL2
#ifdef flagOGL

void SdlOglGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r, NativeFrameBuffer& color_buf) {
	SDL_GL_SwapWindow(&w);
}

#endif

void SdlCpuGfx::ActivateNextFrame(SDL_Window& w, SDL_Renderer& r, NativeFrameBuffer& color_buf) {
	SDL_RenderCopy(&r, color_buf.GetTex(), NULL, NULL);
	SDL_RenderPresent(&r);
}

Size SdlGfx::GetWindowSize(NativeWindow& win) {
	int w, h;
	SDL_GetWindowSize(&win, &w, &h);
	return Size(w, h);
}

bool SdlGfx::CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow*& win, NativeRenderer*& rend) {
	return SDL_CreateWindowAndRenderer(screen_sz.cx, screen_sz.cy, flags, &win, &nat_rend) >= 0;
}

void SdlGfx::SetTitle(NativeWindow* win, String title) {
	SDL_SetWindowTitle(win, title);
}

void SdlGfx::DestroyRenderer(NativeRenderer* rend) {
	SDL_DestroyRenderer(rend);
}

void SdlGfx::DestroyWindow(NativeWindow* win) {
	SDL_DestroyWindow(win);
}

void SdlGfx::DeleteContext(NativeGLContext& ctx) {
	SDL_GL_DeleteContext(ctx);
}

void SdlGfx::SetWindowFullscreen(NativeWindow* win, bool b) {
	if (b)
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(win, 0);
}

void SdlGfx::MaximizeWindow(NativeWindow* win) {
	SDL_MaximizeWindow(win);
}

void SdlGfx::RestoreWindow(NativeWindow* win) {
	SDL_RestoreWindow(win);
}

void SdlGfx::SetWindowPosition(NativeWindow* win, Point pt) {
	SDL_SetWindowPosition(win, pt.x, pt.y);
}

void SdlGfx::SetWindowSize(NativeWindow* win, Size sz) {
	SDL_SetWindowSize(win, sz.cx, sz.cy);
}

#endif


NAMESPACE_PARALLEL_END
