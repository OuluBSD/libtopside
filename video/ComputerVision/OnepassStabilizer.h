#ifndef _ComputerVision_OnepassStabilizer_h_
#define _ComputerVision_OnepassStabilizer_h_


NAMESPACE_TOPSIDE_BEGIN



int areaSign(const keypoint_t& a, const keypoint_t& b, const keypoint_t& c);
bool segmentsIntersect(const keypoint_t& a, const keypoint_t& b, const keypoint_t& c, const keypoint_t& d);
int isRectInside(const Vector<keypoint_t>& a, const Vector<keypoint_t>& b);
bool isGoodMotion(const FloatMat& M, int w, int h, int dx, int dy);
void relaxMotion(const Vector<float>& M, double t, Vector<float>& res);
void ensureInclusionConstraint(FloatMat& M, Size size, double trimRatio);
double estimateOptimalTrimRatio(const FloatMat& M, const Size& size);


class onepass_stabilizer {
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
	keypoint_motion_estimator motion_estimator;
	gauss_motion_filter motion_filter;
	FloatMat im33;
	
public:
    
	onepass_stabilizer(int motionModel);
	void Init(Size sz);
	void reset();
	void setup(const ByteMat& rgbaImageData);
	const FloatMat& estimate_motion();
	FloatMat& estimate_stabilization_motion();
	const ByteMat* postprocess_frame(const ByteMat& frame);
	const ByteMat* next_stabilized_frame(const ByteMat& frame_rgba);
	bool do_one_iteration(const ByteMat* frame_rgba);
	void stabilize_frame();
	
};


NAMESPACE_TOPSIDE_END


#endif
