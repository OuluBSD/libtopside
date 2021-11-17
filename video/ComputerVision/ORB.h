#ifndef _ComputerVision_ORB_h_
#define _ComputerVision_ORB_h_


NAMESPACE_TOPSIDE_BEGIN


struct KeypointMatch : Moveable<KeypointMatch> {
    int screen_idx;
    int pattern_lev;
    int pattern_idx;
    int distance;
    
    void Set(int screen_idx=0, int pattern_lev=0, int pattern_idx=0, int distance=0);
};


class Orb {
	
public:
	static const int bit_pattern_31_[];
	
	FloatMat	H;
	ByteMat		patch_img;
	
	
	Orb();
	void RectifyPatch(const ByteMat& src, ByteMat& dst, double angle, int px, int py, int psize);
	void Describe(const ByteMat& src, const Vector<Keypoint>& corners, Vector<BinDescriptor>& descriptors);
	
};


NAMESPACE_TOPSIDE_END

#endif
