#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void BbfFaceBase::SetSize(Size sz) {
	auto& videoWidth = sz.cx;
	auto& videoHeight = sz.cy;
    canvasWidth  = canvas.width;
    canvasHeight = canvas.height;
    ctx = canvas.getContext('2d');

    ctx.fillStyle = "rgb(0,255,0)";
    ctx.strokeStyle = "rgb(0,255,0)";

    var scale = Math.min(max_work_size/videoWidth, max_work_size/videoHeight);
    var w = (videoWidth*scale);
    var h = (videoHeight*scale);

    img_u8 = new jsfeat.matrix_t(w, h, jsfeat.U8_t | jsfeat.C1_t);
    work_canvas = document.createElement('canvas');
    work_canvas.width = w;
    work_canvas.height = h;
    work_ctx = work_canvas.getContext('2d');

    jsfeat.bbf.prepare_cascade(jsfeat.bbf.face_cascade);
    
}

void BbfFaceBase::Process() {
    work_ctx.drawImage(video, 0, 0, work_canvas.width, work_canvas.height);
    var imageData = work_ctx.getImageData(0, 0, work_canvas.width, work_canvas.height);
    
    Grayscale(input, work_canvas.width, work_canvas.height, img_u8);

    // possible options
    //equalize_histogram(img_u8, img_u8);

    var pyr = jsfeat.bbf.build_pyramid(img_u8, 24*2, 24*2, 4);

    var rects = jsfeat.bbf.detect(pyr, jsfeat.bbf.face_cascade);
    rects = jsfeat.bbf.group_rectangles(rects, 1);
    
}

void BbfFaceBase::draw_faces(rects, sc, max) {
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
}


NAMESPACE_TOPSIDE_END
