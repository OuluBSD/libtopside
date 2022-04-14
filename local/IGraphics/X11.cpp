#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

#if 0
// TODO REMOVE CreateWindowAndRenderer etc when SDL2 tests works
#endif

bool X11Gfx::CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow& win, NativeRenderer& rend) {
	return true;
}

void X11Gfx::SetTitle(NativeDisplay& display, NativeWindow& win, String title) {
	ASSERT(display && win);
	XStoreName(display, win, title);
}

void X11Gfx::SetWindowFullscreen(NativeWindow& win, bool b) {
	TODO
}

void X11Gfx::DestroyRenderer(NativeRenderer& rend) {
	TODO
}

void X11Gfx::DestroyWindow(NativeWindow& win) {
	TODO
}

void X11Gfx::MaximizeWindow(NativeWindow& win) {
	TODO
}

void X11Gfx::RestoreWindow(NativeWindow& win) {
	TODO
}

void X11Gfx::SetWindowPosition(NativeWindow& win, Point pt) {
	TODO
}

void X11Gfx::SetWindowSize(NativeWindow& win, Size sz) {
	TODO
}

Size X11Gfx::GetWindowSize(NativeWindow& win) {
	TODO
}


#ifdef flagOGL

void X11OglGfx::DeleteContext(NativeGLContext& ctx) {
	TODO
}

void X11OglGfx::ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeFrameBuffer& color_buf) {
	ASSERT(d && w);
	glXSwapBuffers(d, w);
}

#endif

void X11SwGfx::ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeFrameBuffer& color_buf) {
	ASSERT(d && w);
	XFlush(d);
}



NAMESPACE_PARALLEL_END
