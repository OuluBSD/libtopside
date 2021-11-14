#ifndef _ComputerVision_HAAR_h_
#define _ComputerVision_HAAR_h_


NAMESPACE_TOPSIDE_BEGIN

class haar {
	double edges_density = 0.07;
	Vector<BBox> rects;
	Vector<BBox> idx_seq, comps, seq2, result_seq;
	
public:
	
	const Vector<BBox>& detect_single_scale(const Vector<int>& int_sum, const Vector<int>& int_sqsum, const Vector<int>& int_tilted, const Vector<int>& int_canny_sum, int width, int height, double scale, const ComplexCascade& classifier);
	const Vector<BBox>& detect_multi_scale(const Vector<int>& int_sum, const Vector<int>& int_sqsum, const Vector<int>& int_tilted, const Vector<int>& int_canny_sum, int width, int height, const ComplexCascade& classifier, double scale_factor = 1.2, double scale_min = 1.0);
	
	
};



NAMESPACE_TOPSIDE_END

#endif
