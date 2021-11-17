#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void Yape06Base::SetSize(Size sz) {
	ASSERT(!sz.IsEmpty());
	
	this->sz = sz;
	
	corners.SetCount(sz.cx * sz.cy);
	for (Keypoint& k : corners)
		k.Clear();
	
}

void Yape06Base::Process() {
    Grayscale(input, tmp0);
    
    BoxBlurGray(tmp0, tmp1, 2, 0);
    
    y.laplacian_threshold = lap_thres;
    y.min_eigen_value_threshold = eigen_thres;
    
    int count = y.Detect(tmp1, corners);
    
    RenderCorners(corners, output);
}


NAMESPACE_TOPSIDE_END
