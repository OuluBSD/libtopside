#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


HaarFaceBase::HaarFaceBase() {
	LoadCascadeFrontalFace(classifier);
}

void HaarFaceBase::SetSize(Size sz) {
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
    edg = new jsfeat.matrix_t(w, h, jsfeat.U8_t | jsfeat.C1_t);
    work_canvas = document.createElement('canvas');
    work_canvas.width = w;
    work_canvas.height = h;
    work_ctx = work_canvas.getContext('2d');
    ii_sum = new Int32Array((w+1)*(h+1));
    ii_sqsum = new Int32Array((w+1)*(h+1));
    ii_tilted = new Int32Array((w+1)*(h+1));
    ii_canny = new Int32Array((w+1)*(h+1));

    options = new demo_opt();
    gui = new dat.GUI();

    gui.add(options, 'min_scale', 1, 4).step(0.1);
    gui.add(options, 'scale_factor', 1.1, 2).step(0.025);
    gui.add(options, 'equalize_histogram');
    gui.add(options, 'use_canny');
    gui.add(options, 'edges_density', 0.01, 1.).step(0.005);
    
}

void HaarFaceBase::Process() {
    compatibility.requestAnimationFrame(tick);
    stat.new_frame();
    if (video.readyState === video.HAVE_ENOUGH_DATA) {

        ctx.drawImage(video, 0, 0, canvasWidth, canvasHeight);

        work_ctx.drawImage(video, 0, 0, work_canvas.width, work_canvas.height);
        var imageData = work_ctx.getImageData(0, 0, work_canvas.width, work_canvas.height);
        
        Grayscale(input, work_canvas.width, work_canvas.height, img_u8);

        // possible options
        if(equalize_histogram) {
            equalize_histogram(img_u8, img_u8);
        }
        //gaussian_blur(img_u8, img_u8, 3);

        compute_integral_image(img_u8, ii_sum, ii_sqsum, classifier.tilted ? ii_tilted : null);

        if(use_canny) {
            canny(img_u8, edg, 10, 50);
            compute_integral_image(edg, ii_canny, null, null);
        }

        jsfeat.haar.edges_density = edges_density;
        var rects = jsfeat.haar.detect_multi_scale(ii_sum, ii_sqsum, ii_tilted, use_canny? ii_canny : null, img_u8.cols, img_u8.rows, classifier, scale_factor, min_scale);
        rects = jsfeat.haar.group_rectangles(rects, 1);
        
        // draw only most confident one
        draw_faces(rects, canvasWidth/img_u8.cols, 1);

        $('#log').html(stat.log());
    }
}

void HaarFaceBase::draw_faces(Vector<BBox>& rects, double sc, bool max) {
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
