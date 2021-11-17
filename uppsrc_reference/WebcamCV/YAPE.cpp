#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN



void YapeBase::InitDefault() {
	ASSERT(!sz.IsEmpty() && sz.cx > 0 && sz.cy > 0);
	
	corners.SetCount(sz.cx * sz.cy);
	for (Keypoint& k : corners)
		k.Clear();
	
	y.Init(sz.cx, sz.cy, 5, 4);
}

void YapeBase::Process() {
    Grayscale(input, tmp0);
    
    BoxBlurGray(tmp0, tmp1, 2, 0);
    
    int count = y.Detect(tmp1, corners, 5);

    RenderCorners(corners, output);
}


NAMESPACE_TOPSIDE_END

