#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


BbfFaceBase::BbfFaceBase() {
	
}

void BbfFaceBase::InitDefault() {
    double scale = min((double)max_work_size/sz.cx, (double)max_work_size/sz.cy);
    int w = (int)(sz.cx*scale);
    int h = (int)(sz.cy*scale);
	
	auto& img_u8 = tmp0;
    img_u8.SetSize(w, h, 1);
    
	LoadCascadeBbfFace(cascade);
    b.prepare_cascade(cascade);
    
}

void BbfFaceBase::Process() {
	auto& img_u8 = tmp0;
	
	ASSERT(cascade.count > 0);
	
    Grayscale(input, img_u8);

    // possible options
    //equalize_histogram(img_u8, img_u8);

    b.build_pyramid(pyr, img_u8, 24*2, 24*2, 4);
	b.detect(detected_rects, pyr, cascade);
	
	int limit = 10;
	if (detected_rects.GetCount() > limit) {
		Sort(detected_rects, BBox());
		detected_rects.SetCount(limit);
	}
	
    group_rectangles(detected_rects, rects, 1);
    
    OutputFromGray(img_u8);
}



NAMESPACE_TOPSIDE_END
