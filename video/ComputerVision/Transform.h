#ifndef _ComputerVision_Transform_h_
#define _ComputerVision_Transform_h_


NAMESPACE_TOPSIDE_BEGIN

class transform {
	
public:

	
	void perspective_4point_transform(
			Vector<float>& mat,
			double src_x0, double src_y0, double dst_x0, double dst_y0,
			double src_x1, double src_y1, double dst_x1, double dst_y1,
			double src_x2, double src_y2, double dst_x2, double dst_y2,
			double src_x3, double src_y3, double dst_x3, double dst_y3);
	void invert_affine_transform(const Vector<double>& src, Vector<double>& dst);
	void invert_perspective_transform(const Vector<double>& src, Vector<double>& dst);
	
};


NAMESPACE_TOPSIDE_END

#endif
