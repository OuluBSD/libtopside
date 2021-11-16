#ifndef _ComputerVision_GaussMotionFilter_h_
#define _ComputerVision_GaussMotionFilter_h_


NAMESPACE_TOPSIDE_BEGIN


class gauss_motion_filter {
	int radius = 15;
	double stdev = -1.0;
	
	Vector<float> weight;
	matrix_t<float> m33;
	
public:
	
	void setup(int radius=15, double stdev=-1.0);
	FloatMat& stabilize(int idx, Vector<FloatMat>& motions, int from_idx, int to_idx);
	
};


NAMESPACE_TOPSIDE_END


#endif
