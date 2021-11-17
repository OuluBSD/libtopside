#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void FastCornersBase::SetSize(Size sz) {
	ASSERT(!sz.IsEmpty());
	
	this->sz = sz;
	
	corners.SetCount(sz.cx * sz.cy);
	for (keypoint_t& k : corners)
		k.Clear();
	
}

void FastCornersBase::Process() {
    Grayscale(input, tmp0);
    
    c.set_threshold(threshold);
    
    int count = c.detect(tmp0, corners, 5);
    
    // render result back to canvas
    render_corners(corners, output);
}


NAMESPACE_TOPSIDE_END

