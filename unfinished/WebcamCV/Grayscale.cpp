#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void GrayscaleBase::Process() {
	Grayscale(input, tmp0);
	OutputFromGray(tmp0);
}


NAMESPACE_TOPSIDE_END
