#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


BbfFaceBase::BbfFaceBase() {
	
}

void BbfFaceBase::SetSize(Size sz) {
	auto& videoWidth = sz.cx;
	auto& videoHeight = sz.cy;
	
    double scale = min((double)max_work_size/videoWidth, (double)max_work_size/videoHeight);
    int w = (int)(videoWidth*scale);
    int h = (int)(videoHeight*scale);
	
	auto& img_u8 = tmp0;
    img_u8.SetSize(w, h, 1);
    
    b.prepare_cascade(cascade);
    
	LoadCascadeBbfFace(cascade);
}

void BbfFaceBase::Process() {
	auto& img_u8 = tmp0;
	
    Grayscale(input, img_u8);

    // possible options
    //equalize_histogram(img_u8, img_u8);

    b.build_pyramid(pyr, img_u8, 24*2, 24*2, 4);
	b.detect(rects, pyr, cascade);
    group_rectangles(rects, result_seq, 1);
    
}

/*void BbfFaceBase::draw_faces(sc, max) {
    var on = rects.length;
    if(on && max) {
        jsfeat.math.qsort(rects, 0, on-1, function(a,b){return (b.confidence<a.confidence);})
    }
    var n = max || on;
    n = Math.min(n, on);
    var r;
    for(var i = 0; i < n; ++i) {
        r = rects[i];
        ctx.strokeRect((r.x*sc),(r.y*sc),(r.width*sc),(r.height*sc));
    }
}*/


NAMESPACE_TOPSIDE_END
