#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void OpticalFlowLKBase::SetSize(Size sz) {
	auto& videoWidth = sz.cx;
	auto& videoHeight = sz.cy;
    ctx = canvas.getContext('2d');

    ctx.fillStyle = "rgb(0,255,0)";
    ctx.strokeStyle = "rgb(0,255,0)";

    curr_img_pyr = new jsfeat.pyramid_t(3);
    prev_img_pyr = new jsfeat.pyramid_t(3);
    curr_img_pyr.allocate(sz.cx, sz.cy, jsfeat.U8_t|jsfeat.C1_t);
    prev_img_pyr.allocate(sz.cx, sz.cy, jsfeat.U8_t|jsfeat.C1_t);

    point_count = 0;
    point_status = new Uint8Array(100);
    prev_xy = new Float32Array(100*2);
    curr_xy = new Float32Array(100*2);

    options = new demo_opt();
    gui = new dat.GUI();

    gui.add(options, 'win_size', 7, 30).step(1);
    gui.add(options, 'max_iterations', 3, 30).step(1);
    gui.add(options, 'epsilon', 0.001, 0.1).step(0.0025);
    gui.add(options, 'min_eigen', 0.001, 0.01).step(0.0025);

    stat.add("grayscale");
    stat.add("build image pyramid");
    stat.add("optical flow lk");
}

void OpticalFlowLKBase::Process() {
    compatibility.requestAnimationFrame(tick);
    stat.new_frame();
    if (video.readyState === video.HAVE_ENOUGH_DATA) {
        ctx.drawImage(video, 0, 0, sz.cx, sz.cy);
        var imageData = ctx.getImageData(0, 0, sz.cx, sz.cy);

        // swap flow data
        var _pt_xy = prev_xy;
        prev_xy = curr_xy;
        curr_xy = _pt_xy;
        var _pyr = prev_img_pyr;
        prev_img_pyr = curr_img_pyr;
        curr_img_pyr = _pyr;

        Grayscale(input, sz.cx, sz.cy, curr_img_pyr.data[0]);
        
        curr_img_pyr.build(curr_img_pyr.data[0], true);
        
        jsfeat.optical_flow_lk.track(prev_img_pyr, curr_img_pyr, prev_xy, curr_xy, point_count, win_size, max_iterations, point_status, epsilon, min_eigen);
        
        prune_oflow_points(ctx);

    }
}

void OpticalFlowLKBase::on_canvas_click() {
    var coords = canvas.relMouseCoords(e);
    if(coords.x > 0 & coords.y > 0 & coords.x < canvasWidth & coords.y < canvasHeight) {
        curr_xy[point_count<<1] = coords.x;
        curr_xy[(point_count<<1)+1] = coords.y;
        point_count++;
    }
}

void OpticalFlowLKBase::draw_circle(int x, int y) {
    ctx.beginPath();
    ctx.arc(x, y, 4, 0, Math.PI*2, true);
    ctx.closePath();
    ctx.fill();
}

void OpticalFlowLKBase::prune_oflow_points(ctx) {
    var n = point_count;
    var i=0,j=0;

    for(; i < n; ++i) {
        if(point_status[i] == 1) {
            if(j < i) {
                curr_xy[j<<1] = curr_xy[i<<1];
                curr_xy[(j<<1)+1] = curr_xy[(i<<1)+1];
            }
            draw_circle(curr_xy[j<<1], curr_xy[(j<<1)+1]);
            ++j;
        }
    }
    point_count = j;
}

Point OpticalFlowLKBase::relMouseCoords(event) {
    var totalOffsetX=0,totalOffsetY=0,canvasX=0,canvasY=0;
    var currentElement = this;

    do {
        totalOffsetX += currentElement.offsetLeft - currentElement.scrollLeft;
        totalOffsetY += currentElement.offsetTop - currentElement.scrollTop;
    } while(currentElement = currentElement.offsetParent)

    canvasX = event.pageX - totalOffsetX;
    canvasY = event.pageY - totalOffsetY;

    return Point(canvasX, canvasY);
}


NAMESPACE_TOPSIDE_END
