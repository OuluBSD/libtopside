#include "WebcamCV.h"

NAMESPACE_TOPSIDE_BEGIN

void GaussianBlurBase::Process() {
    Grayscale(input, tmp0);
    
    int r = radius;
    int kernel_size = r * 2 + 1;
    
    GaussianBlur<byte,int>(tmp0, tmp1, kernel_size, sigma);
    
    OutputFromGray(tmp1);
}
   
NAMESPACE_TOPSIDE_END
