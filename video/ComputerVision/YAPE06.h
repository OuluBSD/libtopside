#ifndef _ComputerVision_YAPE06_h_
#define _ComputerVision_YAPE06_h_


NAMESPACE_TOPSIDE_BEGIN

class yape06 {
	float laplacian_threshold = 30;
	float min_eigen_value_threshold = 25;
	
	
public:
	void compute_laplacian(const Vector<float>& src, Vector<float>& dst, int w, int h, int Dxx, int Dyy, int sx, int sy, int ex, int ey);
	double hessian_min_eigen_value(const Vector<float>& src, int off, double tr, int Dxx, int Dyy, int Dxy, int Dyx);
	int detect(const FloatMat& src, Vector<ScorePoint>& points, int border=5);
	
};



NAMESPACE_TOPSIDE_END

#endif
