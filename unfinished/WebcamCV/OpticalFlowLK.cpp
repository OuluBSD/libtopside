#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void OpticalFlowLKBase::InitDefault() {
    curr_img_pyr.SetSize(sz.cx, sz.cy, 1, 3);
    prev_img_pyr.SetSize(sz.cx, sz.cy, 1, 3);

    point_count = 0;
    point_status.SetCount(100, 0);
    prev_xy.SetCount(100*2, 0);
    curr_xy.SetCount(100*2, 0);
    
}

void OpticalFlowLKBase::MakeRandomPoints() {
	while (point_count < 10) {
		bool found = false;
		for(int i = 0; i < point_status.GetCount(); i++) {
			auto& b = point_status[i];
			if (!b) {
				b = true;
				Point p(Random(sz.cx), Random(sz.cy));
				curr_xy[i * 2 + 0] = p.x;
				curr_xy[i * 2 + 1] = p.y;
				prev_xy[i * 2 + 0] = p.x;
				prev_xy[i * 2 + 1] = p.y;
				point_count++;
				found = true;
				break;
			}
		}
		if (!found)
			break;
	}
}

void OpticalFlowLKBase::Process() {
    // swap flow data
    MemSwap(prev_xy, curr_xy);
    MemSwap(prev_img_pyr, curr_img_pyr);

    MakeRandomPoints();
    
    auto& d0 = curr_img_pyr.data[0];
    Grayscale(input, d0);
    
    curr_img_pyr.Build(d0, true);
    
    of.track(prev_img_pyr, curr_img_pyr, prev_xy, curr_xy, point_count, win_size, max_iterations, point_status, epsilon, min_eigen);
    
    OutputFromGray(d0);
    
    prune_oflow_points();
}

/*void OpticalFlowLKBase::on_canvas_click() {
    var coords = canvas.relMouseCoords(e);
    if(coords.x > 0 & coords.y > 0 & coords.x < canvasWidth & coords.y < canvasHeight) {
        curr_xy[point_count<<1] = coords.x;
        curr_xy[(point_count<<1)+1] = coords.y;
        point_count++;
    }
}*/

/*void OpticalFlowLKBase::draw_circle(int x, int y) {
    ctx.beginPath();
    ctx.arc(x, y, 4, 0, Math.PI*2, true);
    ctx.closePath();
    ctx.fill();
}*/

void OpticalFlowLKBase::prune_oflow_points() {
    int n = point_count;
    int i=0,j=0;
	
	points.SetCount(0);
    for(; i < n; ++i) {
        if(point_status[i] == 1) {
            if(j < i) {
                curr_xy[j<<1] = curr_xy[i<<1];
                curr_xy[(j<<1)+1] = curr_xy[(i<<1)+1];
            }
            
            Point p(curr_xy[j<<1], curr_xy[(j<<1)+1]);
            points << p;
            ++j;
        }
    }
    point_count = j;
}

/*Point OpticalFlowLKBase::relMouseCoords(event) {
    var totalOffsetX=0,totalOffsetY=0,canvasX=0,canvasY=0;
    var currentElement = this;

    do {
        totalOffsetX += currentElement.offsetLeft - currentElement.scrollLeft;
        totalOffsetY += currentElement.offsetTop - currentElement.scrollTop;
    } while(currentElement = currentElement.offsetParent)

    canvasX = event.pageX - totalOffsetX;
    canvasY = event.pageY - totalOffsetY;

    return keypoint_t(canvasX, canvasY);
}*/


NAMESPACE_TOPSIDE_END
