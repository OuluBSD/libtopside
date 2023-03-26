#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


#ifdef flagPOSIXDESKTOP
bool X11SwGfx::LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf) {
	surf = tex->Get(0);
	ASSERT(surf);
	return true;
}

void X11SwGfx::QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h) {
	ASSERT(tex);
	fmt = 0;
	access = 0;
	Size sz = tex->GetSize();
	w = sz.cx;
	h = sz.cy;
}
#endif


#ifdef flagSDL2
bool SdlSwGfx::LockTextureToSurface(SoftFramebuffer* tex, Rect r, NativeSurface& surf) {
	TODO
}

void SdlSwGfx::QueryTexture(SoftFramebuffer* tex, uint32& fmt, int& access, int& w, int& h) {
	Size sz = tex->GetSize();
	w = sz.cx;
	h = sz.cy;
}

void SdlSwGfx::UnlockTextureToSurface(SoftFramebuffer* tex) {
	TODO
}

#endif


NAMESPACE_PARALLEL_END
