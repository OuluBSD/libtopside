#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN


void Yape06::ComputeLaplacian(const Vector<byte>& src, Vector<int>& dst, int w, int h, int Dxx, int Dyy, int sx, int sy, int ex, int ey) {
	int yrow = (sy * w + sx);
	int row = yrow;
	
	for (int y = sy; y < ey; ++y, yrow += w, row = yrow) {
		for (int x = sx; x < ex; ++x, ++row) {
			dst[row] =	  -4 * src[row]
						     + src[row+Dxx]
						     + src[row-Dxx]
						     + src[row+Dyy]
						     + src[row-Dyy];
		}
	}
}

double Yape06::HessianMinEigenValue(const Vector<byte>& src, int off, double tr, int Dxx, int Dyy, int Dxy, int Dyx) {
	double Ixx = -2 * src[off] + src[off + Dxx] + src[off - Dxx];
	double Iyy = -2 * src[off] + src[off + Dyy] + src[off - Dyy];
	double Ixy = src[off + Dxy] + src[off - Dxy] - src[off + Dyx] - src[off - Dyx];
	double sqrt_delta = (FastSqrt(((Ixx - Iyy) * (Ixx - Iyy) + 4 * Ixy * Ixy)));
	
	return min(abs(tr - sqrt_delta), abs(-(tr + sqrt_delta)));
}

int Yape06::Detect(const ByteMat& src, Vector<Keypoint>& points, int border) {
	using T = int;
	
	int w = src.cols;
	int h = src.rows;
	auto& srd_d = src.data;
	int Dxx = 5;
	int Dyy = (5 * w);
	int Dxy = (3 + 3 * w);
	int Dyx = (3 - 3 * w);
	
	static thread_local Vector<T> laplacian;
	T lv = 0;
	int row = 0;
	int rowx = 0;
	T min_eigen_value = 0;
	int number_of_points = 0;
	T lap_thresh = this->laplacian_threshold;
	T eigen_thresh = this->min_eigen_value_threshold;
	
	int sx = max(5, border);
	int sy = max(3, border);
	int ex = min(w - 5, w - border);
	int ey = min(h - 3, h - border);
	
	laplacian.SetCount(w * h, 0);
	
	ComputeLaplacian(srd_d, laplacian, w, h, Dxx, Dyy, sx, sy, ex, ey);
	points.SetCount(0);
	points.Reserve(512);
	row = (sy * w + sx);
	for (int y = sy; y < ey; ++y, row += w) {
		for (int x = sx, rowx = row; x < ex; ++x, ++rowx) {
			lv = laplacian[rowx];
			if ((lv < -lap_thresh &&
				 lv < laplacian[rowx - 1]     && lv < laplacian[rowx + 1] &&
				 lv < laplacian[rowx - w]     && lv < laplacian[rowx + w] &&
				 lv < laplacian[rowx - w - 1] && lv < laplacian[rowx + w - 1] &&
				 lv < laplacian[rowx - w + 1] && lv < laplacian[rowx + w + 1])
				||
				(lv > lap_thresh &&
				 lv > laplacian[rowx - 1]     && lv > laplacian[rowx + 1] &&
				 lv > laplacian[rowx - w]     && lv > laplacian[rowx + w] &&
				 lv > laplacian[rowx - w - 1] && lv > laplacian[rowx + w - 1] &&
				 lv > laplacian[rowx - w + 1] && lv > laplacian[rowx + w + 1])
			   ) {
			   
				min_eigen_value = (T)HessianMinEigenValue(srd_d, rowx, lv, Dxx, Dyy, Dxy, Dyx);
				if (min_eigen_value > eigen_thresh) {
					Keypoint& pt = points.Add();
					pt.x = x;
					pt.y = y;
					pt.score = min_eigen_value;
					++number_of_points;
					++x, ++rowx; // skip next pixel since this is maxima in 3x3
				}
			}
		}
	}
	
	return number_of_points;
}


NAMESPACE_TOPSIDE_END
