#ifndef _ComputerVision_MotionEstimator_h_
#define _ComputerVision_MotionEstimator_h_


NAMESPACE_TOPSIDE_BEGIN


inline double sqr(double x) {return x*x;}


// does isotropic normalization
template <class T>
void iso_normalize_points(const Vector<Point>& from, Vector<Point>& to, Vector<T>& T0, Vector<T>& T1, int count) {
	double cx0 = 0.0, cy0 = 0.0, d0 = 0.0, s0 = 0.0;
	double cx1 = 0.0, cy1 = 0.0, d1 = 0.0, s1 = 0.0;
	double  dx = 0.0,  dy = 0.0;
	
	for (int i = 0; i < count; ++i) {
		cx0 += from[i].x;
		cy0 += from[i].y;
		cx1 += to[i].x;
		cy1 += to[i].y;
	}
	
	cx0 /= count;
	cy0 /= count;
	cx1 /= count;
	cy1 /= count;
	
	for (int i = 0; i < count; ++i) {
		dx = from[i].x - cx0;
		dy = from[i].y - cy0;
		d0 += FastSqrt(dx * dx + dy * dy);
		dx = to[i].x - cx1;
		dy = to[i].y - cy1;
		d1 += FastSqrt(dx * dx + dy * dy);
	}
	
	d0 /= count;
	d1 /= count;
	
	s0 = M_SQRT2 / d0;
	s1 = M_SQRT2 / d1;
	
	T0[0] = T0[4] = (T)s0;
	T0[2] = (T)(-cx0 * s0);
	T0[5] = (T)(-cy0 * s0);
	T0[1] = T0[3] = T0[6] = T0[7] = (T)0.0;
	T0[8] = (T)1.0;
	
	T1[0] = T1[4] = (T)s1;
	T1[2] = (T)(-cx1 * s1);
	T1[5] = (T)(-cy1 * s1);
	T1[1] = T1[3] = T1[6] = T1[7] = (T)0.0;
	T1[8] = (T)1.0;
}


bool have_collinear_points(Vector<Point>& points, int count);


class affine2d {
	matrix_t<float> T0;
	matrix_t<float> T1;
	matrix_t<float> AtA;
	matrix_t<float> AtB;

public:
	affine2d() :
		T0(3, 3, 1),
		T1(3, 3, 1),
		AtA(6, 6, 1),
		AtB(6, 1, 1)
	{
		// empty constructor
	}
	
	template<class T>
	bool run(const Vector<Point>& from, Vector<Point>& to, matrix_t<T> model, int count) {
		var dt = model.type | C1_t;
		var md = model.data, t0d = T0.data, t1d = T1.data;
		var pt0, pt1;
		
		iso_normalize_points(from, to, t0d, t1d, count);
		
		var a_buff = cache.get_buffer((2 * count * 6) << 3);
		var b_buff = cache.get_buffer((2 * count) << 3);
		
		var a_mt = new matrix_t(6, 2*count, dt, a_buff.data);
		var b_mt = new matrix_t(1, 2*count, dt, b_buff.data);
		var ad = a_mt.data, bd = b_mt.data;
		
		for (int i = 0; i < count; ++i) {
			pt0 = from[i];
			pt1 = to[i];
			
			double px = t0d[0] * pt0.x + t0d[1] * pt0.y + t0d[2];
			double py = t0d[3] * pt0.x + t0d[4] * pt0.y + t0d[5];
			
			int j = i * 2 * 6;
			ad[j] = px, ad[j+1] = py, ad[j+2] = 1.0, ad[j+3] = 0.0, ad[j+4] = 0.0, ad[j+5] = 0.0;
			
			j += 6;
			ad[j] = 0.0, ad[j+1] = 0.0, ad[j+2] = 0.0, ad[j+3] = px, ad[j+4] = py, ad[j+5] = 1.0;
			
			bd[i<<1] = t1d[0] * pt1.x + t1d[1] * pt1.y + t1d[2];
			bd[(i<<1)+1] = t1d[3] * pt1.x + t1d[4] * pt1.y + t1d[5];
		}
		
		multiply_AtA(AtA, a_mt);
		multiply_AtB(AtB, a_mt, b_mt);
		
		linalg.lu_solve(AtA, AtB);
		
		md[0] = AtB.data[0], md[1] = AtB.data[1], md[2] = AtB.data[2];
		md[3] = AtB.data[3], md[4] = AtB.data[4], md[5] = AtB.data[5];
		md[6] = 0.0, md[7] = 0.0, md[8] = 1.0; // fill last row
		
		// denormalize
		invert_3x3(T1, T1);
		multiply_3x3(model, T1, model);
		multiply_3x3(model, model, T0);
		
		// free buffer
		cache.put_buffer(a_buff);
		cache.put_buffer(b_buff);
		
		return true;
	}
	
	template<class T>
	void error(const Vector<Point>& from, const Vector<Point>& to, const matrix_t<T>& model, Vector<double>& err, int count) {
		const auto& m = model.data;
		
		auto f = from.Begin();
		auto t = to.Begin();
		for (auto& e : err) {
			const Point& pt0 = *f;
			const Point& pt1 = *t;
			
			e = sqr(pt1.x - m[0] * pt0.x - m[1] * pt0.y - m[2]) +
			    sqr(pt1.y - m[3] * pt0.x - m[4] * pt0.y - m[5]);
			
			f++;
			t++;
		}
		
		/*for (int i = 0; i < count; ++i) {
			const Point& pt0 = from[i];
			const Point& pt1 = to[i];
			
			err[i] = sqr(pt1.x - m[0] * pt0.x - m[1] * pt0.y - m[2]) +
					 sqr(pt1.y - m[3] * pt0.x - m[4] * pt0.y - m[5]);
		}*/
	}
	
	bool check_subset(const Vector<Point>& from, const Vector<Point>& to, int count) {
		return true; // all good
	}
	
};


class homography2d {
	matrix_t<float> mLtL;
	matrix_t<float> Evec;


public:
	
	homography2d() :
		mLtL(9, 9, 1),
		Evec(9, 9, 1)
	{
		// empty constructor
		//this->T0 = new matrix_t(3, 3, F32_t|C1_t);
		//this->T1 = new matrix_t(3, 3, F32_t|C1_t);
		//this->mLtL = new matrix_t(9, 9, F32_t|C1_t);
		//this->Evec = new matrix_t(9, 9, F32_t|C1_t);
	}
	
	template<class T>
	bool run(const Vector<T>& from, Vector<T>& to, const matrix_t<T>& model, int count) {
		const auto& md = model.data;
		auto& t0d = T0.data;
		auto& t1d = T1.data;
		auto& LtL = mLtL.data;
		auto& = Evec.data;
		double x = 0.0, y = 0.0, X = 0.0, Y = 0.0;
		
		// norm
		double smx = 0.0, smy = 0.0, cmx = 0.0, cmy = 0.0, sMx = 0.0, sMy = 0.0, cMx = 0.0, cMy = 0.0;
		
		for (int i = 0; i < count; ++i) {
			cmx += to[i].x;
			cmy += to[i].y;
			cMx += from[i].x;
			cMy += from[i].y;
		}
		
		cmx /= count;
		cmy /= count;
		cMx /= count;
		cMy /= count;
		
		for (int i = 0; i < count; ++i) {
			smx += abs(to[i].x - cmx);
			smy += abs(to[i].y - cmy);
			sMx += abs(from[i].x - cMx);
			sMy += abs(from[i].y - cMy);
		}
		
		if (   abs(smx) < EPSILON
			|| abs(smy) < EPSILON
			|| abs(sMx) < EPSILON
			|| abs(sMy) < EPSILON)
			return 0;
			
		smx = count / smx;
		smy = count / smy;
		sMx = count / sMx;
		sMy = count / sMy;
		
		t0d[0] = sMx;
		t0d[1] = 0;
		t0d[2] = -cMx * sMx;
		t0d[3] = 0;
		t0d[4] = sMy;
		t0d[5] = -cMy * sMy;
		t0d[6] = 0;
		t0d[7] = 0;
		t0d[8] = 1;
		
		t1d[0] = 1.0 / smx;
		t1d[1] = 0;
		t1d[2] = cmx;
		t1d[3] = 0;
		t1d[4] = 1.0 / smy;
		t1d[5] = cmy;
		t1d[6] = 0;
		t1d[7] = 0;
		t1d[8] = 1;
		//
		
		// construct system
		{
			int i = 81;
			while (--i >= 0) {
				LtL[i] = 0.0;
			}
		}
		for (int i = 0; i < count; ++i) {
			x = (to[i].x - cmx) * smx;
			y = (to[i].y - cmy) * smy;
			X = (from[i].x - cMx) * sMx;
			Y = (from[i].y - cMy) * sMy;
			
			LtL[0] += X * X;
			LtL[1] += X * Y;
			LtL[2] += X;
			
			LtL[6] += X * -x * X;
			LtL[7] += X * -x * Y;
			LtL[8] += X * -x;
			LtL[10] += Y * Y;
			LtL[11] += Y;
			
			LtL[15] += Y * -x * X;
			LtL[16] += Y * -x * Y;
			LtL[17] += Y * -x;
			LtL[20] += 1.0;
			
			LtL[24] += -x * X;
			LtL[25] += -x * Y;
			LtL[26] += -x;
			LtL[30] += X * X;
			LtL[31] += X * Y;
			LtL[32] += X;
			LtL[33] += X * -y * X;
			LtL[34] += X * -y * Y;
			LtL[35] += X * -y;
			LtL[40] += Y * Y;
			LtL[41] += Y;
			LtL[42] += Y * -y * X;
			LtL[43] += Y * -y * Y;
			LtL[44] += Y * -y;
			LtL[50] += 1.0;
			LtL[51] += -y * X;
			LtL[52] += -y * Y;
			LtL[53] += -y;
			LtL[60] += -x * X * -x * X + -y * X * -y * X;
			LtL[61] += -x * X * -x * Y + -y * X * -y * Y;
			LtL[62] += -x * X * -x + -y * X * -y;
			LtL[70] += -x * Y * -x * Y + -y * Y * -y * Y;
			LtL[71] += -x * Y * -x + -y * Y * -y;
			LtL[80] += -x * -x + -y * -y;
		}
		//
		
		// symmetry
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < i; ++j)
				LtL[i*9+j] = LtL[j*9+i];
		}
		
		linalg.eigenVV(mLtL, Evec);
		
		md[0] = evd[72], md[1] = evd[73], md[2] = evd[74];
		md[3] = evd[75], md[4] = evd[76], md[5] = evd[77];
		md[6] = evd[78], md[7] = evd[79], md[8] = evd[80];
		
		// denormalize
		multiply_3x3(model, T1, model);
		multiply_3x3(model, model, T0);
		
		// set bottom right to 1.0
		x = 1.0 / md[8];
		md[0] *= x;
		md[1] *= x;
		md[2] *= x;
		md[3] *= x;
		md[4] *= x;
		md[5] *= x;
		md[6] *= x;
		md[7] *= x;
		md[8] = 1.0;
		
		return true;
	}
	
	template <class T>
	void error(const Vector<T>& from, Vector<T>& to, const matrix_t<T>& model, Vector<double>& err, int count) {
		const auto& m = model.data;
		
		auto f = from.Begin();
		auto t = to.Begin();
		for (auto& e : err) {
			const Point& pt0 = *f;
			const Point& pt1 = *t;
			
			double ww = 1.0 / (m[6] * pt0.x + m[7] * pt0.y + 1.0);
			double dx = (m[0] * pt0.x + m[1] * pt0.y + m[2]) * ww - pt1.x;
			double dy = (m[3] * pt0.x + m[4] * pt0.y + m[5]) * ww - pt1.y;
			e = (dx * dx + dy * dy);
			
			f++;
			t++;
		}
	}
	
	template <class T>
	void check_subset(const Vector<T>& from, Vector<T>& to, int count) {
		// seems to reject good subsets actually
		//if( have_collinear_points(from, count) || have_collinear_points(to, count) ) {
		//return false;
		//}
		if (count == 4) {
			int negative = 0;
			
			var fp0 = from[0], fp1 = from[1], fp2 = from[2], fp3 = from[3];
			var tp0 = to[0], tp1 = to[1], tp2 = to[2], tp3 = to[3];
			
			// set1
			var A11 = fp0.x, A12 = fp0.y, A13 = 1.0;
			var A21 = fp1.x, A22 = fp1.y, A23 = 1.0;
			var A31 = fp2.x, A32 = fp2.y, A33 = 1.0;
			
			var B11 = tp0.x, B12 = tp0.y, B13 = 1.0;
			var B21 = tp1.x, B22 = tp1.y, B23 = 1.0;
			var B31 = tp2.x, B32 = tp2.y, B33 = 1.0;
			
			var detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
			var detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
			
			if (detA*detB < 0)
				negative++;
			
			// set2
			A11 = fp1.x, A12 = fp1.y;
			A21 = fp2.x, A22 = fp2.y;
			A31 = fp3.x, A32 = fp3.y;
			
			B11 = tp1.x, B12 = tp1.y;
			B21 = tp2.x, B22 = tp2.y;
			B31 = tp3.x, B32 = tp3.y;
			
			detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
			detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
			
			if (detA*detB < 0)
				negative++;
				
			// set3
			A11 = fp0.x, A12 = fp0.y;
			A21 = fp2.x, A22 = fp2.y;
			A31 = fp3.x, A32 = fp3.y;
			
			B11 = tp0.x, B12 = tp0.y;
			B21 = tp2.x, B22 = tp2.y;
			B31 = tp3.x, B32 = tp3.y;
			
			detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
			detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
			
			if (detA*detB < 0)
				negative++;
				
			// set4
			A11 = fp0.x, A12 = fp0.y;
			A21 = fp1.x, A22 = fp1.y;
			A31 = fp3.x, A32 = fp3.y;
			
			B11 = tp0.x, B12 = tp0.y;
			B21 = tp1.x, B22 = tp1.y;
			B31 = tp3.x, B32 = tp3.y;
			
			detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
			detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
			
			if (detA*detB < 0)
				negative++;
				
			if (negative != 0 && negative != 4) {
				return false;
			}
		}
		return true; // all good
	}
};


class ransac_params_t {
	int size;
	double thresh, eps, prob;
	
public:
	ransac_params_t(int size = 0, double thresh = 0.5, double eps = 0.5, double prob = 0.99) {
		this->size = size;
		this->thresh = thresh;
		this->eps = eps;
		this->prob = prob;
	}
	
	int update_iters(double _eps, int max_iters) {
		double num = FastLn(1 - this->prob);
		double denom = FastLn(1 - pow_fast(1 - _eps, this->size));
		return (denom >= 0 || -num >= max_iters*(-denom)) ? max_iters : (int)round(num / denom);
	}
};


template <class Kernel>
class motion_estimator {


public:
	
	template <class T>
	bool get_subset(Kernel& kernel, const Vector<T>& from, const Vector<T>& to, int need_cnt, int max_cnt, Vector<T>& from_sub, Vector<T>& to_sub) {
		int max_try = 1000;
		var indices = [];
		//var i = 0, j = 0, ssiter = 0, idx_i = 0, ok = false;
		int ssiter = 0;
		bool ok = false;
		for (; ssiter < max_try; ++ssiter)  {
			for (int i = 0; i < need_cnt && ssiter < max_try;) {
				ok = false;
				int idx_i = 0;
				while (!ok) {
					ok = true;
					idx_i = indices[i] = floor(Math.random() * max_cnt);
					for (int j = 0; j < i; ++j) {
						if (idx_i == indices[j]) {
							ok = false;
							break;
						}
					}
				}
				from_sub[i] = from[idx_i];
				to_sub[i] = to[idx_i];
				if (!kernel.check_subset(from_sub, to_sub, i + 1)) {
					ssiter++;
					continue;
				}
				++i;
			}
			break;
		}
		
		return (i == need_cnt && ssiter < max_try);
	}
	
	template <class T>
	int find_inliers(Kernel& kernel, const matrix_t<T>& model, const Vector<T>& from, const Vector<T>& to, int count, double thresh, const Vector<double>& err, Vector<bool>& mask) {
		int numinliers = 0;
		double t = thresh * thresh;
		
		kernel.error(from, to, model, err, count);
		
		for (int i = 0; i < count; ++i) {
			bool f = err[i] <= t;
			mask[i] = f;
			numinliers += f * 1;
		}
		return numinliers;
	}
	
	template <class T>
	bool ransac(const ransac_params_t& params, Kernel& kernel, const Vector<T>& from, const Vector<T>& to, int count, const matrix_t<T>& model, Vector<bool>& mask, int max_iters = 1000) {
	
		if (count < params.size)
			return false;
			
		int model_points = params.size;
		int niters = max_iters;
		bool result = false;
		
		var subset0 = [];
		var subset1 = [];
		bool found = false;
		
		int mc = model.cols;
		int mr = model.rows;
		var dt = model.type | C1_t;
		
		var m_buff = cache.get_buffer((mc * mr) << 3);
		var ms_buff = cache.get_buffer(count);
		var err_buff = cache.get_buffer(count << 2);
		var M = new matrix_t(mc, mr, dt, m_buff.data);
		var curr_mask = new matrix_t(count, 1, U8C1_t, ms_buff.data);
		
		int inliers_max = -1;
		int numinliers = 0;
		int nmodels = 0;
		
		var err = err_buff.f32;
		
		// special case
		if (count == model_points) {
			if (kernel.run(from, to, M, count) <= 0) {
				cache.put_buffer(m_buff);
				cache.put_buffer(ms_buff);
				cache.put_buffer(err_buff);
				return false;
			}
			
			M.copy_to(model);
			if (mask) {
				while (--count >= 0) {
					mask.data[count] = 1;
				}
			}
			cache.put_buffer(m_buff);
			cache.put_buffer(ms_buff);
			cache.put_buffer(err_buff);
			return true;
		}
		
		for (int iter = 0; iter < niters; ++iter) {
			// generate subset
			found = get_subset(kernel, from, to, model_points, count, subset0, subset1);
			if (!found) {
				if (iter == 0) {
					cache.put_buffer(m_buff);
					cache.put_buffer(ms_buff);
					cache.put_buffer(err_buff);
					return false;
				}
				break;
			}
			
			nmodels = kernel.run(subset0, subset1, M, model_points);
			if (nmodels <= 0)
				continue;
				
			// TODO handle multimodel output
			
			numinliers = find_inliers(kernel, M, from, to, count, params.thresh, err, curr_mask.data);
			
			if (numinliers > max(inliers_max, model_points - 1)) {
				M.copy_to(model);
				inliers_max = numinliers;
				if (mask)
					curr_mask.copy_to(mask);
				niters = params.update_iters((count - numinliers) / count, niters);
				result = true;
			}
		}
		
		cache.put_buffer(m_buff);
		cache.put_buffer(ms_buff);
		cache.put_buffer(err_buff);
		
		return result;
	}
	
	template <class T>
	bool lmeds(const ransac_params_t& params, Kernel& kernel, const Vector<T>& from, Vector<T>& to, int count, const matrix_t<T>& model, Vector<bool>& mask, int max_iters = 1000) {
	
		if (count < params.size)
			return false;
			
		int model_points = params.size;
		int niters = max_iters;
		bool result = false;
		
		var subset0 = [];
		var subset1 = [];
		bool found = false;
		
		int mc = model.cols;
		int mr = model.rows;
		var dt = model.type | C1_t;
		
		var m_buff = cache.get_buffer((mc * mr) << 3);
		var ms_buff = cache.get_buffer(count);
		var err_buff = cache.get_buffer(count << 2);
		var M = new matrix_t(mc, mr, dt, m_buff.data);
		var curr_mask = new matrix_t(count, 1, U8_t | C1_t, ms_buff.data);
		
		int numinliers = 0;
		int nmodels = 0;
		
		var err = err_buff.f32;
		double min_median = 1000000000.0;
		double sigma = 0.0;
		double median = 0.0;
		
		params.eps = 0.45;
		niters = params.update_iters(params.eps, niters);
		
		// special case
		if (count == model_points) {
			if (kernel.run(from, to, M, count) <= 0) {
				cache.put_buffer(m_buff);
				cache.put_buffer(ms_buff);
				cache.put_buffer(err_buff);
				return false;
			}
			
			M.copy_to(model);
			if (mask) {
				while (--count >= 0) {
					mask.data[count] = 1;
				}
			}
			cache.put_buffer(m_buff);
			cache.put_buffer(ms_buff);
			cache.put_buffer(err_buff);
			return true;
		}
		
		for (int iter = 0; iter < niters; ++iter) {
			// generate subset
			found = get_subset(kernel, from, to, model_points, count, subset0, subset1);
			if (!found) {
				if (iter == 0) {
					cache.put_buffer(m_buff);
					cache.put_buffer(ms_buff);
					cache.put_buffer(err_buff);
					return false;
				}
				break;
			}
			
			nmodels = kernel.run(subset0, subset1, M, model_points);
			if (nmodels <= 0)
				continue;
				
			// TODO handle multimodel output
			
			kernel.error(from, to, M, err, count);
			median = math.median(err, 0, count - 1);
			
			if (median < min_median) {
				min_median = median;
				M.copy_to(model);
				result = true;
			}
		}
		
		if (result) {
			sigma = 2.5 * 1.4826 * (1 + 5.0 / (count - model_points)) * FastSqrt(min_median);
			sigma = max(sigma, 0.001);
			
			numinliers = find_inliers(kernel, model, from, to, count, sigma, err, curr_mask.data);
			if (mask)
				curr_mask.copy_to(mask);
				
			result = numinliers >= model_points;
		}
		
		cache.put_buffer(m_buff);
		cache.put_buffer(ms_buff);
		cache.put_buffer(err_buff);
		
		return result;
	}
	
};



NAMESPACE_TOPSIDE_END

#endif
