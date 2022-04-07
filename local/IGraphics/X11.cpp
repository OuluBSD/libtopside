#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


bool X11Gfx::CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow*& win, NativeRenderer*& rend) {
	TODO
}

void X11Gfx::SetTitle(NativeWindow* win, String title) {
	TODO
}

void X11Gfx::SetWindowFullscreen(NativeWindow* win, bool b) {
	TODO
}

void X11Gfx::DestroyRenderer(NativeRenderer* rend) {
	TODO
}

void X11Gfx::DestroyWindow(NativeWindow* win) {
	TODO
}

void X11Gfx::DeleteContext(NativeGLContext& ctx) {
	TODO
}

void X11Gfx::MaximizeWindow(NativeWindow* win) {
	TODO
}

void X11Gfx::RestoreWindow(NativeWindow* win) {
	TODO
}

void X11Gfx::SetWindowPosition(NativeWindow* win, Point pt) {
	TODO
}

void X11Gfx::SetWindowSize(NativeWindow* win, Size sz) {
	TODO
}

Size X11Gfx::GetWindowSize(NativeWindow& win) {
	TODO
}


#ifdef flagOGL

void X11OglGfx::ActivateNextFrame(NativeWindow& w, NativeRenderer& r, NativeFrameBuffer& color_buf) {
	TODO //SDL_GL_SwapWindow(&w);
}

#endif


NAMESPACE_PARALLEL_END
