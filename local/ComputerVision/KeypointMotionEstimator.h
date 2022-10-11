#ifndef _ComputerVision_KeypointMotionEstimator_h_
#define _ComputerVision_KeypointMotionEstimator_h_


NAMESPACE_TOPSIDE_BEGIN


class KeypointMotionEstimator {
	FloatMat mm3x3;
	Homography2D homo;
	Affine2D aff;
	TransformationKernel& mm_kernel;
	int motionModel = MM_AFFINE;
	RansacParams ransac_param;
	pyra8 curr_img_pyr;
	pyra8 prev_img_pyr;
	ByteMat match_mask;
	int max_points;
	int point_count;
	Vector<byte> point_status;
	Vector<float> prev_xy, curr_xy;
	Vector<Keypoint> corners0, corners1;
	Yape06 y;
	OpticalFlowLK of;
	MotionEstimator<Affine2D> aff_me;
	MotionEstimator<Homography2D> homo_me;
	
public:
	
	KeypointMotionEstimator(int motionModel);
	void Init(Size size);
    const FloatMat& Estimate(ByteMat& frame0, ByteMat& frame1);
    
    int GetMotionModel() const {return motionModel;}
    
};


NAMESPACE_TOPSIDE_END


#endif
