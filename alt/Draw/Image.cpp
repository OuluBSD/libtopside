#include "Draw.h"


NAMESPACE_UPP_BEGIN

Image DefaultImages::Arrow;



void Image::MakeSysAccel() {
	TODO
}

const byte* Image::GetIter(int x, int y) const {
	if (!data) return 0;
	const byte* d = data->img.GetData();
	int pitch = data->img.GetPitch();
	int stride = data->img.GetStride();
	return d + y * pitch + x * stride;
}






void ImageBuffer::Create(Size sz) {
	ASSERT(sz.cx > 0 && sz.cy > 0);
	this->sz = sz;
	int area = sz.GetArea();
	buf.SetCount(area);
}

void ImageBuffer::Clear() {
	buf.SetCount(0);
}

#ifndef flagGUI
Image ImageBuffer::GetImage() {
	TODO
}
#endif






Image RescaleFilter(const Image& img, int cx, int cy, int filter) {
	TODO
}

Image RescaleFilter(const Image& img, Size sz, Rect r, int filter) {
	TODO
}

Image CachedRescale(const Image& img, Size sz) {
	TODO
}



NAMESPACE_UPP_END

