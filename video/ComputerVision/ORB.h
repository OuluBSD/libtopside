#ifndef _ComputerVision_ORB_h_
#define _ComputerVision_ORB_h_


NAMESPACE_TOPSIDE_BEGIN


class Orb {
	
public:
	static const int bit_pattern_31_[];
	
	FloatMat	H;
	ByteMat		patch_img;
	
	
	Orb();
	void rectify_patch(const ByteMat& src, ByteMat& dst, double angle, int px, int py, int psize);
	void describe(const ByteMat& src, const Vector<keypoint_t>& corners, ByteMat& descriptors);
	
};


NAMESPACE_TOPSIDE_END

#endif
