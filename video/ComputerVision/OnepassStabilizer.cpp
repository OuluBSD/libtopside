#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


int areaSign(const keypoint_t& a, const keypoint_t& b, const keypoint_t& c) {
	int bax = b.x-a.x, bay = b.y-a.y;
	int cax = c.x-a.x, cay = c.y-a.y;
    int area = bax*cay - bay*cax;
    if (area < -1e-5) return -1;
    if (area > 1e-5) return 1;
    return 0;
}


bool segmentsIntersect(const keypoint_t& a, const keypoint_t& b, const keypoint_t& c, const keypoint_t& d) {
    return areaSign(a, b, c) * areaSign(a, b, d) < 0 &&
           areaSign(c, d, a) * areaSign(c, d, b) < 0;
}


// Checks if rect a (with sides parallel to axis) is inside rect b (arbitrary).
// Rects must be passed in the [(0,0), (w,0), (w,h), (0,h)] order.
int isRectInside(const Vector<keypoint_t>& a, const Vector<keypoint_t>& b) {
	int i=0,j=0;
    for (i = 0; i < 4; ++i)
        if (b[i].x > a[0].x && b[i].x < a[2].x && b[i].y > a[0].y && b[i].y < a[2].y)
            return false;
    for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
        if (segmentsIntersect(a[i], a[(i+1)&3], b[j], b[(j+1)&3]))
            return false;
    return true;
}


bool isGoodMotion(const FloatMat& M, int w, int h, int dx, int dy) {
	static thread_local Vector<keypoint_t> pt, Mpt;
	pt  << keypoint_t(0,0) << keypoint_t(w,0) << keypoint_t(w,h) << keypoint_t(0,h);
	Mpt << keypoint_t(0,0) << keypoint_t(0,0) << keypoint_t(0,0) << keypoint_t(0,0);
	
    const auto& md = M.data;
    double z = 0.0;
    int i = 0;

    for (; i < 4; ++i) {
        const auto& p = pt[i];
        auto& o = Mpt[i];
        o.x = md[0]*p.x + md[1]*p.y + md[2];
        o.y = md[3]*p.x + md[4]*p.y + md[5];
        z   = md[6]*p.x + md[7]*p.y + md[8];
        o.x /= z;
        o.y /= z;
    }

    pt[0].x = dx, pt[0].y = dy;
    pt[1].x = w - dx, pt[1].y = dy;
    pt[2].x = w - dx, pt[2].y = h - dy;
    pt[3].x = dx, pt[3].y = h - dy;

    return isRectInside(pt, Mpt);
}


void relaxMotion(const Vector<float>& M, double t, Vector<float>& res) {
    res[0] = M[0]*(1.0-t) + t;
    res[1] = M[1]*(1.0-t);
    res[2] = M[2]*(1.0-t);
    res[3] = M[3]*(1.0-t);
    res[4] = M[4]*(1.0-t) + t;
    res[5] = M[5]*(1.0-t);
    res[6] = M[6]*(1.0-t);
    res[7] = M[7]*(1.0-t);
    res[8] = M[8]*(1.0-t) + t;
}


void ensureInclusionConstraint(FloatMat& M, Size size, double trimRatio) {
    int w = size.cx;
    int h = size.cy;
    int dx = floor(w * trimRatio);
    int dy = floor(h * trimRatio);
    auto& md = M.data;
    FloatMat srcM;
    srcM.SetSize(3,3,1);
    for(int i = 0; i < 9; i++)
		srcM.data[i] = md[i];
    
    FloatMat curM;
    double t = 0.0;
    
    relaxMotion(srcM.data, t, curM.data);
    if (isGoodMotion(curM, w, h, dx, dy))
        return;

    double l = 0.0, r = 1.0;
    while (r - l > 1e-3)
    {
        t = (l + r) * 0.5;
        relaxMotion(srcM.data, t, curM.data);
        if (isGoodMotion(curM, w, h, dx, dy))
            r = t;
        else
            l = t;
    }

    l = 1.0 - r;
    md[0] = md[0]*l+r, md[1] = md[1]*l,   md[2] = md[2]*l;
    md[3] = md[3]*l,   md[4] = md[4]*l+r, md[5] = md[5]*l;
    md[6] = md[6]*l,   md[7] = md[7]*l,   md[8] = md[8]*l+r;
}


double estimateOptimalTrimRatio(const FloatMat& M, const Size& size) {
    int w = size.cx;
    int h = size.cy;
    const auto& md = M.data;
	
	static thread_local Vector<keypoint_t> pt, Mpt;
	pt  << keypoint_t(0,0) << keypoint_t(w,0) << keypoint_t(w,h) << keypoint_t(0,h);
	Mpt << keypoint_t(0,0) << keypoint_t(0,0) << keypoint_t(0,0) << keypoint_t(0,0);
	
    double z = 0.0;
    int i = 0;

    for (; i < 4; ++i) {
        const auto& p = pt[i];
        auto& o = Mpt[i];
        o.x = md[0]*p.x + md[1]*p.y + md[2];
        o.y = md[3]*p.x + md[4]*p.y + md[5];
        z   = md[6]*p.x + md[7]*p.y + md[8];
        o.x /= z;
        o.y /= z;
    }
	
	int l = 0;
	double r = 0.5;
    while (r - l > 1e-3)
    {
        double t = (l + r) * 0.5;
        double dx = floor(w * t);
        double dy = floor(h * t);
        pt[0].x = dx, pt[0].y = dy;
        pt[1].x = w - dx, pt[1].y = dy;
        pt[2].x = w - dx, pt[2].y = h - dy;
        pt[3].x = dx, pt[3].y = h - dy;
        if (isRectInside(pt, Mpt))
            r = t;
        else
            l = t;
    }

    return r;
}















onepass_stabilizer::onepass_stabilizer(int motionModel) : motion_estimator(motionModel) {
    radius = 15;
    trimRatio = 0.0;
    doImage = true;
    doCorrectionForInclusion = false;
    frameSize = Size(0,0);
    frameBufferSize = -1;
    curPos = -1;
    curStabilizedPos = -1;
    
    motion_filter.setup(radius);

	eye3x3.SetSize(3,3,1);
	identity_3x3(eye3x3, 1.0f);
	
	im33.SetSize(3,3,1);
	
    reset();
}

void onepass_stabilizer::Init(Size sz) {
    
    motion_estimator.Init(sz);
    
    
}

void onepass_stabilizer::reset() {
	frameSize.cx = frameSize.cy = 0;
    curPos = -1;
    curStabilizedPos = -1;
    frameBufferSize = -1;
    frames.SetCount(0);
    rgba.SetCount(0);
    motions.SetCount(0);
    stabilizedFrames.SetCount(0);
}

void onepass_stabilizer::setup(const ByteMat& rgbaImageData) {
    int w = frameSize.cx = rgbaImageData.cols;
    int h = frameSize.cy = rgbaImageData.rows;

    int cache_size = 2*radius + 1;
    frames.SetCount(cache_size);
    rgba.SetCount(cache_size);
    stabilizedFrames.SetCount(cache_size);
    motions.SetCount(cache_size);
    stabilizationMotions.SetCount(cache_size);

    frameBufferSize = cache_size;

    int i = 0, j=0;

    // create objects
    for (auto& m : motions) m.SetSize(3, 3, 1);
    for (auto& m : frames) m.SetSize(w, h, 1);
    for (auto& m : stabilizationMotions) m.SetSize(3,3,1);
    for (auto& m : stabilizedFrames) m.SetSize(w, h, 1);

    static thread_local ByteMat gray;
    Grayscale(rgbaImageData, gray);

    for (i = -radius; i < 0; ++i) {
		j = get_ring_ind(i, cache_size);
		eye3x3.copy_to( motions[j] );
		gray.copy_to( frames[j] );
		rgba[i] = rgbaImageData;
    }

    gray.copy_to( frames[0] );
    rgba[0] = rgbaImageData;

    if (doImage) {
		preProcessedFrame.SetSize(w, h, 1);
    }
}

const FloatMat& onepass_stabilizer::estimate_motion()
{
	int id0 = get_ring_ind(curPos - 1, frameBufferSize)|0;
	int id1 = get_ring_ind(curPos, frameBufferSize)|0;
    return motion_estimator.estimate( frames[id0], frames[id1] );
}


FloatMat& onepass_stabilizer::estimate_stabilization_motion()
{
    return motion_filter.stabilize(curStabilizedPos, motions, 0, curPos);
}


const ByteMat* onepass_stabilizer::postprocess_frame(const ByteMat& frame)
{
    return &frame;
}

const ByteMat* onepass_stabilizer::next_stabilized_frame(const ByteMat& frame_rgba) {

    // check if we've processed all frames already
    if (curStabilizedPos == curPos && curStabilizedPos != -1)
    {
        LOG("no more frames");
        return 0;
    }

    bool processed = true;
    do {
		processed = do_one_iteration(&frame_rgba);
    }
    while (processed && curStabilizedPos == -1);

    // check if the frame source is empty
    if (curStabilizedPos == -1) {
		LOG("frame source is empty");
        return 0;
    }
	
	ASSERT(doImage); // type conflict
    /*if(!doImage) {
		return &get_at(curStabilizedPos, frameBufferSize, stabilizationMotions);
    }*/

    return postprocess_frame( get_at(curStabilizedPos, frameBufferSize, stabilizedFrames) );
}

bool onepass_stabilizer::do_one_iteration(const ByteMat* frame_rgba) {
    if (frame_rgba) {
        curPos++;

        if (curPos > 0) {

            ByteMat& gray_frame = get_at(curPos, frameBufferSize, frames);
            ASSERT(frame_rgba->cols == gray_frame.cols && frame_rgba->rows == gray_frame.rows);
            Grayscale(*frame_rgba, gray_frame);

            rgba[get_ring_ind(curPos, frameBufferSize)] = *frame_rgba;

            const FloatMat& m33 = estimate_motion();
            m33.copy_to( get_at(curPos-1, frameBufferSize, motions) );

            if (curPos >= radius) {
                curStabilizedPos = curPos - radius;
                stabilize_frame();
            }
        }
        else
            setup(*frame_rgba);

        return true;
    }

    if (curStabilizedPos < curPos) {
        curStabilizedPos++;

        get_at(curPos, frameBufferSize, frames).copy_to( get_at(curStabilizedPos + radius, frameBufferSize, frames) );

        eye3x3.copy_to( get_at(curStabilizedPos+radius-1, frameBufferSize, motions) );

        rgba[get_ring_ind(curStabilizedPos + radius, frameBufferSize)] = rgba[ get_ring_ind(curPos, frameBufferSize) ];

        stabilize_frame();

        return true;
    }

    return false;
}


void onepass_stabilizer::stabilize_frame() {
    FloatMat& stabilizationMotion = estimate_stabilization_motion();
    
    if (doCorrectionForInclusion) {
		ensureInclusionConstraint(stabilizationMotion, frameSize, trimRatio);
    }
    
    stabilizationMotion.copy_to( get_at(curStabilizedPos, frameBufferSize, stabilizationMotions) );

    // apply stabilization transformation

    if (doImage) {

		get_at(curStabilizedPos, frameBufferSize, frames).copy_to( preProcessedFrame );

	    invert_3x3(stabilizationMotion, im33);

	    if(motion_estimator.GetMotionModel() == MM_AFFINE) {
			warp_affine(preProcessedFrame,
								get_at(curStabilizedPos, frameBufferSize, stabilizedFrames),
								im33, 0);
		} else {
			warp_perspective(preProcessedFrame,
							get_at(curStabilizedPos, frameBufferSize, stabilizedFrames),
							im33, 0);
		}
	} else {
		preProcessedFrame = rgba[ get_ring_ind(curStabilizedPos, frameBufferSize) ];
	}
}


NAMESPACE_TOPSIDE_END
