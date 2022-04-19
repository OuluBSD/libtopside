#include "IGraphics.h"
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



NAMESPACE_PARALLEL_END

#endif
