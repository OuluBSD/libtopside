#ifndef _ComputerVision_OnepassStabilizer_h_
#define _ComputerVision_OnepassStabilizer_h_


NAMESPACE_TOPSIDE_BEGIN



int GetAreaSign(const Keypoint& a, const Keypoint& b, const Keypoint& c);
bool IsSegmentIntersect(const Keypoint& a, const Keypoint& b, const Keypoint& c, const Keypoint& d);
int IsRectInside(const Vector<Keypoint>& a, const Vector<Keypoint>& b);
bool IsGoodMotion(const FloatMat& M, int w, int h, int dx, int dy);
void RelaxMotion(const Vector<float>& M, double t, Vector<float>& res);
void EnsureInclusionConstraint(FloatMat& M, Size size, double trimRatio);
double EstimateOptimalTrimRatio(const FloatMat& M, const Size& size);


class OnepassStabilizer {
	int radius;
	double trimRatio;
	bool doImage;
	bool doCorrectionForInclusion;
	Size frameSize;
	int frameBufferSize;
	int curPos;
	int curStabilizedPos;
	ByteMat preProcessedFrame;
	Vector<ByteMat> frames;
	Vector<ByteMat> rgba;
	Vector<FloatMat> motions;
	Vector<ByteMat> stabilizedFrames;
	Vector<FloatMat> stabilizationMotions;
	FloatMat eye3x3;
	KeypointMotionEstimator MotionEstimator;
	GaussMotionFilter motion_filter;
	FloatMat im33;
	
public:
    
	OnepassStabilizer(int motionModel);
	void Init(Size sz, int radius=15);
	void reset();
	void Setup(const ByteMat& rgbaImageData);
	const FloatMat& EstimateMotion();
	FloatMat& EstimateStabilizationMotion();
	const ByteMat* PostprocessFrame(const ByteMat& frame);
	const ByteMat* NextStabilizedFrame(const ByteMat& frame_rgba);
	bool DoOneIteration(const ByteMat* frame_rgba);
	void StabilizeFrame();
	
};


NAMESPACE_TOPSIDE_END


#endif
