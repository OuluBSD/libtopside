#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


//VideoStabilizerBase::VideoStabilizerBase() : stabilizer(MM_AFFINE) {
VideoStabilizerBase::VideoStabilizerBase() : stabilizer(MM_HOMOGRAPHY) {
	
}

void VideoStabilizerBase::TCorners(const Vector<float>& M, int w, int h) {
	corners.SetCount(0);
	corners.Reserve(4);
    corners << Keypoint(0,0) << Keypoint(w,0) << Keypoint(w,h) << Keypoint(0,h);
    double z=0.0;
    double px=0.0, py=0.0;

    for (Keypoint& p : corners) {
        px = M[0]*p.x + M[1]*p.y + M[2];
        py = M[3]*p.x + M[4]*p.y + M[5];
        z = M[6]*p.x + M[7]*p.y + M[8];
        p.x = px/z;
        p.y = py/z;
    }
}

void VideoStabilizerBase::InitDefault() {
	ASSERT(!sz.IsEmpty());
	stabilizer.Init(sz, 10);
}

void VideoStabilizerBase::Process() {
    const ByteMat* out = stabilizer.NextStabilizedFrame(input);

	if (out)
		OutputFromGray(*out);
}



NAMESPACE_TOPSIDE_END

