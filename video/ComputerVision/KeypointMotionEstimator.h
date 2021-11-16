#ifndef _ComputerVision_KeypointMotionEstimator_h_
#define _ComputerVision_KeypointMotionEstimator_h_


NAMESPACE_TOPSIDE_BEGIN


class keypoint_motion_estimator {
	FloatMat mm3x3;
	homography2d homo;
	affine2d aff;
	TransformationKernel& mm_kernel;
	int motionModel = MM_AFFINE;
	ransac_params_t ransac_param;
	pyra8 curr_img_pyr;
	pyra8 prev_img_pyr;
	ByteMat match_mask;
	int max_points;
	int point_count;
	Vector<byte> point_status;
	Vector<float> prev_xy, curr_xy;
	Vector<keypoint_t> corners0, corners1;
	yape06 y;
	optical_flow_lk of;
	motion_estimator<affine2d> aff_me;
	motion_estimator<homography2d> homo_me;
	
public:
	
	keypoint_motion_estimator(int motionModel);
	void Init(Size size);
    const FloatMat& estimate(ByteMat& frame0, ByteMat& frame1);
    
    int GetMotionModel() const {return motionModel;}
    
};


NAMESPACE_TOPSIDE_END


#endif
