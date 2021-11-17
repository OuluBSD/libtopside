#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


HaarFaceBase::HaarFaceBase() {
	
}

void HaarFaceBase::InitDefault() {
	auto& videoWidth = sz.cx;
	auto& videoHeight = sz.cy;
	
	use_canny = 0;
	scale_factor = 2;
	
	LoadCascadeFrontalFace(classifier);
	//LoadCascadeMouth(classifier);
	
    double scale = min((double)max_work_size/videoWidth, (double)max_work_size/videoHeight);
    int w = (videoWidth*scale);
    int h = (videoHeight*scale);
	
	auto& img_u8 = tmp0;
	auto& edg = tmp1;
    img_u8.SetSize(w, h, 1);
    edg.SetSize(w, h, 1);
    
    ii_sum.SetCount((w+1)*(h+1));
    ii_sqsum.SetCount((w+1)*(h+1));
    if (classifier.tilted)
		ii_tilted.SetCount((w+1)*(h+1));
    if (use_canny)
		ii_canny.SetCount((w+1)*(h+1));
	
}

void HaarFaceBase::Process() {
	auto& img_u8 = tmp0;
	auto& edg = tmp1;
	
    Grayscale(input, img_u8);

    // possible options
    if(is_EqualizeHistogram) {
        EqualizeHistogram(img_u8, img_u8);
    }
    //GaussianBlur(img_u8, img_u8, 3);

    ComputeIntegralImage(img_u8, ii_sum, &ii_sqsum, classifier.tilted ? &ii_tilted : 0);

    if(use_canny) {
        Canny(img_u8, edg, 10, 50);
        ComputeIntegralImage(edg, ii_canny, 0, 0);
    }

    h.SetEdgeDensity(edges_density);
    h.DetectMultiScale(detected_rects, ii_sum, ii_sqsum, ii_tilted, use_canny ? &ii_canny : 0, img_u8.cols, img_u8.rows, classifier, scale_factor, min_scale);
    
	int limit = 10;
	if (detected_rects.GetCount() > limit) {
		Sort(detected_rects, BBox());
		detected_rects.SetCount(limit);
	}
	
    GroupRectangles(detected_rects, rects, 1);
    
    OutputFromGray(img_u8);
}



NAMESPACE_TOPSIDE_END
