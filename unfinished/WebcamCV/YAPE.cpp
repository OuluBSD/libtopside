#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN



void YapeBase::InitDefault() {
	ASSERT(!sz.IsEmpty() && sz.cx > 0 && sz.cy > 0);
	
	corners.SetCount(sz.cx * sz.cy);
	for (keypoint_t& k : corners)
		k.Clear();
	
	y.init(sz.cx, sz.cy, 5, 4);
}

void YapeBase::Process() {
    Grayscale(input, tmp0);
    
    box_blur_gray(tmp0, tmp1, 2, 0);
    
    int count = y.detect(tmp1, corners, 5);

    render_corners(corners, output);
}


NAMESPACE_TOPSIDE_END

