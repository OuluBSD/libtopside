#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void GrayscaleBase::Process() {
	Grayscale(input, sz.cx, sz.cy, tmp0, COLOR_RGBA2GRAY);
	OutputFromGray(tmp0);
}


NAMESPACE_TOPSIDE_END
