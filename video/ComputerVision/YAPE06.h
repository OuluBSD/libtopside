#ifndef _ComputerVision_YAPE06_h_
#define _ComputerVision_YAPE06_h_


NAMESPACE_OULU_BEGIN

class yape06 {


public:
	void compute_laplacian(src, dst, w, h, Dxx, Dyy, int sx, int sy, int ex, int ey) {
		int yrow = (sy * w + sx);
		int row = yrow;
		
		for (int y = sy; y < ey; ++y, yrow += w, row = yrow) {
			for (int x = sx; x < ex; ++x, ++row) {
				dst[row] = -4 * src[row] + src[row+Dxx] + src[row-Dxx] + src[row+Dyy] + src[row-Dyy];
			}
		}
	}
	
	double hessian_min_eigen_value(src, int off, double tr, int Dxx, int Dyy, int Dxy, int Dyx) {
		double Ixx = -2 * src[off] + src[off + Dxx] + src[off - Dxx];
		double Iyy = -2 * src[off] + src[off + Dyy] + src[off - Dyy];
		double Ixy = src[off + Dxy] + src[off - Dxy] - src[off + Dyx] - src[off - Dyx];
		double sqrt_delta = (sqrt_fast(((Ixx - Iyy) * (Ixx - Iyy) + 4 * Ixy * Ixy)));
		
		return min(abs(tr - sqrt_delta), abs(-(tr + sqrt_delta)));
	}
	
	
	int laplacian_threshold = 30;
	int min_eigen_value_threshold = 25;
	
	int detect(src, points, int border = 5) {
		var w = src.cols, h = src.rows, srd_d = src.data;
		var Dxx = 5, Dyy = (5 * w);
		var Dxy = (3 + 3 * w), Dyx = (3 - 3 * w);
		var lap_buf = cache.get_buffer((w * h) << 2);
		var laplacian = lap_buf.i32;
		var lv = 0, row = 0, rowx = 0, min_eigen_value = 0, pt;
		var number_of_points = 0;
		var lap_thresh = this->laplacian_threshold;
		var eigen_thresh = this->min_eigen_value_threshold;
		
		var sx = max(5, border);
		var sy = max(3, border);
		var ex = min(w - 5, w - border);
		var ey = min(h - 3, h - border);
		
		{
			int x = w * h;
			while (--x >= 0) {
				laplacian[x] = 0;
			}
		}
		
		compute_laplacian(srd_d, laplacian, w, h, Dxx, Dyy, sx, sy, ex, ey);
		
		row = (sy * w + sx);
		for (int y = sy; y < ey; ++y, row += w) {
			for (int x = sx, rowx = row; x < ex; ++x, ++rowx) {
			
				lv = laplacian[rowx];
				if ((lv < -lap_thresh &&
					 lv < laplacian[rowx - 1]      && lv < laplacian[rowx + 1] &&
					 lv < laplacian[rowx - w]     && lv < laplacian[rowx + w] &&
					 lv < laplacian[rowx - w - 1] && lv < laplacian[rowx + w - 1] &&
					 lv < laplacian[rowx - w + 1] && lv < laplacian[rowx + w + 1])
					||
					(lv > lap_thresh &&
					 lv > laplacian[rowx - 1]      && lv > laplacian[rowx + 1] &&
					 lv > laplacian[rowx - w]     && lv > laplacian[rowx + w] &&
					 lv > laplacian[rowx - w - 1] && lv > laplacian[rowx + w - 1] &&
					 lv > laplacian[rowx - w + 1] && lv > laplacian[rowx + w + 1])
				   ) {
				   
					min_eigen_value = hessian_min_eigen_value(srd_d, rowx, lv, Dxx, Dyy, Dxy, Dyx);
					if (min_eigen_value > eigen_thresh) {
						pt = points[number_of_points];
						pt.x = x, pt.y = y, pt.score = min_eigen_value;
						++number_of_points;
						++x, ++rowx; // skip next pixel since this is maxima in 3x3
					}
				}
			}
		}
		
		cache.put_buffer(lap_buf);
		
		return number_of_points;
	}
	
};



NAMESPACE_OULU_END

#endif
