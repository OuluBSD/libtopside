#ifndef _ComputerVision_FAST_h_
#define _ComputerVision_FAST_h_


NAMESPACE_TOPSIDE_BEGIN

class FastCorners {
	typedef Vector<int> PixVec;
	
	Vector<byte> threshold_tab;
	PixVec pixel_off;
	Vector<int> score_diff;
	int _threshold = 20;
	
public:
	static const int offsets16[];
	
	
	FastCorners();
	
	int set_threshold(int threshold);
	int Detect(const ByteMat& src, Vector<Keypoint>& corners, int border = 3);
	
private:
	void _cmp_offsets(PixVec& pixel, int step, int pattern_size);
	
	static int _cmp_score_16(const Vector<byte>& src, int off, const PixVec& pixel, Vector<int>& d, int threshold);
	
};


NAMESPACE_TOPSIDE_END

#endif
