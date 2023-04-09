#include "IGraphics.h"

#if defined flagSCREEN && defined flagPOSIXDESKTOP

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

void X11OglGfx::ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf) {
	ASSERT(d && w);
	glXSwapBuffers(d, w);
}

#endif

void X11SwGfx::DeleteContext(NativeGLContext& ctx) {
	TODO
}

void X11SwGfx::ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf) {
	ASSERT(d && w);
	XFlush(d);
}

int X11SwGfx::GetBytesPerPixel(NativeSurface& surf) {
	return surf->GetChannels();
}

int X11SwGfx::GetPitch(NativeSurface& surf) {
	return surf->GetPitch();
}

byte* X11SwGfx::GetData(NativeSurface& surf) {
	return surf->Begin();
}

void X11SwGfx::UnlockTextureToSurface(NativeTexture& tex) {
	// pass
}

/*void X11SwGfx::ClearFramebufferRef(NativeFrameBufferRef& fb) {
	fb = 0;
}*/


NAMESPACE_PARALLEL_END

#endif
