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
    Grayscale(input, sz.cx, sz.cy, tmp0);
    
    c.set_threshold(threshold);
    
    int count = c.detect(tmp0, corners, 5);
    
    // render result back to canvas
    render_corners(corners, output);
}

void ImageProcBase::render_corners(const Vector<keypoint_t>& corners, ByteMat& out) {
	int count = corners.GetCount();
	int step = sz.cx;
	
	out.SetSize(sz.cx, sz.cy, 4);
	uint32* img = (uint32*)(byte*)out.data.Begin();
	
    uint32 pix = (0xff << 24) | (0x00 << 16) | (0xff << 8) | 0x00;
    for(int i=0; i < count; ++i)
    {
        int x = corners[i].x;
        int y = corners[i].y;
        int off = (x + y * step);
        img[off] = pix;
        img[off-1] = pix;
        img[off+1] = pix;
        img[off-step] = pix;
        img[off+step] = pix;
    }
}


NAMESPACE_TOPSIDE_END

