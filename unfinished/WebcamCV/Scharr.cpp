#include "WebcamCV.h"

NAMESPACE_TOPSIDE_BEGIN

void ScharrBase::Process() {
	auto& img_u8 = tmp0;
	
    Grayscale(input, sz.cx, sz.cy, img_u8);
    
    scharr_derivatives(img_u8, img_gxgy);
    
    // render result back to canvas
    static thread_local Vector<uint32> data_u32;
    int i = img_u8.cols*img_u8.rows, pix=0, gx = 0, gy = 0;
    data_u32.SetCount(i);
    while(--i >= 0) {
        gx = abs(img_gxgy.data[i<<1]>>2)&0xff;
        gy = abs(img_gxgy.data[(i<<1)+1]>>2)&0xff;
        pix = ((gx + gy)>>2)&0xff;
        data_u32[i] = (pix << 24) | (gx << 16) | (0 << 8) | gy;
    }
}

NAMESPACE_TOPSIDE_END
