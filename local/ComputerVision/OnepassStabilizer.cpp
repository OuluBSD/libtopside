#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


int GetAreaSign(const Keypoint& a, const Keypoint& b, const Keypoint& c) {
	int bax = b.x-a.x, bay = b.y-a.y;
	int cax = c.x-a.x, cay = c.y-a.y;
    int area = bax*cay - bay*cax;
    if (area < -1e-5) return -1;
    if (area > 1e-5) return 1;
    return 0;
}


bool IsSegmentIntersect(const Keypoint& a, const Keypoint& b, const Keypoint& c, const Keypoint& d) {
    return GetAreaSign(a, b, c) * GetAreaSign(a, b, d) < 0 &&
           GetAreaSign(c, d, a) * GetAreaSign(c, d, b) < 0;
}


// Checks if rect a (with sides parallel to axis) is inside rect b (arbitrary).
// Rects must be passed in the [(0,0), (w,0), (w,h), (0,h)] order.
int IsRectInside(const Vector<Keypoint>& a, const Vector<Keypoint>& b) {
	int i=0,j=0;
    for (i = 0; i < 4; ++i)
        if (b[i].x > a[0].x && b[i].x < a[2].x && b[i].y > a[0].y && b[i].y < a[2].y)
            return false;
    for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
        if (IsSegmentIntersect(a[i], a[(i+1)&3], b[j], b[(j+1)&3]))
            return false;
    return true;
}


bool IsGoodMotion(const FloatMat& M, int w, int h, int dx, int dy) {
	static thread_local Vector<Keypoint> pt, Mpt;
	pt  << Keypoint(0,0) << Keypoint(w,0) << Keypoint(w,h) << Keypoint(0,h);
	Mpt << Keypoint(0,0) << Keypoint(0,0) << Keypoint(0,0) << Keypoint(0,0);
	
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

    return IsRectInside(pt, Mpt);
}


void RelaxMotion(const Vector<float>& M, double t, Vector<float>& res) {
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


void EnsureInclusionConstraint(FloatMat& M, Size size, double trimRatio) {
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
    
    RelaxMotion(srcM.data, t, curM.data);
    if (IsGoodMotion(curM, w, h, dx, dy))
        return;

    double l = 0.0, r = 1.0;
    while (r - l > 1e-3)
    {
        t = (l + r) * 0.5;
        RelaxMotion(srcM.data, t, curM.data);
        if (IsGoodMotion(curM, w, h, dx, dy))
            r = t;
        else
            l = t;
    }

    l = 1.0 - r;
    md[0] = md[0]*l+r, md[1] = md[1]*l,   md[2] = md[2]*l;
    md[3] = md[3]*l,   md[4] = md[4]*l+r, md[5] = md[5]*l;
    md[6] = md[6]*l,   md[7] = md[7]*l,   md[8] = md[8]*l+r;
}


double EstimateOptimalTrimRatio(const FloatMat& M, const Size& size) {
    int w = size.cx;
    int h = size.cy;
    const auto& md = M.data;
	
	static thread_local Vector<Keypoint> pt, Mpt;
	pt  << Keypoint(0,0) << Keypoint(w,0) << Keypoint(w,h) << Keypoint(0,h);
	Mpt << Keypoint(0,0) << Keypoint(0,0) << Keypoint(0,0) << Keypoint(0,0);
	
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
        if (IsRectInside(pt, Mpt))
            r = t;
        else
            l = t;
    }

    return r;
}















OnepassStabilizer::OnepassStabilizer(int motionModel) : MotionEstimator(motionModel) {
    
}

void OnepassStabilizer::Init(Size sz, int radius) {
    reset();
    
    this->radius = radius;
    trimRatio = 0.0;
    doImage = true;
    doCorrectionForInclusion = false;
    frameSize = Size(0,0);
    frameBufferSize = -1;
    curPos = -1;
    curStabilizedPos = -1;
    
    motion_filter.Setup(radius);

	eye3x3.SetSize(3,3,1);
	Identity3x3(eye3x3, 1.0f);
	
	im33.SetSize(3,3,1);
	
    
    
    MotionEstimator.Init(sz);
    
    
}

void OnepassStabilizer::reset() {
	frameSize.cx = frameSize.cy = 0;
    curPos = -1;
    curStabilizedPos = -1;
    frameBufferSize = -1;
    frames.SetCount(0);
    rgba.SetCount(0);
    motions.SetCount(0);
    stabilizedFrames.SetCount(0);
}

void OnepassStabilizer::Setup(const ByteMat& rgbaImageData) {
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
		j = GetRingIndex(i, cache_size);
		eye3x3.copy_to( motions[j] );
		gray.copy_to( frames[j] );
		rgba[-i] = rgbaImageData;
    }

    gray.copy_to( frames[0] );
    rgba[0] = rgbaImageData;

    if (doImage) {
		preProcessedFrame.SetSize(w, h, 1);
    }
}

const FloatMat& OnepassStabilizer::EstimateMotion()
{
	int id0 = GetRingIndex(curPos - 1, frameBufferSize)|0;
	int id1 = GetRingIndex(curPos, frameBufferSize)|0;
    return MotionEstimator.Estimate( frames[id0], frames[id1] );
}


FloatMat& OnepassStabilizer::EstimateStabilizationMotion()
{
    return motion_filter.Stabilize(curStabilizedPos, motions, 0, curPos);
}


const ByteMat* OnepassStabilizer::PostprocessFrame(const ByteMat& frame)
{
    return &frame;
}

const ByteMat* OnepassStabilizer::NextStabilizedFrame(const ByteMat& frame_rgba) {

    // check if we've processed all frames already
    if (curStabilizedPos == curPos && curStabilizedPos != -1)
    {
        LOG("no more frames");
        return 0;
    }

    bool processed = true;
    do {
		processed = DoOneIteration(&frame_rgba);
    }
    while (processed && curStabilizedPos == -1);

    // check if the frame source is empty
    if (curStabilizedPos == -1) {
		LOG("frame source is empty");
        return 0;
    }
	
	ASSERT(doImage); // type conflict
    /*if(!doImage) {
		return &GetAt(curStabilizedPos, frameBufferSize, stabilizationMotions);
    }*/

    return PostprocessFrame( GetAt(curStabilizedPos, frameBufferSize, stabilizedFrames) );
}

bool OnepassStabilizer::DoOneIteration(const ByteMat* frame_rgba) {
    if (frame_rgba) {
        curPos++;

        if (curPos > 0) {

            ByteMat& gray_frame = GetAt(curPos, frameBufferSize, frames);
            ASSERT(frame_rgba->cols == gray_frame.cols && frame_rgba->rows == gray_frame.rows);
            Grayscale(*frame_rgba, gray_frame);
			
			int i = GetRingIndex(curPos, frameBufferSize);
			rgba[i] = *frame_rgba;

            const FloatMat& m33 = EstimateMotion();
            m33.copy_to( GetAt(curPos-1, frameBufferSize, motions) );

            if (curPos >= radius) {
                curStabilizedPos = curPos - radius;
                StabilizeFrame();
            }
        }
        else
            Setup(*frame_rgba);

        return true;
    }

    if (curStabilizedPos < curPos) {
        curStabilizedPos++;

        GetAt(curPos, frameBufferSize, frames).copy_to( GetAt(curStabilizedPos + radius, frameBufferSize, frames) );

        eye3x3.copy_to( GetAt(curStabilizedPos+radius-1, frameBufferSize, motions) );

        rgba[GetRingIndex(curStabilizedPos + radius, frameBufferSize)] = rgba[ GetRingIndex(curPos, frameBufferSize) ];

        StabilizeFrame();

        return true;
    }

    return false;
}


void OnepassStabilizer::StabilizeFrame() {
    FloatMat& stabilizationMotion = EstimateStabilizationMotion();
    
    if (doCorrectionForInclusion) {
		EnsureInclusionConstraint(stabilizationMotion, frameSize, trimRatio);
    }
    
    stabilizationMotion.copy_to( GetAt(curStabilizedPos, frameBufferSize, stabilizationMotions) );

    // apply stabilization transformation

    if (doImage) {

		GetAt(curStabilizedPos, frameBufferSize, frames).copy_to( preProcessedFrame );

	    Invert3x3(stabilizationMotion, im33);

	    if(MotionEstimator.GetMotionModel() == MM_AFFINE) {
			WarpAffine(preProcessedFrame,
								GetAt(curStabilizedPos, frameBufferSize, stabilizedFrames),
								im33, 0);
		} else {
			WarpPerspective(preProcessedFrame,
							GetAt(curStabilizedPos, frameBufferSize, stabilizedFrames),
							im33, 0);
		}
	} else {
		preProcessedFrame = rgba[ GetRingIndex(curStabilizedPos, frameBufferSize) ];
	}
}


NAMESPACE_TOPSIDE_END
