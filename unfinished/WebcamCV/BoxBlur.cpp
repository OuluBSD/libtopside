#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void BoxBlurBase::Process() {
	Grayscale(input, tmp0);
	box_blur_gray(tmp0, tmp1, radius, 0);
	OutputFromGray(tmp1);
}


NAMESPACE_TOPSIDE_END
