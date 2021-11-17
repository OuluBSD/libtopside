#include "WebcamCV.h"

NAMESPACE_TOPSIDE_BEGIN


void CannyEdgeBase::Process() {
    Grayscale(input, tmp0);
    
    int r = blur_radius;
    int kernel_size = (r+1) << 1;
    
    GaussianBlur(tmp0, tmp1, kernel_size, 0);
    
    Canny(tmp1, tmp0, low_threshold, high_threshold);
    
    OutputFromGray(tmp0);
}


NAMESPACE_TOPSIDE_END

