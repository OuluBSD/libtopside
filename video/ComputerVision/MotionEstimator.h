#ifndef _ComputerVision_MotionEstimator_h_
#define _ComputerVision_MotionEstimator_h_


NAMESPACE_TOPSIDE_BEGIN


inline double sqr(double x) {return x*x;}


// does isotropic normalization
template <class T>
void iso_normalize_points(const Vector<keypoint_t>& from, Vector<keypoint_t>& to, Vector<T>& T0, Vector<T>& T1, int count) {
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


bool have_collinear_points(Vector<keypoint_t>& points, int count);


class TransformationKernel {
	
	
public:
	virtual bool run(const Vector<keypoint_t>& from, Vector<keypoint_t>& to, FloatMat& model) = 0;
	virtual void error(const Vector<keypoint_t>& from, const Vector<keypoint_t>& to, const FloatMat& model, Vector<double>& err) = 0;
	
};

class affine2d : public TransformationKernel {
	matrix_t<float> T0;
	matrix_t<float> T1;
	matrix_t<float> AtA;
	matrix_t<float> AtB;
	matrix_t<float> a_mt;
	matrix_t<float> b_mt;

public:
	affine2d() :
		T0(3, 3, 1),
		T1(3, 3, 1),
		AtA(6, 6, 1),
		AtB(6, 1, 1)
	{
		// empty constructor
	}
	
	bool run(const Vector<keypoint_t>& from, Vector<keypoint_t>& to, FloatMat& model) override {
		int count = from.GetCount();
		
		int dt = 1;
		auto& md = model.data;
		auto&t0d = T0.data;
		auto&t1d = T1.data;
		
		iso_normalize_points(from, to, t0d, t1d, count);
		
		a_mt.SetSize(6, 2*count, 1);
		b_mt.SetSize(1, 2*count, 1);
		
		auto& ad = a_mt.data;
		auto&bd = b_mt.data;
		
		for (int i = 0; i < count; ++i) {
			const keypoint_t& pt0 = from[i];
			const keypoint_t& pt1 = to[i];
			
			double px = t0d[0] * pt0.x + t0d[1] * pt0.y + t0d[2];
			double py = t0d[3] * pt0.x + t0d[4] * pt0.y + t0d[5];
			
			int j = i * 2 * 6;
			ad[j] = px;
			ad[j+1] = py;
			ad[j+2] = 1.0;
			ad[j+3] = 0.0;
			ad[j+4] = 0.0;
			ad[j+5] = 0.0;
			
			j += 6;
			ad[j] = 0.0;
			ad[j+1] = 0.0;
			ad[j+2] = 0.0;
			ad[j+3] = px;
			ad[j+4] = py;
			ad[j+5] = 1.0;
			
			bd[i<<1] = t1d[0] * pt1.x + t1d[1] * pt1.y + t1d[2];
			bd[(i<<1)+1] = t1d[3] * pt1.x + t1d[4] * pt1.y + t1d[5];
		}
		
		multiply_AtA(AtA, a_mt);
		multiply_AtB(AtB, a_mt, b_mt);
		
		lu_solve(AtA, AtB);
		
		md[0] = AtB.data[0], md[1] = AtB.data[1], md[2] = AtB.data[2];
		md[3] = AtB.data[3], md[4] = AtB.data[4], md[5] = AtB.data[5];
		md[6] = 0.0, md[7] = 0.0, md[8] = 1.0; // fill last row
		
		// denormalize
		invert_3x3(T1, T1);
		multiply_3x3(model, T1, model);
		multiply_3x3(model, model, T0);
		
		return true;
	}
	
	void error(const Vector<keypoint_t>& from, const Vector<keypoint_t>& to, const FloatMat& model, Vector<double>& err) {
		int count = from.GetCount();
		const auto& m = model.data;
		
		auto f = from.Begin();
		auto t = to.Begin();
		for (auto& e : err) {
			const keypoint_t& pt0 = *f;
			const keypoint_t& pt1 = *t;
			
			e = sqr(pt1.x - m[0] * pt0.x - m[1] * pt0.y - m[2]) +
			    sqr(pt1.y - m[3] * pt0.x - m[4] * pt0.y - m[5]);
			
			f++;
			t++;
		}
		
		/*for (int i = 0; i < count; ++i) {
			const keypoint_t& pt0 = from[i];
			const keypoint_t& pt1 = to[i];
			
			err[i] = sqr(pt1.x - m[0] * pt0.x - m[1] * pt0.y - m[2]) +
					 sqr(pt1.y - m[3] * pt0.x - m[4] * pt0.y - m[5]);
		}*/
	}
	
	bool check_subset(const Vector<keypoint_t>& from, const Vector<keypoint_t>& to, int count) {
		return true; // all good
	}
	
};


class homography2d : public TransformationKernel {
	matrix_t<float> mLtL;
	matrix_t<float> Evec;
	matrix_t<float> T0;
	matrix_t<float> T1;


public:
	
	homography2d() :
		mLtL(9, 9, 1),
		Evec(9, 9, 1)
	{
		// empty constructor
		T0.SetSize(3, 3, 1);
		T1.SetSize(3, 3, 1);
		mLtL.SetSize(9, 9, 1);
		Evec.SetSize(9, 9, 1);
	}
	
	bool run(const Vector<keypoint_t>& from, Vector<keypoint_t>& to, FloatMat& model) override;
	void error(const Vector<keypoint_t>& from, const Vector<keypoint_t>& to, const FloatMat& model, Vector<double>& err);
	bool check_subset(const Vector<keypoint_t>& from, Vector<keypoint_t>& to, int count);
	
};


class ransac_params_t {
	
public:
	int size;
	double thresh, eps, prob;
	
public:
	void Init(int size = 0, double thresh = 0.5, double eps = 0.5, double prob = 0.99) {
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
	Vector<int> indices;

public:
	
	bool get_subset(Kernel& kernel, const Vector<keypoint_t>& from, const Vector<keypoint_t>& to, int need_cnt, int max_cnt, Vector<keypoint_t>& from_sub, Vector<keypoint_t>& to_sub) {
		int max_try = 1000;
		indices.Reserve(need_cnt);
		indices.SetCount(0);
		//var i = 0, j = 0, ssiter = 0, idx_i = 0, ok = false;
		int ssiter = 0;
		bool ok = false;
		int i = 0;
		from_sub.SetCount(0);
		from_sub.Reserve(128);
		to_sub.SetCount(0);
		to_sub.Reserve(128);
		for (; ssiter < max_try; ++ssiter)  {
			for (i = 0; i < need_cnt && ssiter < max_try;) {
				auto& idx = indices.Add();
				idx = 0;
				ok = false;
				int idx_i = 0;
				while (!ok) {
					ok = true;
					idx_i = idx = Random(max_cnt);
					for (int j = 0; j < i; ++j) {
						if (idx_i == indices[j]) {
							ok = false;
							break;
						}
					}
				}
				auto& f = from_sub.Add();
				auto& t = to_sub.Add();
				f = from[idx_i];
				t = to[idx_i];
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
	
	
	int find_inliers(Kernel& kernel, const FloatMat& model, const Vector<keypoint_t>& from, Vector<keypoint_t>& to, double thresh, Vector<double>& err, ByteMat& mask) {
		int numinliers = 0;
		double t = thresh * thresh;
		int count = from.GetCount();
		ASSERT(count);
		
		kernel.error(from, to, model, err);
		
		for (int i = 0; i < count; ++i) {
			bool f = err[i] <= t;
			mask.data[i] = f;
			numinliers += f * 1;
		}
		return numinliers;
	}
	
	bool ransac(ransac_params_t& params, Kernel& kernel, const Vector<keypoint_t>& from, Vector<keypoint_t>& to, FloatMat& model, ByteMat* mask, int max_iters = 1000) {
		int count = from.GetCount();
		if (count < params.size)
			return false;
			
		int model_points = params.size;
		int niters = max_iters;
		bool result = false;
		
		Vector<keypoint_t> subset0;
		Vector<keypoint_t> subset1;
		bool found = false;
		
		int mc = model.cols;
		int mr = model.rows;
		int dt = 1;
		
		FloatMat M (mc, mr, dt);
		ByteMat curr_mask(count, 1, 1);
		
		int inliers_max = -1;
		int numinliers = 0;
		int nmodels = 0;
		
		Vector<double> err;
		err.SetCount(count << 2);
		
		// special case
		if (count == model_points) {
			if (kernel.run(from, to, M) == 0) {
				return false;
			}
			
			M.copy_to(model);
			if (mask) {
				while (--count >= 0) {
					mask->data[count] = 1;
				}
			}
			return true;
		}
		
		for (int iter = 0; iter < niters; ++iter) {
			// generate subset
			found = get_subset(kernel, from, to, model_points, count, subset0, subset1);
			if (!found) {
				if (iter == 0) {
					return false;
				}
				break;
			}
			
			ASSERT(subset0.GetCount() == model_points);
			nmodels = kernel.run(subset0, subset1, M);
			if (nmodels <= 0)
				continue;
				
			// TODO handle multimodel output
			
			ASSERT(from.GetCount() == count);
			numinliers = find_inliers(kernel, M, from, to, params.thresh, err, curr_mask);
			
			if (numinliers > max(inliers_max, model_points - 1)) {
				M.copy_to(model);
				inliers_max = numinliers;
				if (mask)
					curr_mask.copy_to(*mask);
				niters = params.update_iters((count - numinliers) / count, niters);
				result = true;
			}
		}
		
		return result;
	}
	
	bool lmeds(ransac_params_t& params, Kernel& kernel, const Vector<keypoint_t>& from, Vector<keypoint_t>& to, FloatMat& model, ByteMat* mask, int max_iters = 1000) {
		int count = from.GetCount();
		if (count < params.size)
			return false;
			
		int model_points = params.size;
		int niters = max_iters;
		bool result = false;
		
		Vector<keypoint_t> subset0;
		Vector<keypoint_t> subset1;
		bool found = false;
		
		int mc = model.cols;
		int mr = model.rows;
		int dt = 1;
		
		FloatMat M;
		M.SetSize(mc, mr, dt);
		
		ByteMat curr_mask;
		curr_mask.SetSize(count, 1, 1);
		
		int numinliers = 0;
		int nmodels = 0;
		
		Vector<double> err;
		double min_median = 1000000000.0;
		double sigma = 0.0;
		double median_i = 0.0;
		
		params.eps = 0.45;
		niters = params.update_iters(params.eps, niters);
		
		// special case
		if (count == model_points) {
			if (kernel.run(from, to, M) == 0) {
				return false;
			}
			
			M.copy_to(model);
			if (mask) {
				while (--count >= 0) {
					mask->data[count] = 1;
				}
			}
			return true;
		}
		
		for (int iter = 0; iter < niters; ++iter) {
			// generate subset
			found = get_subset(kernel, from, to, model_points, count, subset0, subset1);
			if (!found) {
				if (iter == 0) {
					return false;
				}
				break;
			}
			
			ASSERT(subset0.GetCount() == model_points);
			nmodels = kernel.run(subset0, subset1, M);
			if (nmodels <= 0)
				continue;
				
			// TODO handle multimodel output
			ASSERT(from.GetCount() == count);
			kernel.error(from, to, M, err);
			ASSERT(err.GetCount() == count);
			median_i = median(err, 0, count - 1);
			
			if (median_i < min_median) {
				min_median = median_i;
				M.copy_to(model);
				result = true;
			}
		}
		
		if (result) {
			sigma = 2.5 * 1.4826 * (1 + 5.0 / (count - model_points)) * FastSqrt(min_median);
			sigma = max(sigma, 0.001);
			
			numinliers = find_inliers(kernel, model, from, to, sigma, err, curr_mask);
			if (mask)
				*mask = curr_mask;
				
			result = numinliers >= model_points;
		}
		
		return result;
	}
	
};



NAMESPACE_TOPSIDE_END

#endif
