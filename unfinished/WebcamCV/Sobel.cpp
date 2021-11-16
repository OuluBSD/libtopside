#include "WebcamCV.h"

NAMESPACE_TOPSIDE_BEGIN

void SobelBase::Process() {
	auto& img_u8 = tmp0;
	
    Grayscale(input, img_u8);
    
    sobel_derivatives(img_u8, img_gxgy);
    
    OutputFromXY(img_gxgy);
}

NAMESPACE_TOPSIDE_END
