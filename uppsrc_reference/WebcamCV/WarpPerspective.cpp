#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


WarpPerspectiveBase::WarpPerspectiveBase() {
    
}

void WarpPerspectiveBase::Process() {
	Perspective4PointTransform(transform,  0,     0,   50,  50,
                                           640,     0,  550, 100,
                                         sz.cx, sz.cy,  300, 400,
                                             0,   480,  100, 400);
    Invert3x3(transform, transform);
    
    
	auto& img_u8 = tmp0;
	auto& img_u8_warp = tmp1;
	
    Grayscale(input, img_u8);
    
    WarpPerspective(img_u8, img_u8_warp, transform, 0);
    
    OutputFromGray(img_u8_warp);
}


NAMESPACE_TOPSIDE_END
