#include "WebcamCV.h"

NAMESPACE_TOPSIDE_BEGIN


void EqualizeHistBase::Process() {
    Grayscale(input, tmp0);
    
    equalize_histogram(tmp0, tmp1);
    
    OutputFromGray(tmp1);
}
        

NAMESPACE_TOPSIDE_END
