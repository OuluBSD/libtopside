#include "Graphics.h"
#if 0

NAMESPACE_TOPSIDE_BEGIN


bool CpuMemoryFramebuffer::Create(int w, int h, int channels) {
	int sz = w * h * channels;
	pixels.SetCount(sz);
	pitch = w * stride;
	this->stride = channels;
	this->w = w;
	this->h = h;
	return true;
}


NAMESPACE_TOPSIDE_END
#endif
