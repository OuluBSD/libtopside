#ifndef _ComputerVision_Transform_h_
#define _ComputerVision_Transform_h_


NAMESPACE_TOPSIDE_BEGIN

class transform {
	
public:

	
	void Perspective4PointTransform(
			Vector<float>& mat,
			double src_x0, double src_y0, double dst_x0, double dst_y0,
			double src_x1, double src_y1, double dst_x1, double dst_y1,
			double src_x2, double src_y2, double dst_x2, double dst_y2,
			double src_x3, double src_y3, double dst_x3, double dst_y3);
	void InvertAffineTransform(const Vector<double>& src, Vector<double>& dst);
	void InvertPerspectiveTransform(const Vector<double>& src, Vector<double>& dst);
	
};


NAMESPACE_TOPSIDE_END

#endif
